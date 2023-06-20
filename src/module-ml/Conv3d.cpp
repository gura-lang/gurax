//==============================================================================
// Conv3d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv3d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv3d_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		const T_Elem& fwdIn = *pFwdIn;
		*pFwdOut = 1. / (1. + std::exp(-fwdIn));
	}
}

template<> void Conv3d_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn)
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

template<typename T_Elem> void Conv3d_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
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

template<> void Conv3d_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
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

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn)> Conv3d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)> Conv3d_Backward_Array[Array::ElemTypeIdMax];

void Conv3d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv3d_Forward_Array, Conv3d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv3d_Backward_Array, Conv3d_Backward_Array_T);
}

bool Conv3d::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	}
	Conv3d_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn);
	return true;
}

bool Conv3d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Conv3d_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdOutSaved, arrayBwdIn);
	return true;
}

String Conv3d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Conv3d");
}

//------------------------------------------------------------------------------
// Conv3dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Conv3dOwner
//------------------------------------------------------------------------------
void Conv3dOwner::Clear()
{
	for (Conv3d* pConv3d : *this) Conv3d::Delete(pConv3d);
	clear();
}

Gurax_EndModuleScope(ml)
