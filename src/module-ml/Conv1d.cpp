//==============================================================================
// Conv1d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv1d
//------------------------------------------------------------------------------
template<typename T_Elem> void Conv1d_Forward_Array_T(Array& arrayRtn, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + ::exp(-*p));
}

template<> void Conv1d_Forward_Array_T<Complex>(Array& arrayRtn, const Array& array)
{
	using T_Elem = Complex;
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	for ( ; pRtn != pRtnEnd; pRtn++, p++) *pRtn = 1. / (1. + std::exp(-*p));
}

template<> void Conv1d_Forward_Array_T<Half>(Array& arrayRtn, const Array& array)
{
}

template<typename T_Elem> void Conv1d_Backward_Array_T(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
	const T_Elem* p = array.GetPointerC<T_Elem>();
	size_t len = array.GetDimSizes().CalcLength();
	T_Elem* pRtn = arrayRtn.GetPointerC<T_Elem>();
	T_Elem* pRtnEnd = pRtn + len;
	const T_Elem* pFwd = arrayFwd.GetPointerC<T_Elem>();
	for ( ; pRtn != pRtnEnd; pRtn++, p++, pFwd++) *pRtn = *p * (1. - *pFwd) * *pFwd;
}

template<> void Conv1d_Backward_Array_T<Half>(Array& arrayRtn, const Array& arrayFwd, const Array& array)
{
}

std::function<void (Array& arrayRtn, const Array& array)> Conv1d_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayRtn, const Array& arrayFwd, const Array& array)> Conv1d_Backward_Array[Array::ElemTypeIdMax];

void Conv1d::Initialize()
{
	Gurax_SetArrayFuncSingle(Conv1d_Forward_Array, Conv1d_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Conv1d_Backward_Array, Conv1d_Backward_Array_T);
}

bool Conv1d::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
		_pArrayFwd.reset(pArrayRtn.Reference());
	}
	Conv1d_Forward_Array[array.GetElemType().id](*pArrayRtn, array);
	return true;
}

bool Conv1d::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	if (!pArrayRtn) {
		pArrayRtn.reset(Array::Create(array.GetElemType(), array.GetDimSizes()));
		if (!pArrayRtn) return false;
	}
	Conv1d_Backward_Array[array.GetElemType().id](*pArrayRtn, *_pArrayFwd, array);
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
