//==============================================================================
// Element.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
Element::Element(String name) : Node(Type::Element), _name(name), _pAttrs(new AttrOwner()), _pNodesChild(new NodeOwner()) {}

Value* Element::CreateValue() const
{
	return new Value_Element(Reference());
}

String Element::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Element");
}

Gurax_EndModuleScope(xml)
