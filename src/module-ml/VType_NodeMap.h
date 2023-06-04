//==============================================================================
// VType_NodeMap.h
//==============================================================================
#ifndef GURAX_MODULE_ML_VTYPE_NodeMap_H
#define GURAX_MODULE_ML_VTYPE_NodeMap_H
#include <gurax.h>
#include "NodeMap.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// VType_NodeMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_NodeMap : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_NodeMap VTYPE_NodeMap;

//------------------------------------------------------------------------------
// Value_NodeMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_NodeMap : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_NodeMap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_NodeMap");
protected:
	RefPtr<NodeMap> _pNodeMap;
public:
	static VType& vtype;
public:
	// Constructor
	Value_NodeMap() = delete;
	explicit Value_NodeMap(NodeMap* pNodeMap, VType& vtype = VTYPE_NodeMap) :
		Value_Object(vtype), _pNodeMap(pNodeMap) {}
	// Copy constructor/operator
	Value_NodeMap(const Value_NodeMap& src) :
		Value_Object(src), _pNodeMap(src._pNodeMap->Reference()) {}
	Value_NodeMap& operator=(const Value_NodeMap& src) = delete;
	// Move constructor/operator
	Value_NodeMap(Value_NodeMap&& src) noexcept = delete;
	Value_NodeMap& operator=(Value_NodeMap&& src) noexcept = delete;
protected:
	// Destructor
	~Value_NodeMap() = default;
public:
	NodeMap& GetNodeMap() { return *_pNodeMap; }
	const NodeMap& GetNodeMap() const { return *_pNodeMap; }
public:
	static NodeMap& GetNodeMap(Value& value) {
		return dynamic_cast<Value_NodeMap&>(value).GetNodeMap();
	}
	static const NodeMap& GetNodeMap(const Value& value) {
		return dynamic_cast<const Value_NodeMap&>(value).GetNodeMap();
	}
	static NodeMap* GetEntityPtr(Value& value) { return &GetNodeMap(value); }
	static const NodeMap* GetEntityPtr(const Value& value) { return &GetNodeMap(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetNodeMap().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetNodeMap().IsEqualTo(Value_NodeMap::GetNodeMap(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetNodeMap().IsLessThan(Value_NodeMap::GetNodeMap(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	// Virtual functions for runtime process
	virtual Value* DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag) override;
};

Gurax_EndModuleScope(ml)

#endif
