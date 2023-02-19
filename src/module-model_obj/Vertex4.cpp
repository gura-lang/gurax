//==============================================================================
// Vertex4.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex4
//------------------------------------------------------------------------------
String Vertex4::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Vertex4");
}

//------------------------------------------------------------------------------
// Vertex4List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Vertex4Owner
//------------------------------------------------------------------------------
void Vertex4Owner::Clear()
{
	for (Vertex4* pVertex4 : *this) Vertex4::Delete(pVertex4);
	clear();
}

Gurax_EndModuleScope(model_obj)
