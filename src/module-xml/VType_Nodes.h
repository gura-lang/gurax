//==============================================================================
// VType_Nodes.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_NODES_H
#define GURAX_MODULE_XML_VTYPE_NODES_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_Nodes
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Nodes : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Nodes VTYPE_Nodes;

//------------------------------------------------------------------------------
// Value_Nodes
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Nodes : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Nodes);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Nodes");
protected:
	RefPtr<NodeOwner> _pNodes;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Nodes() = delete;
	explicit Value_Nodes(NodeOwner* pNodes, VType& vtype = VTYPE_Nodes) :
		Value_Object(vtype), _pNodes(pNodes) {}
	// Copy constructor/operator
	Value_Nodes(const Value_Nodes& src) :
		Value_Object(src), _pNodes(src._pNodes->Reference()) {}
	Value_Nodes& operator=(const Value_Nodes& src) = delete;
	// Move constructor/operator
	Value_Nodes(Value_Nodes&& src) noexcept = delete;
	Value_Nodes& operator=(Value_Nodes&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Nodes() = default;
public:
	NodeOwner& GetNodes() { return *_pNodes; }
	const NodeOwner& GetNodes() const { return *_pNodes; }
public:
	static NodeOwner& GetNodes(Value& value) {
		return dynamic_cast<Value_Nodes&>(value).GetNodes();
	}
	static const NodeOwner& GetNodes(const Value& value) {
		return dynamic_cast<const Value_Nodes&>(value).GetNodes();
	}
	static NodeOwner* GetEntityPtr(Value& value) { return &GetNodes(value); }
	static const NodeOwner* GetEntityPtr(const Value& value) { return &GetNodes(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return 0; }
	virtual bool IsEqualTo(const Value& value) const override { return false; }
	virtual bool IsLessThan(const Value& value) const override { return false; }
	bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
