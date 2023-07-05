//==============================================================================
// Reshape.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Reshape
//------------------------------------------------------------------------------
bool Reshape::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn)
{
	_pArrayFwdInSaved.reset(arrayFwdIn.Reference());
	return arrayFwdIn.Reshape(pArrayFwdOut, *_pValuesDimSize);
}

bool Reshape::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& arrayBwdIn)
{
	if (!bwdPropagationFlag) return true;
	arrayBwdIn.Reshape(pArrayBwdOut, _pArrayFwdInSaved->GetDimSizes());
	return true;
}

bool Reshape::Serialize(Stream& stream) const
{
	return false;
}

Reshape* Reshape::Deserialize(Stream& stream)
{
	return nullptr;
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
