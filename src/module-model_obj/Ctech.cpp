//==============================================================================
// Ctech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Ctech
//------------------------------------------------------------------------------
String Ctech::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Ctech");
}

//------------------------------------------------------------------------------
// CtechList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CtechOwner
//------------------------------------------------------------------------------
void CtechOwner::Clear()
{
	for (Ctech* pCtech : *this) Ctech::Delete(pCtech);
	clear();
}

Gurax_EndModuleScope(model_obj)
