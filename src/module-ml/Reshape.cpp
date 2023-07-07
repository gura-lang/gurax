//==============================================================================
// Reshape.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Reshape
//------------------------------------------------------------------------------
bool Reshape::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, bool trainingFlag)
{
	_pArrayFwdInSaved.reset(arrayFwdIn.Reference());
	return arrayFwdIn.Reshape(pArrayFwdOut, *_pValuesDimSize);
}

bool Reshape::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (!bwdPropagationFlag) return true;
	arrayBwdIn.Reshape(pArrayBwdOut, _pArrayFwdInSaved->GetDimSizes());
	return true;
}

bool Reshape::Serialize(Stream& stream) const
{
	if (!_pValuesDimSize->Serialize(stream)) return false;
	return true;
}

Reshape* Reshape::Deserialize(Stream& stream)
{
	RefPtr<ValueOwner> pValuesDimSize(ValueOwner::Deserialize(stream));
	return pValuesDimSize? new Reshape(pValuesDimSize.release()) : nullptr;
}

String Reshape::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Reshape:%s", _pValuesDimSize->ToString(StringStyle::Cram).c_str());
}

//------------------------------------------------------------------------------
// ReshapeList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ReshapeOwner
//------------------------------------------------------------------------------
void ReshapeOwner::Clear()
{
	for (Reshape* pReshape : *this) Reshape::Delete(pReshape);
	clear();
}

Gurax_EndModuleScope(ml)
