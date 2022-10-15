//==============================================================================
// Element.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
Element::Element(String name) : Node(Type::Element), _name(name), _pAttrs(new AttrOwner()), _pNodesChild(new NodeOwner()) {}

bool Element::Compose(Stream& stream) const
{
	if (HasNodesChild()) {
		stream.Print(TextizeStart().c_str());
		for (auto pNode : GetNodesChild()) if (!pNode->Compose(stream)) return false;
		stream.Print(TextizeEnd().c_str());
	} else {
		stream.Print(TextizeEmpty());
	}
	return !Error::IsIssued();
}

Value* Element::CreateValue() const
{
	return new Value_Element(Reference());
}

const Element* Element::Locate(const char* path)
{
	const Element *pElement = this;
	if (::strcmp(pElement->GetName(),  Node::ExtractField(&path).c_str()) != 0) return nullptr;
	while (*path) {
		pElement = pElement->GetNodesChild().FindElement(&path);
		if (!pElement) break;
	}
	return pElement;
}

String Element::AccumText() const
{
	String str;
	NodeWalker nodeWalker(Reference());
	for (;;) {
		const Node* pNode = nodeWalker.Next();
		if (!pNode) break;
		if (pNode->CheckTypeMask(Node::TypeMask::Text | Node::TypeMask::CData)) str += pNode->GetText();
	}
	return str;
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
