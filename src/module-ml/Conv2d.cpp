//==============================================================================
// Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv2d
//------------------------------------------------------------------------------
Conv2d::Conv2d(Array* pArrayFilter, size_t padding, size_t strides) : _pArrayFilter(pArrayFilter), _padding(padding), _strides(strides)
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
	// _pArrayWork1 .. (nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter)
	// _pArrayWork2 .. (nFilters, nChannels * nRowsFilter * nColsFilter)
	// _pArrayWork3 .. (nChannels * nRowsFilter * nColsFilter, nFilters)
	// _pArrayWork4 .. (nSamples * nRowsOut * nColsOut, nFilters)
	// _pArrayWork5 .. (nSamples, nRowsOut, nColsOut, nFilters)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	size_t nSamples = arrayFwdIn.GetDimSizes()[0];
	size_t nRowsOut, nColsOut;
	Img2dToCol(_pArrayWork1, arrayFwdIn, nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding, &nRowsOut, &nColsOut);
	_pArrayFilter->Reshape(_pArrayWork2, DimSizes(nFilters, nChannels * nRowsFilter * nColsFilter));
	if (!_pArrayWork2->Transpose2d(_pArrayWork3)) return false;
	Array::Mul(_pArrayWork4, *_pArrayWork1, *_pArrayWork3);
	_pArrayWork4->Reshape(_pArrayWork5, DimSizes(nSamples, nRowsOut, nColsOut, nFilters));
	NumList<size_t> axes;
	axes.reserve(4);
	axes.push_back(0); axes.push_back(3); axes.push_back(1); axes.push_back(2);
	_pArrayWork5->TransposeMulti(pArrayFwdOut, axes); // (nSamples, nFilters, nRowsOut, nColsOut)
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
