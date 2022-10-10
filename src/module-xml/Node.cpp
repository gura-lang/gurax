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
	_iteratorStack.push_back(new Iterator_Each(pElement->GetNodesChild().Reference()));
}

Value* Iterator_Walk::DoNextValue()
{
	if (_pElement) {
		RefPtr<Element> pElement(_pElement.release());
		if (_typeMask & Node::TypeMask::Element) return pElement->CreateValue();
	}
	while (!_iteratorStack.empty()) {
		Iterator* pIterator = _iteratorStack.back();
		RefPtr<Value> pValue(pIterator->NextValue());
		if (!pValue) {
			_iteratorStack.pop_back();
			Iterator::Delete(pIterator);
		} else if (pValue->IsType(VTYPE_CData)) {
			if (_typeMask & Node::TypeMask::CData) return pValue.release();
		} else if (pValue->IsType(VTYPE_Comment)) {
			if (_typeMask & Node::TypeMask::Comment) return pValue.release();
		} else if (pValue->IsType(VTYPE_Element)) {
			const NodeOwner& nodesChild = Value_Element::GetElement(*pValue).GetNodesChild();
			_iteratorStack.push_back(new Iterator_Each(nodesChild.Reference()));
			if (_typeMask & Node::TypeMask::Element) return pValue.release();
		} else if (pValue->IsType(VTYPE_Text)) {
			if (_typeMask & Node::TypeMask::Text) return pValue.release();
		} else if (pValue->IsType(VTYPE_XmlDecl)) {
			if (_typeMask & Node::TypeMask::XmlDecl) return pValue.release();
		} else {
			// nothing to do
		}
	}
	return nullptr;
}

String Iterator_Walk::ToString(const StringStyle& ss) const
{
	return String().Format("Walk");
}

Gurax_EndModuleScope(xml)
