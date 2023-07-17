//==============================================================================
// Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv2d
//------------------------------------------------------------------------------
Conv2d::Conv2d(size_t nFilters, size_t nRowsFilter, size_t nColsFilter, size_t stride, size_t padding, bool randInitFlag) : Gear(true),
	_nFilters(nFilters), _nRowsFilter(nRowsFilter), _nColsFilter(nColsFilter), _stride(stride), _padding(padding), _randInitFlag(randInitFlag)
{
}

Conv2d::Conv2d(Array* pArrayFilter, Array* pArrayBias, size_t stride, size_t padding, bool randInitFlag) : Gear(true),
	_stride(stride), _padding(padding), _pArrayFilter(pArrayFilter), _pArrayBias(pArrayBias), _randInitFlag(randInitFlag)
{
	const DimSizes& dimSizes = pArrayFilter->GetDimSizes();
	_nFilters = dimSizes[0];
	_nRowsFilter = dimSizes[2];
	_nColsFilter = dimSizes[3];
}

void Conv2d::Initialize()
{
}

bool Conv2d::ValidateArrayFilter(const Array& arrayFilter)
{
	return true;
}

bool Conv2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller)
{
	// arrayFwdIn                                  .. (nSamples, nChannels, nRowsFwdIn, nColsFwdIn)
	// _pArrayFilter                               .. (nFilters, nChannels, nRowsFilter, nColsFilter)
	// _pArrayFwd1 = Img2dToCol(arrayFwdIn)        .. (nSamples * nRowsFwdOut * nColsFwdOut, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd2 = _pArrayFilter.Reshape()       .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd3 = _pArrayFwd2.Transpose2d()     .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayFwd4 = _pArrayFwd1 |.| _pArrayFwd3   .. (nSamples * nRowsFwdOut * nColsFwdOut, nFilters)
	// _pArrayFwd5 = _pArrayFwd4.Reshape()         .. (nSamples, nRowsFwdOut, nColsFwdOut, nFilters)
	// pArrayFwdOut = _pArrayFwd5.TransposeMulti() .. (nSamples, nFilters, nRowsFwdOut, nColsFwdOut)
	const DimSizes& dimSizesFwdIn = arrayFwdIn.GetDimSizes();
	size_t nSamples = dimSizesFwdIn[0];
	size_t nChannels = dimSizesFwdIn[1];
	size_t nRowsIn = dimSizesFwdIn[2], nColsIn = dimSizesFwdIn[3];
	size_t nRowsFwdOut, nColsFwdOut;
	if (!Img2dToCol(_pArrayFwd1, arrayFwdIn, _nRowsFilter, _nColsFilter, _stride, _stride, _padding, _padding, &nRowsFwdOut, &nColsFwdOut)) return false;
	if (!_pArrayFilter) {
		_pArrayFilter.reset(Array::Create(arrayFwdIn.GetElemType(), DimSizes(_nFilters, nChannels, _nRowsFilter, _nColsFilter)));
		controller.InitArray(*_pArrayFilter, nColsIn);
	}
	if (!_pArrayBias) {
		_pArrayBias.reset(Array::Create(arrayFwdIn.GetElemType(), DimSizes(_nFilters, nRowsFwdOut, nColsFwdOut)));
		controller.InitArray(*_pArrayBias, nColsIn);
	}
	_pArrayFilter->Reshape(_pArrayFwd2, DimSizes(_nFilters, nChannels * _nRowsFilter * _nColsFilter));
	if (!_pArrayFwd2->Transpose2d(_pArrayFwd3)) return false;
	if (!Array::Dot(_pArrayFwd4, *_pArrayFwd1, *_pArrayFwd3)) return false;
	_pArrayFwd4->Reshape(_pArrayFwd5, DimSizes(nSamples, nRowsFwdOut, nColsFwdOut, _nFilters));
	_pArrayFwd5->TransposeMulti(_pArrayFwd6, NumList<size_t>::Create(0, 3, 1, 2));
	Array::Add(pArrayFwdOut, *_pArrayFwd6, *_pArrayBias);
	_pArrayFwdInSaved.reset(arrayFwdIn.Reference());
	_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	return true;
}

