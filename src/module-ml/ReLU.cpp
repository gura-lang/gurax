//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
template<typename T_Elem> void ReLU_Forward_Array_T(Array& arrayFwdOut, Array& arrayBoolSaved, const Array& arrayFwdIn)
{
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	Bool* pBoolSaved = arrayBoolSaved.GetPointerC<Bool>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++, pBoolSaved++) *pFwdOut = (*pBoolSaved = (*pFwdIn > 0))? *pFwdIn : 0;
}

template<typename T_Elem> void ReLU_Backward_Array_T(Array& arrayBwdOut, const Array& arrayBoolSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const Bool* pBoolSaved = arrayBoolSaved.GetPointerC<Bool>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pBoolSaved++) *pBwdOut = *pBoolSaved? *pBwdIn : 0;
}

std::function<void (Array& arrayFwdOut, Array& arrayBoolSaved, const Array& arrayFwdIn)> ReLU_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayBoolSaved, const Array& arrayBwdIn)> ReLU_Backward_Array[Array::ElemTypeIdMax];

void ReLU::Initialize()
{
	Gurax_SetArrayFuncSingle(ReLU_Forward_Array, ReLU_Forward_Array_T);
	Gurax_SetArrayFuncSingle(ReLU_Backward_Array, ReLU_Backward_Array_T);
}

bool ReLU::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag)
{
	if (!pArrayFwdOut) pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
	if (!pArrayFwdOut) return false;
	if (!_pArrayBoolSaved) _pArrayBoolSaved.reset(Array::Create(Array::ElemType::Bool, arrayFwdIn.GetDimSizes()));
	if (!_pArrayBoolSaved) return false;
	ReLU_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, *_pArrayBoolSaved, arrayFwdIn);
	return true;
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (!bwdPropagationFlag) return true;
	if (!pArrayBwdOut) pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
	if (!pArrayBwdOut) return false;
	ReLU_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayBoolSaved, arrayBwdIn);
	return true;
}

bool ReLU::Serialize(Stream& stream) const
{
	// nothing to do
	return true;
}

ReLU* ReLU::Deserialize(Stream& stream)
{
	return new ReLU();
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
