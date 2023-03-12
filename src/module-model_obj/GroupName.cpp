//==============================================================================
// GroupName.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// GroupName
//------------------------------------------------------------------------------
bool GroupName::FeedField(const char* field, size_t iParam)
{
	return true;
}

String GroupName::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.GroupName");
}

//------------------------------------------------------------------------------
// GroupNameList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GroupNameOwner
//------------------------------------------------------------------------------
void GroupNameOwner::Clear()
{
	for (GroupName* pGroupName : *this) GroupName::Delete(pGroupName);
	clear();
}

Gurax_EndModuleScope(model_obj)