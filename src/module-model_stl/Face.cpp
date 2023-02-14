//==============================================================================
// Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
Face::Face(const Face& src) : _pNormal(src._pNormal.Reference()),
	_pVertex1(src._pVertex1.Reference()), _pVertex2(src._pVertex2.Reference()), _pVertex3(src._pVertex3.Reference()),
	_attr(src._attr)
{
}

const Vertex& Face::GetNormal() const
{
	if (!_pNormal) UpdateNormal();
	return _pNormal->v;
}

const VertexRef& Face::GetNormalRef() const
{
	if (!_pNormal) UpdateNormal();
	return *_pNormal;
}

void Face::UpdateNormal() const
{
	const_cast<Face*>(this)->_pNormal.reset(new VertexRef(Vertex::Normal(GetVertex1(), GetVertex2(), GetVertex3(), true)));
}

String Face::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.Face");
}

Gurax_EndModuleScope(model_stl)
