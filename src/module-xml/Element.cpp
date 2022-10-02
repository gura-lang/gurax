//==============================================================================
// Element.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
Element::Element(String name) : Node(Type::Element), _name(name), _pAttrs(new AttrOwner()), _pNodesChild(new NodeOwner()) {}

void Element::Compose(Stream& stream) const
{
}

Value* Element::CreateValue() const
{
	return new Value_Element(Reference());
}

String Element::TextizeStart() const
{
	String str;
	str += "<";
	str += GetName();
	for (auto pAttr : GetAttrs()) {
		str += " ";
		str += pAttr->ToString();
	}
	str += ">";
	return str;
}

String Element::TextizeEnd() const
{
	return String().Format("</%s>", GetName());
}

String Element::TextizeEmpty() const
{
	return String().Format("<%s/>", GetName());
}


String Element::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Element:%s", GetName());
}

Gurax_EndModuleScope(xml)
