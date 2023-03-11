//==============================================================================
// Usemtl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Usemtl
//------------------------------------------------------------------------------
String Usemtl::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Usemtl");
}

//------------------------------------------------------------------------------
// UsemtlList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UsemtlOwner
//------------------------------------------------------------------------------
void UsemtlOwner::Clear()
{
	for (Usemtl* pUsemtl : *this) Usemtl::Delete(pUsemtl);
	clear();
}

Gurax_EndModuleScope(model_obj)
