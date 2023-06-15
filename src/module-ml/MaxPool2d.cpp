//==============================================================================
// MaxPool2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// MaxPool2d
//------------------------------------------------------------------------------
MaxPool2d::MaxPool2d(Array* pArrayFilter, size_t padding, size_t strides) : _pArrayFilter(pArrayFilter), _padding(padding), _strides(strides)
{
}

void MaxPool2d::Initialize()
{
}

bool MaxPool2d::ValidateArrayFilter(const Array& arrayFilter)
{
	return true;
}

bool MaxPool2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	}
	RefPtr<Array> pArrayExp; // (nSamples * nRowsOut * nColsOut, nChannels * nRowsFilter * nColsFilter)
	const DimSizes& dimSizesFilter = _pArrayFilter->GetDimSizes();
	size_t nFilters = dimSizesFilter[0], nChannels = dimSizesFilter[1];
	size_t nRowsFilter = dimSizesFilter[2], nColsFilter = dimSizesFilter[3];
	size_t nRowsOut, nColsOut;
	Img2dToCol(pArrayExp, arrayFwdIn, nRowsFilter, nColsFilter, _strides, _strides, _padding, _padding, &nRowsOut, &nColsOut);
	DimSizes dimSizes;
	dimSizes.push_back(nFilters);
	dimSizes.push_back(nChannels * nRowsFilter * nColsFilter);
	RefPtr<Array> pArrayFilterReshaped(_pArrayFilter->Reshape(dimSizes));
	RefPtr<Array> pArrayFilterReshapedT; // (nChannels * nRowsFilter * nColsFilter, nFilters)
	if (!pArrayFilterReshaped->Transpose2d(pArrayFilterReshapedT)) return false;
	RefPtr<Array> pArrayFwdOutExp; // (nSamples * nRowsOut * nColsOut, nFilters)
	Array::Mul(pArrayFwdOutExp, *pArrayExp, *pArrayFilterReshapedT);
	// (nSamples, nFilters, nRowsOut, nColsOut)
	return true;
}

bool MaxPool2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	return true;
}

String MaxPool2d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.MaxPool2d");
}

//------------------------------------------------------------------------------
// MaxPool2dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MaxPool2dOwner
//------------------------------------------------------------------------------
void MaxPool2dOwner::Clear()
{
	for (MaxPool2d* pMaxPool2d : *this) MaxPool2d::Delete(pMaxPool2d);
	clear();
}

Gurax_EndModuleScope(ml)
