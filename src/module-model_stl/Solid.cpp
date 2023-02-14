//==============================================================================
// Solid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Solid
//------------------------------------------------------------------------------
bool Solid::Prepare()
{
	return false;	
}

String Solid::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.Solid");
}

Gurax_EndModuleScope(model_stl)
