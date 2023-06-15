//==============================================================================
// Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv2d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv2d_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		const T_Elem& fwdIn = *pFwdIn;
		*pFwdOut = 1. / (1. + std::exp(-fwdIn));
	}
}

template<> void Conv2d_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	using T_Elem = Complex;
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		Float fwdIn = static_cast<Float>(*pFwdIn);
		*pFwdOut = 1. / (1. + std::exp(-fwdIn));
	}
}

template<typename T_Elem> void Conv2d_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		const T_Elem& bwdIn = *pBwdIn;
		const T_Elem& fwdSaved = *pFwdSaved;
		*pBwdOut = bwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

template<> void Conv2d_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	using T_Elem = Half;
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		Float bwdIn = static_cast<Float>(*pBwdIn);
		Float fwdSaved = static_cast<Float>(*pFwdSaved);
		*pBwdOut = bwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn)> Conv2d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)> Conv2d_Backward_Array[Array::ElemTypeIdMax];

Conv2d::Conv2d(Array* pArrayFilter, size_t padding, size_t strides) : _pArrayFilter(pArrayFilter), _padding(padding), _strides(strides)
{
}

void Conv2d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv2d_Forward_Array, Conv2d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv2d_Backward_Array, Conv2d_Backward_Array_T);
}

bool Conv2d::ValidateArrayFilter(const Array& arrayFilter)
{
	return true;
}

bool Conv2d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
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

bool Conv2d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Conv2d_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdSaved, arrayBwdIn);
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
