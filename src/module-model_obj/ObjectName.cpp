//==============================================================================
// ObjectName.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// ObjectName
//------------------------------------------------------------------------------
bool ObjectName::FeedField(const char* field, size_t iParam)
{
	return true;
}

String ObjectName::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.ObjectName");
}

//------------------------------------------------------------------------------
// ObjectNameList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ObjectNameOwner
//------------------------------------------------------------------------------
void ObjectNameOwner::Clear()
{
	for (ObjectName* pObjectName : *this) ObjectName::Delete(pObjectName);
	clear();
}

Gurax_EndModuleScope(model_obj)
