//==============================================================================
// Spoint.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Spoint
//------------------------------------------------------------------------------
String Spoint::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Spoint");
}

//------------------------------------------------------------------------------
// SpointList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SpointOwner
//------------------------------------------------------------------------------
void SpointOwner::Clear()
{
	for (Spoint* pSpoint : *this) Spoint::Delete(pSpoint);
	clear();
}

Gurax_EndModuleScope(model_obj)
