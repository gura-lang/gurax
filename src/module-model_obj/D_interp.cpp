//==============================================================================
// D_interp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// D_interp
//------------------------------------------------------------------------------
bool D_interp::FeedField(const char* field, size_t iParam)
{
	return true;
}

String D_interp::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.D_interp");
}

//------------------------------------------------------------------------------
// D_interpList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// D_interpOwner
//------------------------------------------------------------------------------
void D_interpOwner::Clear()
{
	for (D_interp* pD_interp : *this) D_interp::Delete(pD_interp);
	clear();
}

Gurax_EndModuleScope(model_obj)