bool Conv2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	// arrayBwdIn                                .. (nSamples, nFilters, nRowsBwdIn, nColsBwdIn)
	// _pArrayFilter                             .. (nFilters, nChannels, nRowsFilter, nColsFilter)
	// _pArrayFwd1                               .. (nSamples * nRowsFwdOut * nColsFwdOut, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd2                               .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayBwd1 = arrayBwdIn.TransposeMulti() .. (nSamples, nRowsBwdIn, nColsBwdIn, nFilters)
	// _pArrayBwd2 = _pArrayBwd1.Reshape()       .. (nSamples * nRowsBwdIn * nColsBwdIn, nFilters)
	// _pArrayBwd3 = _pArrayFwd1.Transpose2d()   .. (nChannels * nRowsFilter * nColsFilter, nSamples * nRowsFwdOut * nColsFwdOut)
	// _pArrayBwd4 = _pArrayBwd3 |.| _pArrayBwd2 .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayBwd5 = _pArrayBwd4.Transpose2d()   .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFilterGrad = _pArrayBwd5.Rehape()  .. (nFilters, nChannels, nRowsFilter, nColsFIlter)
	// _pArrayBwd6 = _pArrayBwd2 |.| _pArrayFwd2 .. (nSamples * nRowsBwdIn * nColsBwdIn, nChannels * nRowsFilter * nColsFilter)
	// pArrayBwdOut = ColToImg2d(_pArrayBwd6)    .. (nSamples, nChannels, nRowsFwdIn, nColsFwdIn)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	size_t nChannels = dimSizesFilter[1];
	const DimSizes& dimSizesBwdIn = arrayBwdIn.GetDimSizes();
	size_t nSamples = dimSizesBwdIn[0];
	size_t nRowsBwdIn = dimSizesBwdIn[2], nColsBwdIn = dimSizesBwdIn[3];
	_pArrayBiasGrad.reset(arrayBwdIn.Reference());
	arrayBwdIn.TransposeMulti(_pArrayBwd1, NumList<size_t>::Create(0, 2, 3, 1));
	_pArrayBwd1->Reshape(_pArrayBwd2, DimSizes(nSamples * nRowsBwdIn * nColsBwdIn, _nFilters));
	_pArrayFwd1->Transpose2d(_pArrayBwd3);
	if (!Array::Dot(_pArrayBwd4, *_pArrayBwd3, *_pArrayBwd2)) return false;
	_pArrayBwd4->Transpose2d(_pArrayBwd5);
	_pArrayBwd5->Reshape(_pArrayFilterGrad, DimSizes(_nFilters, nChannels, _nRowsFilter, _nColsFilter));
	if (!Array::Dot(_pArrayBwd6, *_pArrayBwd2, *_pArrayFwd2)) return false;
	if (bwdPropagationFlag && !ColToImg2d(pArrayBwdOut, _pArrayFwdInSaved->GetDimSizes(), *_pArrayBwd6,
				_nRowsFilter, _nColsFilter, _stride, _stride, _padding, _padding)) return false;
	return _pOptimizerInstFilter->Update(processor, _pArrayFilter, *_pArrayFilterGrad) &&
			_pOptimizerInstBias->Update(processor, _pArrayBias, *_pArrayBiasGrad);
}

String Conv2d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Conv2d");
}

bool Conv2d::Serialize(Stream& stream) const
{
	if (!stream.SerializePackedNumber<size_t>(_stride)) return false;
	if (!stream.SerializePackedNumber<size_t>(_padding)) return false;
	if (!stream.SerializeNumber<bool>(_randInitFlag)) return false;
	if (!_pArrayFilter->Serialize(stream)) return false;
	if (!_pArrayBias->Serialize(stream)) return false;
	return true;
}

Conv2d* Conv2d::Deserialize(Stream& stream)
{
	size_t stride, padding;
	bool randInitFlag;
	if (!stream.DeserializePackedNumber<size_t>(stride)) return nullptr;
	if (!stream.DeserializePackedNumber<size_t>(padding)) return nullptr;
	if (!stream.DeserializeNumber<bool>(randInitFlag)) return nullptr;
	RefPtr<Array> pArrayFilter(Array::Deserialize(stream));
	if (!pArrayFilter) return nullptr;
	RefPtr<Array> pArrayBias(Array::Deserialize(stream));
	if (!pArrayBias) return nullptr;
	return new Conv2d(pArrayFilter.release(), pArrayBias.release(), stride, padding, randInitFlag);
}

//------------------------------------------------------------------------------
// Conv2dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Conv2dOwner
//------------------------------------------------------------------------------
void Conv2dOwner::Clear()
{
	for (Conv2d* pConv2d : *this) Conv2d::Delete(pConv2d);
	clear();
}

Gurax_EndModuleScope(ml)
