//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
template<typename T_Elem> void ReLU_Forward_Array_T(void* pvRtn, Bool* pBool, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) {
		*pRtn = (*pBool = (*p > 0))? *p : 0;
	}
}

template<typename T_Elem> void ReLU_Backward_Array_T(void* pvRtn, const Bool* pBool, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) {
		*pRtn = *pBool? *p : 0;
	}
}

std::function<void (void* pvDst, Bool* pBool, const void* pvSrc, size_t len)> ReLU_Forward_Array[Array::ElemTypeIdMax];
std::function<void (void* pvDst, const Bool* pBool, const void* pvSrc, size_t len)> ReLU_Backward_Array[Array::ElemTypeIdMax];

void ReLU::Initialize()
{
	Gurax_SetArrayFuncSingle(ReLU_Forward_Array, ReLU_Forward_Array_T);
	Gurax_SetArrayFuncSingle(ReLU_Backward_Array, ReLU_Backward_Array_T);
}

bool ReLU::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	if (!_pArrayBool) _pArrayBool.reset(Array::Create(Array::ElemType::Bool, array.GetDimSizes()));
	if (!_pArrayBool) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	Bool* pBool = _pArrayBool->GetPointerC<Bool>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	ReLU_Forward_Array[array.GetElemType().id](pvRtn, pBool, pv, len);
	return true;
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	//return Array::Mul(pArrayRtn, *_pArrayBool, array);
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	Bool* pBool = _pArrayBool->GetPointerC<Bool>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	ReLU_Backward_Array[array.GetElemType().id](pvRtn, pBool, pv, len);
	return true;
}

String ReLU::ToString(const StringStyle& ss) const
{
	return String().Format("ml.ReLU");
}

//------------------------------------------------------------------------------
// ReLUList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ReLUOwner
//------------------------------------------------------------------------------
void ReLUOwner::Clear()
{
	for (ReLU* pReLU : *this) ReLU::Delete(pReLU);
	clear();
}

Gurax_EndModuleScope(ml)
