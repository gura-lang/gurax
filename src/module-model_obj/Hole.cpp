//==============================================================================
// Hole.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Hole
//------------------------------------------------------------------------------
bool Hole::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Hole::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Hole::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Hole");
}

//------------------------------------------------------------------------------
// HoleList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// HoleOwner
//------------------------------------------------------------------------------
void HoleOwner::Clear()
{
	for (Hole* pHole : *this) Hole::Delete(pHole);
	clear();
}

Gurax_EndModuleScope(model_obj)
