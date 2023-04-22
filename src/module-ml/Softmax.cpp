//==============================================================================
// Softmax.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Softmax
//------------------------------------------------------------------------------
template<typename T_Elem> void Softmax_Forward_Array_T(Array& arrayRtn, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + ::exp(-*p));
}

template<> void Softmax_Forward_Array_T<Complex>(Array& arrayRtn, const Array& array)
{
	using T_Elem = Complex;
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + std::exp(-*p));
}

template<> void Softmax_Forward_Array_T<Half>(Array& arrayRtn, const Array& array)
{
}

template<typename T_Elem> void Softmax_Backward_Array_T(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* pFwd = arrayFwd.GetPointerC<T_Elem>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) *pRtn = *p * (1. - *pFwd) * *pFwd;
}

template<> void Softmax_Backward_Array_T<Half>(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
}

std::function<void (Array& arrayRtn, const Array& array)> Softmax_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayRtn, const Array& arrayFwd, const Array& array)> Softmax_Backward_Array[Array::ElemTypeIdMax];

void Softmax::Initialize()
{
	Gurax_SetArrayFuncSingle(Softmax_Forward_Array, Softmax_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Softmax_Backward_Array, Softmax_Backward_Array_T);
}

bool Softmax::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	Softmax_Forward_Array[array.GetElemType().id](*pArrayRtn, array);
	return true;
}

bool Softmax::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
	}
	Softmax_Backward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayFwd, array);
	return true;
}

String Softmax::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Softmax");
}

//------------------------------------------------------------------------------
// SoftmaxList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SoftmaxOwner
//------------------------------------------------------------------------------
void SoftmaxOwner::Clear()
{
	for (Softmax* pSoftmax : *this) Softmax::Delete(pSoftmax);
	clear();
}

Gurax_EndModuleScope(ml)
