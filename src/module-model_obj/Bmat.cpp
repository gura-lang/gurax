//==============================================================================
// Bmat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Bmat
//------------------------------------------------------------------------------
bool Bmat::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Bmat::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Bmat::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Bmat");
}

//------------------------------------------------------------------------------
// BmatList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BmatOwner
//------------------------------------------------------------------------------
void BmatOwner::Clear()
{
	for (Bmat* pBmat : *this) Bmat::Delete(pBmat);
	clear();
}

Gurax_EndModuleScope(model_obj)
