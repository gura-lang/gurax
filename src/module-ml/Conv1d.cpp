//==============================================================================
// Conv1d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv1d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv1d_Forward_Array_T(void* pvRtn, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + ::exp(-*p));
	}
}

template<> void Conv1d_Forward_Array_T<Complex>(void* pvRtn, const void* pv, size_t len)
{
	using T_Elem = Complex;
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + std::exp(-*p));
	}
}

template<> void Conv1d_Forward_Array_T<Half>(void* pvRtn, const void* pv, size_t len)
{
}

template<typename T_Elem> void Conv1d_Backward_Array_T(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	const T_Elem* pFwd = reinterpret_cast<const T_Elem*>(pvFwd);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) {
		*pRtn = *p * (1. - *pFwd) * *pFwd;
	}
}

template<> void Conv1d_Backward_Array_T<Half>(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
}

std::function<void (void* pvDst, const void* pvSrc, size_t len)> Conv1d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (void* pvDst, const void* pvFwd, const void* pvSrc, size_t len)> Conv1d_Backward_Array[Array::ElemTypeIdMax];

void Conv1d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv1d_Forward_Array, Conv1d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv1d_Backward_Array, Conv1d_Backward_Array_T);
}

bool Conv1d::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Conv1d_Forward_Array[array.GetElemType().id](pvRtn, pv, len);
	return true;
}

bool Conv1d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	void* pvFwd = _pArrayFwd->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Conv1d_Backward_Array[array.GetElemType().id](pvRtn, pvFwd, pv, len);
	return true;
}

String Conv1d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Conv1d");
}

//------------------------------------------------------------------------------
// Conv1dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Conv1dOwner
//------------------------------------------------------------------------------
void Conv1dOwner::Clear()
{
	for (Conv1d* pConv1d : *this) Conv1d::Delete(pConv1d);
	clear();
}

Gurax_EndModuleScope(ml)
