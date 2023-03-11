//==============================================================================
// SmoothingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// SmoothingGroup
//------------------------------------------------------------------------------
String SmoothingGroup::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.SmoothingGroup");
}

//------------------------------------------------------------------------------
// SmoothingGroupList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SmoothingGroupOwner
//------------------------------------------------------------------------------
void SmoothingGroupOwner::Clear()
{
	for (SmoothingGroup* pSmoothingGroup : *this) SmoothingGroup::Delete(pSmoothingGroup);
	clear();
}

Gurax_EndModuleScope(model_obj)
