//==============================================================================
// Lod.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Lod
//------------------------------------------------------------------------------
bool Lod::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Lod::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Lod::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Lod");
}

//------------------------------------------------------------------------------
// LodList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LodOwner
//------------------------------------------------------------------------------
void LodOwner::Clear()
{
	for (Lod* pLod : *this) Lod::Delete(pLod);
	clear();
}

Gurax_EndModuleScope(model_obj)
