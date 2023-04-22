//==============================================================================
// Sigmoid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Sigmoid
//------------------------------------------------------------------------------
template<typename T_Elem> void Sigmoid_Forward_Array_T(Array& arrayRtn, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + ::exp(-*p));
}

template<> void Sigmoid_Forward_Array_T<Complex>(Array& arrayRtn, const Array& array)
{
	using T_Elem = Complex;
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + std::exp(-*p));
}

template<> void Sigmoid_Forward_Array_T<Half>(Array& arrayRtn, const Array& array)
{
}

template<typename T_Elem> void Sigmoid_Backward_Array_T(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* pFwd = arrayFwd.GetPointerC<T_Elem>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) *pRtn = *p * (1. - *pFwd) * *pFwd;
}

template<> void Sigmoid_Backward_Array_T<Half>(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
}

std::function<void (Array& arrayRtn, const Array& array)> Sigmoid_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayRtn, const Array& arrayFwd, const Array& array)> Sigmoid_Backward_Array[Array::ElemTypeIdMax];

void Sigmoid::Initialize()
{
	Gurax_SetArrayFuncSingle(Sigmoid_Forward_Array, Sigmoid_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Sigmoid_Backward_Array, Sigmoid_Backward_Array_T);
}

bool Sigmoid::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	Sigmoid_Forward_Array[array.GetElemType().id](*pArrayRtn, array);
	return true;
}

bool Sigmoid::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
	}
	Sigmoid_Backward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayFwd, array);
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
