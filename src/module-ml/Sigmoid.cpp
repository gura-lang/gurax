//==============================================================================
// Sigmoid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Sigmoid
//------------------------------------------------------------------------------
template<typename T_Elem> void Sigmoid_Forward_Array_T(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) *pFwdOut = 1. / (1. + std::exp(-static_cast<Double>(*pFwdIn)));
}

template<> void Sigmoid_Forward_Array_T<Complex>(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	using T_Elem = Complex;
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) *pFwdOut = 1. / (1. + std::exp(-*pFwdIn));
}

template<typename T_Elem> void Sigmoid_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		Double fwdSaved = static_cast<Double>(*pFwdSaved);
		*pBwdOut = static_cast<Double>(*pBwdIn) * (1. - fwdSaved) * fwdSaved;
	}
}

template<> void Sigmoid_Backward_Array_T<Complex>(Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)
{
	using T_Elem = Complex;
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		const Complex& fwdSaved = *pFwdSaved;
		*pBwdOut = *pBwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn)> Sigmoid_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdSaved, const Array& arrayBwdIn)> Sigmoid_Backward_Array[Array::ElemTypeIdMax];

void Sigmoid::Initialize()
{
	Gurax_SetArrayFuncSingle(Sigmoid_Forward_Array, Sigmoid_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Sigmoid_Backward_Array, Sigmoid_Backward_Array_T);
}

bool Sigmoid::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdSaved.reset(pArrayFwdOut.Reference());
	}
	Sigmoid_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn);
	return true;
}

bool Sigmoid::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn)
{
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Sigmoid_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdSaved, arrayBwdIn);
	return true;
}

String Sigmoid::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Sigmoid");
}

//------------------------------------------------------------------------------
// SigmoidList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SigmoidOwner
//------------------------------------------------------------------------------
void SigmoidOwner::Clear()
{
	for (Sigmoid* pSigmoid : *this) Sigmoid::Delete(pSigmoid);
	clear();
}

Gurax_EndModuleScope(ml)
