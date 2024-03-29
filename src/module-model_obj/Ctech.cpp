//==============================================================================
// Ctech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Ctech
//------------------------------------------------------------------------------
bool Ctech::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Ctech::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Ctech::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Ctech");
}

//------------------------------------------------------------------------------
// CtechList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CtechOwner
//------------------------------------------------------------------------------
void CtechOwner::Clear()
{
	for (Ctech* pCtech : *this) Ctech::Delete(pCtech);
	clear();
}

Gurax_EndModuleScope(model_obj)
