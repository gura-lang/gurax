//==============================================================================
// Element.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
Element::Element(String name) : Node(Type::Element), _name(name), _pAttrs(new AttrOwner()), _pNodesChild(new NodeOwner()) {}

String Element::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Element");
}

Gurax_EndModuleScope(xml)
