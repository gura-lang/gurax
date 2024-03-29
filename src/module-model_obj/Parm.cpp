//==============================================================================
// Parm.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Parm
//------------------------------------------------------------------------------
bool Parm::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Parm::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Parm::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Parm");
}

//------------------------------------------------------------------------------
// ParmList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ParmOwner
//------------------------------------------------------------------------------
void ParmOwner::Clear()
{
	for (Parm* pParm : *this) Parm::Delete(pParm);
	clear();
}

Gurax_EndModuleScope(model_obj)
