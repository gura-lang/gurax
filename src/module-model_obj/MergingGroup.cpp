//==============================================================================
// MergingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// MergingGroup
//------------------------------------------------------------------------------
String MergingGroup::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.MergingGroup");
}

//------------------------------------------------------------------------------
// MergingGroupList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MergingGroupOwner
//------------------------------------------------------------------------------
void MergingGroupOwner::Clear()
{
	for (MergingGroup* pMergingGroup : *this) MergingGroup::Delete(pMergingGroup);
	clear();
}

Gurax_EndModuleScope(model_obj)
