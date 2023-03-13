//==============================================================================
// Usemap.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Usemap
//------------------------------------------------------------------------------
bool Usemap::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Usemap::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Usemap::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Usemap");
}

//------------------------------------------------------------------------------
// UsemapList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UsemapOwner
//------------------------------------------------------------------------------
void UsemapOwner::Clear()
{
	for (Usemap* pUsemap : *this) Usemap::Delete(pUsemap);
	clear();
}

Gurax_EndModuleScope(model_obj)
