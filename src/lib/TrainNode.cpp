//==============================================================================
// TrainNode.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TrainNode
//------------------------------------------------------------------------------
TrainNode::TrainNode(const char* nodeTypeName, Connector* pConnectorDst) : _nodeTypeName(nodeTypeName)
{
	if (pConnectorDst) {
		pConnectorDst->SetNodeSrc(this);
		_connectorsDst.push_back(pConnectorDst);
	}
}

void TrainNode::Print(int indentLevel) const
{
	::printf("%-*s%s\n", indentLevel * 2, "", ToString(StringStyle::Empty).c_str());
}

String TrainNode::ToString(const StringStyle& ss) const
{
	return String().Format("TrainNode");
}

//------------------------------------------------------------------------------
// TrainNodeList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrainNodeOwner
//------------------------------------------------------------------------------
void TrainNodeOwner::Clear()
{
	for (TrainNode* pTrainNode : *this) TrainNode::Delete(pTrainNode);
	clear();
}

}
