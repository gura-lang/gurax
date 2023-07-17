//==============================================================================
// Dropout.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Dropout
//------------------------------------------------------------------------------
template<typename T_Elem> void Dropout_Forward_Array_T(Array& arrayFwdOut, Array& arrayBoolSaved, const Array& arrayFwdIn, Double rate)
{
	const T_Elem* pFwdIn = arrayFwdIn.GetPointerC<T_Elem>();
	const T_Elem* pFwdInEnd = pFwdIn + arrayFwdIn.GetDimSizes().CalcLength();
	T_Elem* pFwdOut = arrayFwdOut.GetPointerC<T_Elem>();
	Bool* pBoolSaved = arrayBoolSaved.GetPointerC<Bool>();
	for ( ; pFwdIn != pFwdInEnd; pFwdIn++, pFwdOut++, pBoolSaved++) {
		*pFwdOut = (*pBoolSaved = Random::Global().GenFloat<Double>() < rate)? 0 : *pFwdIn;
	}
}

template<typename T_Elem> void Dropout_Backward_Array_T(Array& arrayBwdOut, const Array& arrayBoolSaved, const Array& arrayBwdIn)
{
	const T_Elem* pBwdIn = arrayBwdIn.GetPointerC<T_Elem>();
	const T_Elem* pBwdInEnd = pBwdIn + arrayBwdIn.GetDimSizes().CalcLength();
	T_Elem* pBwdOut = arrayBwdOut.GetPointerC<T_Elem>();
	const Bool* pBoolSaved = arrayBoolSaved.GetPointerC<Bool>();
	for ( ; pBwdIn != pBwdInEnd; pBwdIn++, pBwdOut++, pBoolSaved++) *pBwdOut = *pBoolSaved? 0 : *pBwdIn;
}

std::function<void (Array& arrayFwdOut, Array& arrayBoolSaved, const Array& arrayFwdIn, Double rate)> Dropout_Forward_Array[Array::ElemTypeIdMax];
std::function<void (Array& arrayBwdOut, const Array& arrayBoolSaved, const Array& arrayBwdIn)> Dropout_Backward_Array[Array::ElemTypeIdMax];

void Dropout::Initialize()
{
	Gurax_SetArrayFuncSingle(Dropout_Forward_Array, Dropout_Forward_Array_T);
	Gurax_SetArrayFuncSingle(Dropout_Backward_Array, Dropout_Backward_Array_T);
}

bool Dropout::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller)
{
	if (!pArrayFwdOut) pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
	if (!pArrayFwdOut) return false;
	if (!_pArrayBoolSaved) _pArrayBoolSaved.reset(Array::Create(Array::ElemType::Bool, arrayFwdIn.GetDimSizes()));
	if (!_pArrayBoolSaved) return false;
	Dropout_Forward_Array[arrayFwdIn.GetElemType().id](*pArrayFwdOut, *_pArrayBoolSaved, arrayFwdIn, _rate);
	return true;
}

bool Dropout::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (!bwdPropagationFlag) return true;
	if (!pArrayBwdOut) pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
	if (!pArrayBwdOut) return false;
	Dropout_Backward_Array[arrayBwdIn.GetElemType().id](*pArrayBwdOut, *_pArrayBoolSaved, arrayBwdIn);
	return true;
}

bool Dropout::Serialize(Stream& stream) const
{
	stream.SerializeNumber<Double>(_rate);
	return true;
}

Dropout* Dropout::Deserialize(Stream& stream)
{
	Double rate;
	if (!stream.DeserializeNumber<Double>(rate)) return nullptr;
	return new Dropout(rate);
}

String Dropout::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Dropout:rate=%g", _rate);
}

//------------------------------------------------------------------------------
// DropoutList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DropoutOwner
//------------------------------------------------------------------------------
void DropoutOwner::Clear()
{
	for (Dropout* pDropout : *this) Dropout::Delete(pDropout);
	clear();
}

Gurax_EndModuleScope(ml)
