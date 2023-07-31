//==============================================================================
// Flatten.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Flatten
//------------------------------------------------------------------------------
bool Flatten::EvalForward(Processor& processor, RefPtr<Array>& pArrayFwdOut, const Array& arrayFwdIn, const Controller& controller)
{
	if (!_pArrayFwdInSaved) {
		_pArrayFwdInSaved.reset(arrayFwdIn.Reference());
		if (!arrayFwdIn.GetDimSizes().Flatten(_dimSizes, *_pValuesNDim)) {
			return false;
		}
	}
	arrayFwdIn.Reshape(pArrayFwdOut, _dimSizes);
	return true;
}

bool Flatten::EvalBackward(Processor& processor, RefPtr<Array>& pArrayBwdOut, const Array& arrayBwdIn, bool bwdPropagationFlag)
{
	if (!bwdPropagationFlag) return true;
	arrayBwdIn.Reshape(pArrayBwdOut, _pArrayFwdInSaved->GetDimSizes());
	return true;
}

bool Flatten::Serialize(Stream& stream) const
{
	if (!_pValuesNDim->Serialize(stream)) return false;
	return true;
}

Flatten* Flatten::Deserialize(Stream& stream)
{
	RefPtr<ValueOwner> pValuesDimSize(ValueOwner::Deserialize(stream));
	return pValuesDimSize? new Flatten(pValuesDimSize.release()) : nullptr;
}

String Flatten::ToString(const StringStyle& ss) const
{
	return String().Format("ml.Flatten:%s", _pValuesNDim->ToString(StringStyle::Cram).c_str());
}

//------------------------------------------------------------------------------
// FlattenList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FlattenOwner
//------------------------------------------------------------------------------
void FlattenOwner::Clear()
{
	for (Flatten* pFlatten : *this) Flatten::Delete(pFlatten);
	clear();
}

Gurax_EndModuleScope(ml)
