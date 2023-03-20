//==============================================================================
// Bevel.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Bevel
//------------------------------------------------------------------------------
bool Bevel::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Bevel::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Bevel::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Bevel");
}

//------------------------------------------------------------------------------
// BevelList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BevelOwner
//------------------------------------------------------------------------------
void BevelOwner::Clear()
{
	for (Bevel* pBevel : *this) Bevel::Delete(pBevel);
	clear();
}

Gurax_EndModuleScope(model_obj)
