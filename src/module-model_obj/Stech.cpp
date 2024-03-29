//==============================================================================
// Stech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Stech
//------------------------------------------------------------------------------
bool Stech::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Stech::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Stech::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Stech");
}

//------------------------------------------------------------------------------
// StechList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StechOwner
//------------------------------------------------------------------------------
void StechOwner::Clear()
{
	for (Stech* pStech : *this) Stech::Delete(pStech);
	clear();
}

Gurax_EndModuleScope(model_obj)
