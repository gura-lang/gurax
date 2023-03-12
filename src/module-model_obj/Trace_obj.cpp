//==============================================================================
// Trace_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trace_obj
//------------------------------------------------------------------------------
bool Trace_obj::FeedField(const char* field, size_t iParam)
{
	return true;
}

String Trace_obj::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Trace_obj");
}

//------------------------------------------------------------------------------
// Trace_objList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Trace_objOwner
//------------------------------------------------------------------------------
void Trace_objOwner::Clear()
{
	for (Trace_obj* pTrace_obj : *this) Trace_obj::Delete(pTrace_obj);
	clear();
}

Gurax_EndModuleScope(model_obj)
