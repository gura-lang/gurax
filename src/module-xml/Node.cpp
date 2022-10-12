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

//------------------------------------------------------------------------------
// Iterator_Walk
//------------------------------------------------------------------------------
Iterator_Walk::Iterator_Walk(UInt32 typeMask, Element* pElement) : _typeMask(typeMask), _pElement(pElement)
{
	_nodePickerStack.push_back(new NodePicker(pElement->GetNodesChild().Reference()));
}

Value* Iterator_Walk::DoNextValue()
{
	if (_pElement) {
		RefPtr<Element> pElement(_pElement.release());
		if (_typeMask & Node::TypeMask::Element) return pElement->CreateValue();
	}
	while (!_nodePickerStack.empty()) {
		NodePicker* pNodePicker = _nodePickerStack.back();
		const Node* pNode = pNodePicker->Next();
		if (pNode) {
			if (pNode->GetType() == Node::Type::Element) {
				const NodeOwner& nodesChild = dynamic_cast<const Element*>(pNode)->GetNodesChild();
				_nodePickerStack.push_back(new NodePicker(nodesChild.Reference()));
			}
			if (pNode->CheckTypeMask(_typeMask)) return pNode->CreateValue();
		} else {
			_nodePickerStack.pop_back();
			delete pNodePicker;
		}
	}
	return nullptr;
}

String Iterator_Walk::ToString(const StringStyle& ss) const
{
	return String().Format("Walk");
}

//------------------------------------------------------------------------------
// Iterator_Walk::NodePicker
//------------------------------------------------------------------------------
const Node* Iterator_Walk::NodePicker::Next()
{
	if (_idx < _pNodes->size()) return _pNodes->at(_idx++);
	return nullptr;
}

//------------------------------------------------------------------------------
// Iterator_Walk::NodePickerStack
//------------------------------------------------------------------------------
Iterator_Walk::NodePickerStack::~NodePickerStack()
{
	for (NodePicker* pNodePicker : *this) delete pNodePicker;
}

Gurax_EndModuleScope(xml)
