//==============================================================================
// Conv3d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv3d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv3d_Forward_Array_T(Array& arrayRtn, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + ::exp(-*p));
}

template<> void Conv3d_Forward_Array_T<Complex>(Array& arrayRtn, const Array& array)
{
	using T_Elem = Complex;
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + std::exp(-*p));
}

template<> void Conv3d_Forward_Array_T<Half>(Array& arrayRtn, const Array& array)
{
}

template<typename T_Elem> void Conv3d_Backward_Array_T(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* pFwd = arrayFwd.GetPointerC<T_Elem>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) *pRtn = *p * (1. - *pFwd) * *pFwd;
}

template<> void Conv3d_Backward_Array_T<Half>(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
}

std::function<void (Array& arrayRtn, const Array& array)> Conv3d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayRtn, const Array& arrayFwd, const Array& array)> Conv3d_Backward_Array[Array::ElemTypeIdMax];

void Conv3d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv3d_Forward_Array, Conv3d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv3d_Backward_Array, Conv3d_Backward_Array_T);
}

bool Conv3d::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	Conv3d_Forward_Array[array.GetElemType().id](*pArrayRtn, array);
	return true;
}

bool Conv3d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
	}
	Conv3d_Backward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayFwd, array);
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
