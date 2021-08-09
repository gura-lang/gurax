//==============================================================================
// VType_wxPrintData.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPRINTDATA_H
#define GURAX_MODULE_WX_VTYPE_WXPRINTDATA_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/cmndata.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPrintData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPrintData : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPrintData VTYPE_wxPrintData;

//------------------------------------------------------------------------------
// Value_wxPrintData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPrintData : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPrintData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPrintData");
protected:
	wxPrintData _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPrintData() = delete;
	explicit Value_wxPrintData(const wxPrintData& entity, VType& vtype = VTYPE_wxPrintData) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPrintData(const Value_wxPrintData& src) = delete;
	Value_wxPrintData& operator=(const Value_wxPrintData& src) = delete;
	// Move constructor/operator
	Value_wxPrintData(Value_wxPrintData&& src) noexcept = delete;
	Value_wxPrintData& operator=(Value_wxPrintData&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPrintData() = default;
public:
	wxPrintData& GetEntity() { return _entity; }
	const wxPrintData& GetEntity() const { return _entity; }
	wxPrintData* GetEntityPtr() { return &_entity; }
	const wxPrintData* GetEntityPtr() const { return &_entity; }
public:
	static wxPrintData& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPrintData&>(value).GetEntity();
	}
	static const wxPrintData& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPrintData&>(value).GetEntity();
	}
	static wxPrintData* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPrintData&>(value).GetEntityPtr();
	}
	static const wxPrintData* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPrintData&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && GetEntityPtr(*this) == GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(GetEntityPtr(*this) < GetEntityPtr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif