//==============================================================================
// Conv3d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv3d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv3d_Forward_Array_T(void* pvRtn, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + ::exp(-*p));
	}
}

template<> void Conv3d_Forward_Array_T<Complex>(void* pvRtn, const void* pv, size_t len)
{
	using T_Elem = Complex;
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++) {
		*pRtn = 1. / (1. + std::exp(-*p));
	}
}

template<> void Conv3d_Forward_Array_T<Half>(void* pvRtn, const void* pv, size_t len)
{
}

template<typename T_Elem> void Conv3d_Backward_Array_T(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
	T_Elem* pRtn = reinterpret_cast<T_Elem*>(pvRtn);
	const T_Elem* pFwd = reinterpret_cast<const T_Elem*>(pvFwd);
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv);
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) {
		*pRtn = *p * (1. - *pFwd) * *pFwd;
	}
}

template<> void Conv3d_Backward_Array_T<Half>(void* pvRtn, const void* pvFwd, const void* pv, size_t len)
{
}

std::function<void (void* pvDst, const void* pvSrc, size_t len)> Conv3d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (void* pvDst, const void* pvFwd, const void* pvSrc, size_t len)> Conv3d_Backward_Array[Array::ElemTypeIdMax];

void Conv3d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv3d_Forward_Array, Conv3d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv3d_Backward_Array, Conv3d_Backward_Array_T);
}

bool Conv3d::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Conv3d_Forward_Array[array.GetElemType().id](pvRtn, pv, len);
	return true;
}

bool Conv3d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
	if (!pArrayRtn) return false;
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	void* pvFwd = _pArrayFwd->GetPointerC<void>();
	const void* pv = array.GetPointerC<void>();
	size_t len = array.GetDimSizes().CalcLength();
	Conv3d_Backward_Array[array.GetElemType().id](pvRtn, pvFwd, pv, len);
	return true;
}

String Conv3d::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Conv3d");
}

//------------------------------------------------------------------------------
// Conv3dList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Conv3dOwner
//------------------------------------------------------------------------------
void Conv3dOwner::Clear()
{
	for (Conv3d* pConv3d : *this) Conv3d::Delete(pConv3d);
	clear();
}

Gurax_EndModuleScope(ml)
