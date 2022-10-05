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
	Node* pNode = nodeOwner[_idx++];
	return pNode->CreateValue();
}

String Iterator_Node::ToString(const StringStyle& ss) const
{
	return String().Format("Node");
}

Gurax_EndModuleScope(xml)
