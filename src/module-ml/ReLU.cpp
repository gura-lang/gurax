//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
template<typename T_Elem> void ReLU_Forward_Array_T(Array& arrayRtn, Array& arrayBool, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	Bool* pBool = arrayBool.GetPointerC<Bool>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) *pRtn = (*pBool = (*p > 0))? *p : 0;
}

template<typename T_Elem> void ReLU_Backward_Array_T(Array& arrayRtn, const Array& arrayBool, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	const Bool* pBool = arrayBool.GetPointerC<Bool>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) *pRtn = *pBool? *p : 0;
}

std::function<void (Array& arrayRtn, Array& arrayBool, const Array& array)> ReLU_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayRtn, const Array& arrayBool, const Array& array)> ReLU_Backward_Array[Array::ElemTypeIdMax];

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
	ReLU_Forward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayBool, array);
	return true;
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	ReLU_Backward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayBool, array);
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
