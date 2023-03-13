//==============================================================================
// ObjectName.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// ObjectName
//------------------------------------------------------------------------------
bool ObjectName::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool ObjectName::FinishField(const Tokenizer& tokenizer, size_t nParams)
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
