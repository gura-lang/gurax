//==============================================================================
// NodeStruct.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// NodeStruct
//------------------------------------------------------------------------------
NodeStruct::~NodeStruct()
{
	for (auto iter : _map) Node::Delete(iter.second);
}

String NodeStruct::ToString(const StringStyle& ss) const
{
	return String().Format("ml.NodeStruct");
}

//------------------------------------------------------------------------------
// NodeStructList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// NodeStructOwner
//------------------------------------------------------------------------------
void NodeStructOwner::Clear()
{
	for (NodeStruct* pNodeStruct : *this) NodeStruct::Delete(pNodeStruct);
	clear();
}

Gurax_EndModuleScope(ml)
