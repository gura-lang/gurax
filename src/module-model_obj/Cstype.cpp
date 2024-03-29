//==============================================================================
// Cstype.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Cstype
//------------------------------------------------------------------------------
bool Cstype::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Cstype::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Cstype::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Cstype");
}

//------------------------------------------------------------------------------
// CstypeList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CstypeOwner
//------------------------------------------------------------------------------
void CstypeOwner::Clear()
{
	for (Cstype* pCstype : *this) Cstype::Delete(pCstype);
	clear();
}

Gurax_EndModuleScope(model_obj)
