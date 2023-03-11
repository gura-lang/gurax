//==============================================================================
// Csh.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Csh
//------------------------------------------------------------------------------
String Csh::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Csh");
}

//------------------------------------------------------------------------------
// CshList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CshOwner
//------------------------------------------------------------------------------
void CshOwner::Clear()
{
	for (Csh* pCsh : *this) Csh::Delete(pCsh);
	clear();
}

Gurax_EndModuleScope(model_obj)
