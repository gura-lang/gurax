//==============================================================================
// Spoint.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Spoint
//------------------------------------------------------------------------------
bool Spoint::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Spoint::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Spoint::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Spoint");
}

//------------------------------------------------------------------------------
// SpointList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SpointOwner
//------------------------------------------------------------------------------
void SpointOwner::Clear()
{
	for (Spoint* pSpoint : *this) Spoint::Delete(pSpoint);
	clear();
}

Gurax_EndModuleScope(model_obj)
