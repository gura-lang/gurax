//==============================================================================
// VType_NodeStruct.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_NODESTRUCT_H
#define GURAX_MODULE_ML_VTYPE_NODESTRUCT_H
#include <gurax.h>
#include "NodeStruct.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_NodeStruct
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_NodeStruct : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_NodeStruct VTYPE_NodeStruct;

//------------------------------------------------------------------------------
// Value_NodeStruct
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_NodeStruct : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_NodeStruct);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_NodeStruct");
protected:
	RefPtr<NodeStruct> _pNodeStruct;
public:
	static VType& vtype;
public:
	// Constructor
	Value_NodeStruct() = delete;
	explicit Value_NodeStruct(NodeStruct* pNodeStruct, VType& vtype = VTYPE_NodeStruct) :
		Value_Object(vtype), _pNodeStruct(pNodeStruct) {}
	// Copy constructor/operator
	Value_NodeStruct(const Value_NodeStruct& src) :
		Value_Object(src), _pNodeStruct(src._pNodeStruct->Reference()) {}
	Value_NodeStruct& operator=(const Value_NodeStruct& src) = delete;
	// Move constructor/operator
	Value_NodeStruct(Value_NodeStruct&& src) noexcept = delete;
	Value_NodeStruct& operator=(Value_NodeStruct&& src) noexcept = delete;
protected:
	// Destructor
	~Value_NodeStruct() = default;
public:
	NodeStruct& GetNodeStruct() { return *_pNodeStruct; }
	const NodeStruct& GetNodeStruct() const { return *_pNodeStruct; }
public:
	static NodeStruct& GetNodeStruct(Value& value) {
		return dynamic_cast<Value_NodeStruct&>(value).GetNodeStruct();
	}
	static const NodeStruct& GetNodeStruct(const Value& value) {
		return dynamic_cast<const Value_NodeStruct&>(value).GetNodeStruct();
	}
	static NodeStruct* GetEntityPtr(Value& value) { return &GetNodeStruct(value); }
	static const NodeStruct* GetEntityPtr(const Value& value) { return &GetNodeStruct(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetNodeStruct().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetNodeStruct().IsEqualTo(Value_NodeStruct::GetNodeStruct(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetNodeStruct().IsLessThan(Value_NodeStruct::GetNodeStruct(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml)

#endif
