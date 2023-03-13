//==============================================================================
// Surf.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Surf
//------------------------------------------------------------------------------
bool Surf::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Surf::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Surf::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Surf");
}

//------------------------------------------------------------------------------
// SurfList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SurfOwner
//------------------------------------------------------------------------------
void SurfOwner::Clear()
{
	for (Surf* pSurf : *this) Surf::Delete(pSurf);
	clear();
}

Gurax_EndModuleScope(model_obj)
