//==============================================================================
// Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
Face::Face(const Face& src) : _normal(src._normal), _attr(src._attr)
{
	for (int i = 0; i < 3; i++) _vertexes[i] = src._vertexes[i];
}

String Face::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.Face");
}

Gurax_EndModuleScope(model_stl)
