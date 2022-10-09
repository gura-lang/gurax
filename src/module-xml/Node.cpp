//==============================================================================
// Node.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Node
//------------------------------------------------------------------------------
size_t Node::GetDepth() const
{
	size_t depth = 0;
	RefPtr<Node> pNode(LockNodeParent());
	for ( ; pNode; depth++) pNode.reset(pNode->LockNodeParent());
	return depth;
}

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

#if 0
//------------------------------------------------------------------------------
// Iterator_Walk
//------------------------------------------------------------------------------
Value* Iterator_Walk::DoNextValue()
{
	while (!_iteratorStack.empty()) {
		Iterator* pIterator = _iteratorStack.back();
		RefPtr<Value> pValue(pIterator->NextValue());
		if (pValue) {
			if (pValue->IsType(VTYPE_Element)) {
				const NodeOwner& nodesChild = Value_Element::GetElement(*pValue).GetNodesChild();
				_iteratorStack.push_back(_pIteratorFactory->CreateIterator(nodesChild.Reference()));
			}
			return pValue.release();
		}
		_iteratorStack.pop_back();
		Iterator::Delete(pIterator);
	}
	return nullptr;
}

String Iterator_Walk::ToString(const StringStyle& ss) const
{
	return String().Format("Walk");
}
#endif

Gurax_EndModuleScope(xml)
