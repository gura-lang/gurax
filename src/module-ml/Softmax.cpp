//==============================================================================
// Softmax.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Softmax
//------------------------------------------------------------------------------
template<typename T_Elem> void Softmax_Forward_Array_T(void* pvRtn, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + ::exp(-*p));
	}
}

template<> void Softmax_Forward_Array_T<Complex>(void* pvRtn, const void* pv, size_t len)
{
	using T_Elem = Complex;
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + std::exp(-*p));
	}
}

template<> void Softmax_Forward_Array_T<Half>(void* pvRtn, const void* pv, size_t len)
{
}

template<typename T_Elem> void Softmax_Backward_Array_T(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	const T_Elem* pFwd = reinterpret_cast<const T_Elem*>(pvFwd);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) {
		*pRtn = *p * (1. - *pFwd) * *pFwd;
	}
}

template<> void Softmax_Backward_Array_T<Half>(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
}

std::function<void (void* pvDst, const void* pvSrc, size_t len)> Softmax_Forward_Array[Array::ElemTypeIdMax];
std::function<void (void* pvDst, const void* pvFwd, const void* pvSrc, size_t len)> Softmax_Backward_Array[Array::ElemTypeIdMax];

void Softmax::Initialize()
{
	Gurax_SetArrayFuncSingle(Softmax_Forward_Array, Softmax_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Softmax_Backward_Array, Softmax_Backward_Array_T);
}

bool Softmax::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Softmax_Forward_Array[array.GetElemType().id](pvRtn, pv, len);
	return true;
}

bool Softmax::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	void* pvFwd = _pArrayFwd->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Softmax_Backward_Array[array.GetElemType().id](pvRtn, pvFwd, pv, len);
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
