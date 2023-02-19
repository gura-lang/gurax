//==============================================================================
// Vertex3.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex3
//------------------------------------------------------------------------------
String Vertex3::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Vertex3");
}

//------------------------------------------------------------------------------
// Vertex3List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Vertex3Owner
//------------------------------------------------------------------------------
void Vertex3Owner::Clear()
{
	for (Vertex3* pVertex3 : *this) Vertex3::Delete(pVertex3);
	clear();
}

Gurax_EndModuleScope(model_obj)