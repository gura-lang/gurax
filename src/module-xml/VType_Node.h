//==============================================================================
// VType_Node.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_NODE_H
#define GURAX_MODULE_XML_VTYPE_NODE_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Node : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Node VTYPE_Node;

//------------------------------------------------------------------------------
// Value_Node
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Node : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Node);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Node");
protected:
	RefPtr<Node> _pNode;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Node() = delete;
	explicit Value_Node(Node* pNode, VType& vtype = VTYPE_Node) :
		Value_Object(vtype), _pNode(pNode) {}
	// Copy constructor/operator
	Value_Node(const Value_Node& src) :
		Value_Object(src), _pNode(src._pNode->Reference()) {}
	Value_Node& operator=(const Value_Node& src) = delete;
	// Move constructor/operator
	Value_Node(Value_Node&& src) noexcept = delete;
	Value_Node& operator=(Value_Node&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Node() = default;
public:
	Node& GetNode() { return *_pNode; }
	const Node& GetNode() const { return *_pNode; }
public:
	static Node& GetNode(Value& value) {
		return dynamic_cast<Value_Node&>(value).GetNode();
	}
	static const Node& GetNode(const Value& value) {
		return dynamic_cast<const Value_Node&>(value).GetNode();
	}
	static Node* GetEntityPtr(Value& value) { return &GetNode(value); }
	static const Node* GetEntityPtr(const Value& value) { return &GetNode(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetNode().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetNode().IsEqualTo(Value_Node::GetNode(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetNode().IsLessThan(Value_Node::GetNode(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
