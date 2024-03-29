//==============================================================================
// Curv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv
//------------------------------------------------------------------------------
bool Curv::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Curv::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Curv::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Curv");
}

//------------------------------------------------------------------------------
// CurvList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CurvOwner
//------------------------------------------------------------------------------
void CurvOwner::Clear()
{
	for (Curv* pCurv : *this) Curv::Delete(pCurv);
	clear();
}

Gurax_EndModuleScope(model_obj)
