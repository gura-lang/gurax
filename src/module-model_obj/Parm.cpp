//==============================================================================
// Parm.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Parm
//------------------------------------------------------------------------------
bool Parm::FeedField(const char* field, size_t iParam)
{
	return true;
}

String Parm::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Parm");
}

//------------------------------------------------------------------------------
// ParmList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ParmOwner
//------------------------------------------------------------------------------
void ParmOwner::Clear()
{
	for (Parm* pParm : *this) Parm::Delete(pParm);
	clear();
}

Gurax_EndModuleScope(model_obj)
