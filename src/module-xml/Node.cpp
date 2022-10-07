//==============================================================================
// Node.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
String Node::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Node");
}

//------------------------------------------------------------------------------
// NodeList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// NodeOwner
//------------------------------------------------------------------------------
void NodeOwner::Clear()
{
	for (Node* pNode : *this) Node::Delete(pNode);
	clear();
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Value* Iterator_Each::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	if (_idx >= nodeOwner.size()) return nullptr;
	Node* pNode = nodeOwner[_idx++];
	return pNode->CreateValue();
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("Each");
}

//------------------------------------------------------------------------------
// Iterator_EachElement
//------------------------------------------------------------------------------
Value* Iterator_EachElement::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	while (_idx < nodeOwner.size()) {
		Node* pNode = nodeOwner[_idx++];
		if (pNode->IsElement(_tagName.c_str())) return pNode->CreateValue();
	} 
	return nullptr;
}

String Iterator_EachElement::ToString(const StringStyle& ss) const
{
	return String().Format("EachElement");
}

//------------------------------------------------------------------------------
// Iterator_EachText
//------------------------------------------------------------------------------
Value* Iterator_EachText::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	while (_idx < nodeOwner.size()) {
		Node* pNode = nodeOwner[_idx++];
		if (pNode->GetType() == Node::Type::Text) return pNode->CreateValue();
	} 
	return nullptr;
}

String Iterator_EachText::ToString(const StringStyle& ss) const
{
	return String().Format("EachText");
}

Gurax_EndModuleScope(xml)
