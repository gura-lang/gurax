//==============================================================================
// Curv2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv2
//------------------------------------------------------------------------------
bool Curv2::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Curv2::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Curv2::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Curv2");
}

//------------------------------------------------------------------------------
// Curv2List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Curv2Owner
//------------------------------------------------------------------------------
void Curv2Owner::Clear()
{
	for (Curv2* pCurv2 : *this) Curv2::Delete(pCurv2);
	clear();
}

Gurax_EndModuleScope(model_obj)
