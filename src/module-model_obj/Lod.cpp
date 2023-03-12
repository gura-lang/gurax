//==============================================================================
// Lod.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Lod
//------------------------------------------------------------------------------
bool Lod::FeedField(const char* field, size_t iParam)
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