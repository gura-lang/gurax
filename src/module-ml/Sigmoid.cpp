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
	// arrayFwdOUt = 1 / (1 + exp(-arrayFwdIn))
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		const T_Elem& fwdIn = *pFwdIn;
		*pFwdOut = 1. / (1. + std::exp(-fwdIn));
	}
}

template<> void Sigmoid_Forward_Array_T<Half>(Array& arrayFwdOut, const Array& arrayFwdIn)
{
	// arrayFwdOUt = 1 / (1 + exp(-arrayFwdIn))
	using T_Elem = Complex;
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++) {
		Float fwdIn = static_cast<Float>(*pFwdIn);
		*pFwdOut = 1. / (1. + std::exp(-fwdIn));
	}
}

template<typename T_Elem> void Sigmoid_Backward_Array_T(Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)
{
	// arrayBwdOUt = arrayBwdIn / (1 - arrayFwdOutSaved) * arrayFwdOutSaved
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdOutSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		const T_Elem& bwdIn = *pBwdIn;
		const T_Elem& fwdSaved = *pFwdSaved;
		*pBwdOut = bwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

template<> void Sigmoid_Backward_Array_T<Half>(Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)
{
	// arrayBwdOUt = arrayBwdIn / (1 - arrayFwdOutSaved) * arrayFwdOutSaved
	using T_Elem = Half;
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const T_Elem* pFwdSaved = arrayFwdOutSaved.GetPointerC<T_Elem>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pFwdSaved++) {
		Float bwdIn = static_cast<Float>(*pBwdIn);
		Float fwdSaved = static_cast<Float>(*pFwdSaved);
		*pBwdOut = bwdIn * (1. - fwdSaved) * fwdSaved;
	}
}

std::function<void (Array& arrayFwdOut, const Array& arrayFwdIn)> Sigmoid_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayFwdOutSaved, const Array& arrayBwdIn)> Sigmoid_Backward_Array[Array::ElemTypeIdMax];

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
		_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	}
	Sigmoid_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, arrayFwdIn);
	return true;
}

bool Sigmoid::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& arrayBwdIn)
{
	if (!bwdPropagationFlag) return true;
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	Sigmoid_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayFwdOutSaved, arrayBwdIn);
	return true;
}

bool Sigmoid::Serialize(Stream& stream) const
{
	// nothing to do
	return true;
}

Sigmoid* Sigmoid::Deserialize(Stream& stream)
{
	return new Sigmoid();
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
