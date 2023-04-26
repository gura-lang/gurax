//==============================================================================
// Tanh.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Tanh
//------------------------------------------------------------------------------
template<typename T_Elem> void Tanh_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	// arrayFwdOut = tanh(arrayFwdIn)
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		const T_Elem& fwdIn = *pFwdIn;
		*pFwdOut = std::tanh(fwdIn);
	}
}

template<> void Tanh_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	// arrayFwdOut = tanh(arrayFwdIn)
	using T_Elem = Complex;
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		Float fwdIn = static_cast<Float>(*pFwdIn);
		*pFwdOut = std::tanh(fwdIn);
	}
}

template<typename T_Elem> void Tanh_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	// arrayBwdOut = arrayBwdIn * (1 - arrayFwdSaved ** 2)
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		const T_Elem& bwdIn = *pBwdIn;
		const T_Elem& fwdSaved = *pFwdSaved;
		*pBwdOut = bwdIn * (1. - fwdSaved * fwdSaved);
	}
}

template<> void Tanh_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	// arrayBwdOut = arrayBwdIn * (1 - arrayFwdSaved ** 2)
	using T_Elem = Half;
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		Float bwdIn = static_cast<Float>(*pBwdIn);
		Float fwdSaved = static_cast<Float>(*pFwdSaved);
		*pBwdOut = bwdIn * (1. - fwdSaved * fwdSaved);
	}
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn)> Tanh_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)> Tanh_Backward_Array[Array::ElemTypeIdMax];

void Tanh::Initialize()
{
	Gurax_SetArrayFuncSingle(Tanh_Forward_Array, Tanh_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Tanh_Backward_Array, Tanh_Backward_Array_T);
}

bool Tanh::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	}
	Tanh_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn);
	return true;
}

bool Tanh::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Tanh_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdSaved, arrayBwdIn);
	return true;
}

String Tanh::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Tanh");
}

//------------------------------------------------------------------------------
// TanhList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TanhOwner
//------------------------------------------------------------------------------
void TanhOwner::Clear()
{
	for (Tanh* pTanh : *this) Tanh::Delete(pTanh);
	clear();
}

Gurax_EndModuleScope(ml)
