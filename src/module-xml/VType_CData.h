//==============================================================================
// VType_CData.h
//==============================================================================
#ifndef GURAX_MODULE_XML_VTYPE_CDATA_H
#define GURAX_MODULE_XML_VTYPE_CDATA_H
#include <gurax.h>
#include "CData.h"
#include "VType_Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// VType_CData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CData : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CData VTYPE_CData;

//------------------------------------------------------------------------------
// Value_CData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CData : public Value_Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CData");
public:
	static VType& vtype;
public:
	// Constructor
	Value_CData() = delete;
	explicit Value_CData(CData* pCData, VType& vtype = VTYPE_CData) : Value_Node(pCData, vtype) {}
	// Copy constructor/operator
	Value_CData(const Value_CData& src) : Value_Node(src) {}
	Value_CData& operator=(const Value_CData& src) = delete;
	// Move constructor/operator
	Value_CData(Value_CData&& src) noexcept = delete;
	Value_CData& operator=(Value_CData&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CData() = default;
public:
	CData& GetCData() { return dynamic_cast<CData&>(GetNode()); }
	const CData& GetCData() const { return dynamic_cast<const CData&>(GetNode()); }
public:
	static CData& GetCData(Value& value) {
		return dynamic_cast<Value_CData&>(value).GetCData();
	}
	static const CData& GetCData(const Value& value) {
		return dynamic_cast<const Value_CData&>(value).GetCData();
	}
	static CData* GetEntityPtr(Value& value) { return &GetCData(value); }
	static const CData* GetEntityPtr(const Value& value) { return &GetCData(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCData().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCData().IsEqualTo(Value_CData::GetCData(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCData().IsLessThan(Value_CData::GetCData(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(xml)

#endif
