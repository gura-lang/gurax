//==============================================================================
// Hole.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Hole
//------------------------------------------------------------------------------
bool Hole::FeedField(const char* field, size_t iParam)
{
	return true;
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
