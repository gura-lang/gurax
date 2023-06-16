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
	//if (!pArrayFwdOut) {
	//	pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
	//	if (!pArrayFwdOut) return false;
	//	_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	//}
	RefPtr<Array> pArrayWork1; // (nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	size_t nSamples = arrayFwdIn.GetDimSizes()[0];
	size_t nRowsOut, nColsOut;
	Img2dToCol(pArrayWork1, arrayFwdIn, nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding, &nRowsOut, &nColsOut);
	RefPtr<Array> pArrayWork2(_pArrayFilter->Reshape(DimSizes(nFilters, nChannels * nRowsFilter * nColsFilter)));
	RefPtr<Array> pArrayWork3; // (nChannels * nRowsFilter * nColsFilter, nFilters)
	if (!pArrayWork2->Transpose2d(pArrayWork3)) return false;

	RefPtr<Array> pArrayWork4; // (nSamples * nRowsOut * nColsOut, nFilters)
	Array::Mul(pArrayWork4, *pArrayWork1, *pArrayWork3);
	RefPtr<Array> pArrayWork5(pArrayWork4->Reshape(DimSizes(nSamples, nRowsOut, nColsOut, nFilters))); // (nSamples, nRowsOut, nColsOut, nFilters)
	// (nSamples, nFilters, nRowsOut, nColsOut)
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
