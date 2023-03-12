//==============================================================================
// C_interp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// C_interp
//------------------------------------------------------------------------------
bool C_interp::FeedField(const char* field, size_t iParam)
{
	return true;
}

String C_interp::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.C_interp");
}

//------------------------------------------------------------------------------
// C_interpList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// C_interpOwner
//------------------------------------------------------------------------------
void C_interpOwner::Clear()
{
	for (C_interp* pC_interp : *this) C_interp::Delete(pC_interp);
	clear();
}

Gurax_EndModuleScope(model_obj)
