//==============================================================================
// Deg.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Deg
//------------------------------------------------------------------------------
bool Deg::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Deg::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Deg::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Deg");
}

//------------------------------------------------------------------------------
// DegList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DegOwner
//------------------------------------------------------------------------------
void DegOwner::Clear()
{
	for (Deg* pDeg : *this) Deg::Delete(pDeg);
	clear();
}

Gurax_EndModuleScope(model_obj)
