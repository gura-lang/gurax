//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
template<typename T_Elem> void ReLU_Array_T(void* pvRtn, const void* pv, size_t len)
{
	Bool* pRtn = reinterpret_cast<Bool*>(pvRtn);
	Bool* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		//*pRtn = -static_cast<T_Elem>(static_cast<T_Elem>(*p));
	}
}

std::function<void (void* pvDst, const void* pvSrc, size_t len)> ReLU_Array[Array::ElemTypeIdMax];

void ReLU::Initialize()
{
	Gurax_SetArrayFuncSingle(ReLU_Array, ReLU_Array_T);
}

bool ReLU::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	return Array::GenericUnaryOp(pArrayRtn, Array::ElemType::Bool, array, ReLU_Array[array.GetElemType().id]);
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	return false;
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
