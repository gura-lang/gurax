//==============================================================================
// Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
Face::Face(const Face& src) : _normal(src._normal),
	_vertex1(src._vertex1), _vertex2(src._vertex2), _vertex3(src._vertex3), _attr(src._attr)
{
}

String Face::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.Face");
}

Gurax_EndModuleScope(model_stl)
