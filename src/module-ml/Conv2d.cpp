//==============================================================================
// Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv2d
//------------------------------------------------------------------------------
Conv2d::Conv2d(Array* pArrayFilter, size_t strides, size_t padding) : _pArrayFilter(pArrayFilter), _strides(strides), _padding(padding)
{
}

void Conv2d::Initialize()
{
}

bool Conv2d::ValidateArrayFilter(const Array& arrayFilter)
{
	return true;
}

bool Conv2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	// _pArrayFwd1 = Img2dToCol(arrayFwdIn) .. (nSamples * nRowsFwdOut * nColsFwdOut, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd2 = _pArrayFilter.Reshape() .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd3 = _pArrayFilter.Reshape().Transpose2d() .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayFwd4 = _pArrayFwd1 |.| _pArrayFwd3 .. (nSamples * nRowsFwdOut * nColsFwdOut, nFilters)
	// _pArrayFwd5 = (_pArrayFwd1 |.| _pArrayFwd3).Reshape() .. (nSamples, nRowsFwdOut, nColsFwdOut, nFilters)
	// pArrayFwdOut = (_pArrayFwd1 |.| _pArrayFwd3).Reshape().TransposeMulti() .. (nSamples, nFilters, nRowsFwdOut, nColsFwdOut)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	if (dimSizesFilter.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	size_t nSamples = arrayFwdIn.GetDimSizes()[0];
	size_t nRowsFwdOut, nColsFwdOut;
	if (!Img2dToCol(_pArrayFwd1, arrayFwdIn, nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding, &nRowsFwdOut, &nColsFwdOut)) return false;
	_pArrayFilter->Reshape(_pArrayFwd2, DimSizes(nFilters, nChannels * nRowsFilter * nColsFilter));
	if (!_pArrayFwd2->Transpose2d(_pArrayFwd3)) return false;
	if (!Array::Dot(_pArrayFwd4, *_pArrayFwd1, *_pArrayFwd3)) return false;
	_pArrayFwd4->Reshape(_pArrayFwd5, DimSizes(nSamples, nRowsFwdOut, nColsFwdOut, nFilters));
	NumList<size_t> axes;
	axes.reserve(4);
	axes.push_back(0); axes.push_back(3); axes.push_back(1); axes.push_back(2);
	_pArrayFwd5->TransposeMulti(pArrayFwdOut, axes);
	_pArrayFwdInSaved.reset(arrayFwdIn.Reference()); // (nSamples, nChannels, nRowsFwdIn, nColsFwdIn)
	_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference()); // (nSamples, nFilters, nRowsFwdOut, nColsFwdOut)
	return true;
}

bool Conv2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	// _pArrayBwd1 = arrayBwdIn.TransposeMulti() .. (nSamples, nRowsBwdIn, nColsBwdIn, nFilters)
	// _pArrayBwd2 = _pArrayBwd1.Reshape() .. (nSamples * nRowsBwdIn * nColsBwdIn, nFilters)
	// _pArrayBwd3 = _pArrayFwd3.Transpose2d() .. (nChannels * nRowsFilter * nColsFilter, nSamples * nRowsFwdOut * nColsFwdOut)
	// _pArrayBwd4 = _pArrayBwd3 |.| _pArrayBwd2 .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayBwd5 = _pArrayBwd4.Transpose2d() .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayBwd6 = _pArrayBwd5.Rehape() .. (nFilters, nChannels, nRowsFilter, nColsFIlter)
	// _pArrayBwd7 = _pArrayBwd2 |.| _pArrayFwd2 .. (nSamples * nRowsBwdIn * nColsBwdIn, nChannels * nRowsFilter * nColsFilter)
	// pArrayBwdOut = ColToImg2d(_pArrayBwd7) .. (nSamples, nChannels, nRowsFwdIn, nColsFwdIn)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	const DimSizes& dimSizes = arrayBwdIn.GetDimSizes();
	size_t nSamples = dimSizes[0];
	size_t nRowsBwdIn = dimSizes[2], nColsBwdIn = dimSizes[3];
	NumList<size_t> axes;
	axes.reserve(4);
	axes.push_back(0); axes.push_back(2); axes.push_back(3); axes.push_back(1);
	arrayBwdIn.TransposeMulti(_pArrayBwd1, axes);
	_pArrayBwd1->Reshape(_pArrayBwd2, DimSizes(nSamples * nRowsBwdIn * nColsBwdIn, nFilters));
	_pArrayFwd1->Transpose2d(_pArrayBwd3);
	Array::Dot(_pArrayBwd4, *_pArrayBwd3, *_pArrayBwd2);
	_pArrayBwd4->Transpose2d(_pArrayBwd5);
	_pArrayBwd5->Reshape(_pArrayBwd6, DimSizes(nFilters, nChannels, nRowsFilter, nColsFilter));
	Array::Dot(_pArrayBwd7, *_pArrayBwd2, *_pArrayFwd2);
	if (!ColToImg2d(pArrayBwdOut, _pArrayFwdInSaved->GetDimSizes(), *_pArrayBwd7,
				nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding)) return false;
	return true;
}

String Conv2d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Conv2d");
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
