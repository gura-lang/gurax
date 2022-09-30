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
// Iterator_Node
//------------------------------------------------------------------------------
Value* Iterator_Node::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	if (_idx >= nodeOwner.size()) return nullptr;
	return nodeOwner[_idx++]->CreateValue();
}

String Iterator_Node::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Node");
	return str;
}

Gurax_EndModuleScope(xml)
