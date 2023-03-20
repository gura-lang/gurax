//==============================================================================
// Trim.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trim
//------------------------------------------------------------------------------
bool Trim::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Trim::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Trim::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Trim");
}

//------------------------------------------------------------------------------
// TrimList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrimOwner
//------------------------------------------------------------------------------
void TrimOwner::Clear()
{
	for (Trim* pTrim : *this) Trim::Delete(pTrim);
	clear();
}

Gurax_EndModuleScope(model_obj)
