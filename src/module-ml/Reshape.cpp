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
	pArrayFwdOut.reset(arrayFwdIn.Reshape(*pValuesDimSize));
	if (!pArrayFwdOut) {
		pArrayFwdOut.reset(Array::Create(arrayFwdIn.GetElemType(), arrayFwdIn.GetDimSizes()));
		if (!pArrayFwdOut) return false;
		_pArrayFwdOutSaved.reset(pArrayFwdOut.Reference());
	}
	pArrayFwdOut
	return true;
}

bool Reshape::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, bool bwdPropagationFlag, const Array& arrayBwdIn)
{
	if (!bwdPropagationFlag) return true;
	if (!pArrayBwdOut) {
		pArrayBwdOut.reset(Array::Create(arrayBwdIn.GetElemType(), arrayBwdIn.GetDimSizes()));
		if (!pArrayBwdOut) return false;
	}
	return true;
}

String Reshape::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Reshape");
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
