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
	// _pArrayFwd1 = Img2dToCol(arrayFwdIn) .. (nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd2 = _pArrayFilter.Reshape() .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayFwd3 = _pArrayFilter.Reshape().Transpose2d() .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayFwd4 = _pArrayFwd1 |.| _pArrayFwd3 .. (nSamples * nRowsOut * nColsOut, nFilters)
	// _pArrayFwd5 = (_pArrayFwd1 |.| _pArrayFwd3).Reshape() .. (nSamples, nRowsOut, nColsOut, nFilters)
	// pArrayFwdOut = (_pArrayFwd1 |.| _pArrayFwd3).Reshape().Transpose() .. (nSamples, nFilters, nRowsOut, nColsOut)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	if (dimSizesFilter.size() != 4) {
		Error::Issue(ErrorType::SizeError, "the array must have four dimensions");
		return false;
	}
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	size_t nSamples = arrayFwdIn.GetDimSizes()[0];
	size_t nRowsOut, nColsOut;
	if (!Img2dToCol(_pArrayFwd1, arrayFwdIn, nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding, &nRowsOut, &nColsOut)) return false;
	_pArrayFilter->Reshape(_pArrayFwd2, DimSizes(nFilters, nChannels * nRowsFilter * nColsFilter));
	if (!_pArrayFwd2->Transpose2d(_pArrayFwd3)) return false;
	if (!Array::Dot(_pArrayFwd4, *_pArrayFwd1, *_pArrayFwd3)) return false;
	_pArrayFwd4->Reshape(_pArrayFwd5, DimSizes(nSamples, nRowsOut, nColsOut, nFilters));
	NumList<size_t> axes;
	axes.reserve(4);
	axes.push_back(0); axes.push_back(3); axes.push_back(1); axes.push_back(2);
	_pArrayFwd5->TransposeMulti(pArrayFwdOut, axes);
	_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	return true;
}

bool Conv2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
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
