//==============================================================================
// Sigmoid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Sigmoid
//------------------------------------------------------------------------------
template<typename T_Elem> void Sigmoid_Forward_Array_T(void* pvRtn, Bool* pBool, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) {
		*pRtn = (*pBool = (*p > 0))? *p : 0;
	}
}

template<typename T_Elem> void Sigmoid_Backward_Array_T(void* pvRtn, const Bool* pBool, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) {
		*pRtn = *pBool? *p : 0;
	}
}

std::function<void (void* pvDst, Bool* pBool, const void* pvSrc, size_t len)> Sigmoid_Forward_Array[Array::ElemTypeIdMax];
std::function<void (void* pvDst, const Bool* pBool, const void* pvSrc, size_t len)> Sigmoid_Backward_Array[Array::ElemTypeIdMax];

void Sigmoid::Initialize()
{
	Gurax_SetArrayFuncSingle(Sigmoid_Forward_Array, Sigmoid_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Sigmoid_Backward_Array, Sigmoid_Backward_Array_T);
}

bool Sigmoid::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	if (!_pArrayBool) _pArrayBool.reset(Array::Create(Array::ElemType::Bool, array.GetDimSizes()));
	if (!_pArrayBool) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	Bool* pBool = _pArrayBool->GetPointerC<Bool>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Sigmoid_Forward_Array[array.GetElemType().id](pvRtn, pBool, pv, len);
	return true;
}

bool Sigmoid::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	Bool* pBool = _pArrayBool->GetPointerC<Bool>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Sigmoid_Backward_Array[array.GetElemType().id](pvRtn, pBool, pv, len);
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
