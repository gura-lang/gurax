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

String Node::ExtractField(const char** pPath)
{
	const char* start = *pPath;
	const char* end = start;
	for ( ; ; end++) {
		if (*end == '\0') {
			*pPath = end;
			break;
		} else if (*end == '/') {
			*pPath = end + 1;
			break;
		}
	}
	return String(start, end);
}

UInt32 Node::GetTypeMask(const Attribute& attr)
{
	UInt32 typeMask = 0;
	if (attr.IsSet(Gurax_Symbol(cdata))) typeMask |= Node::TypeMask::CData;
	if (attr.IsSet(Gurax_Symbol(comment))) typeMask |= Node::TypeMask::Comment;
	if (attr.IsSet(Gurax_Symbol(element))) typeMask |= Node::TypeMask::Element;
	if (attr.IsSet(Gurax_Symbol(text))) typeMask |= Node::TypeMask::Text;
	return typeMask;
}

//------------------------------------------------------------------------------
// NodeList
//------------------------------------------------------------------------------
const Element* NodeList::FindElement(const char* tagName) const
{
	for (const Node* pNode : *this) {
		if (pNode->IsElement(tagName)) return dynamic_cast<const Element*>(pNode);
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// NodeOwner
//------------------------------------------------------------------------------
void NodeOwner::Clear()
{
	for (Node* pNode : *this) Node::Delete(pNode);
	clear();
}

//------------------------------------------------------------------------------
// NodePicker
//------------------------------------------------------------------------------
const Node* NodePicker::Next()
{
	if (_idx < _pNodes->size()) return _pNodes->at(_idx++);
	return nullptr;
}

//------------------------------------------------------------------------------
// NodePickerStack
//------------------------------------------------------------------------------
NodePickerStack::~NodePickerStack()
{
	for (NodePicker* pNodePicker : *this) delete pNodePicker;
}

//------------------------------------------------------------------------------
// NodeWalker
//------------------------------------------------------------------------------
NodeWalker::NodeWalker(Element* pElement) : _pElement(pElement), _firstFlag(true)
{
	_nodePickerStack.push_back(new NodePicker(pElement->GetNodesChild().Reference()));
}

const Node* NodeWalker::Next()
{
	if (_firstFlag) {
		_firstFlag = false;
		return _pElement.get();
	}
	while (!_nodePickerStack.empty()) {
		NodePicker* pNodePicker = _nodePickerStack.back();
		const Node* pNode = pNodePicker->Next();
		if (!pNode) {
			_nodePickerStack.pop_back();
			delete pNodePicker;
		} else if (pNode->GetType() == Node::Type::Element) {
			const NodeOwner& nodesChild = dynamic_cast<const Element*>(pNode)->GetNodesChild();
			_nodePickerStack.push_back(new NodePicker(nodesChild.Reference()));
			return pNode;
		} else {
			return pNode;
		}
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
Iterator_Each::Iterator_Each(NodeOwner* pNodeOwner, UInt32 typeMask, String tagName) :
		_pNodeOwner(pNodeOwner), _typeMask(typeMask), _tagName(tagName), _idx(0)
{
}

Value* Iterator_Each::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	while (_idx < nodeOwner.size()) {
		Node* pNode = nodeOwner[_idx++];
		if (pNode->CheckTypeMask(_typeMask, _tagName.c_str())) return pNode->CreateValue();
	} 
	return nullptr;
}

String Iterator_Each::ToString(const StringStyle& ss) const
{
	return String().Format("Each");
}

//------------------------------------------------------------------------------
// Iterator_Walk
//------------------------------------------------------------------------------
Iterator_Walk::Iterator_Walk(Element* pElement, UInt32 typeMask, String tagName) :
		_nodeWalker(pElement), _typeMask(typeMask), _tagName(tagName)
{
}

Value* Iterator_Walk::DoNextValue()
{
	for (;;) {
		const Node* pNode = _nodeWalker.Next();
		if (!pNode) return nullptr;
		if (pNode->CheckTypeMask(_typeMask, _tagName.c_str())) return pNode->CreateValue();
	}
	return nullptr;
}

String Iterator_Walk::ToString(const StringStyle& ss) const
{
	return String().Format("Walk");
}

Gurax_EndModuleScope(xml)
