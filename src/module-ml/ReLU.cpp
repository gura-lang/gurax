//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
template<typename T_Elem> void ReLU_Array_T(void* pvRtn, Bool* pBool, const void* pv, size_t len)
{
	::printf("check\n");
	Bool* pRtn = reinterpret_cast<Bool*>(pvRtn);
	Bool* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pBool++) {
		*pRtn = (*pBool = (*p > 0))? *pRtn : 0;
	}
}

std::function<void (void* pvDst, Bool* pBool, const void* pvSrc, size_t len)> ReLU_Array[Array::ElemTypeIdMax];

void ReLU::Initialize()
{
	Gurax_SetArrayFuncSingle(ReLU_Array, ReLU_Array_T);
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
	ReLU_Array[array.GetElemType().id](pvRtn, pBool, pv, len);
	return true;
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	return Array::Mul(pArrayRtn, *_pArrayBool, array);
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
