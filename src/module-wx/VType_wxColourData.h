//==============================================================================
// VType_wxColourData.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOURDATA_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOURDATA_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/colourdata.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColourData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColourData : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxColourData VTYPE_wxColourData;

//------------------------------------------------------------------------------
// Value_wxColourData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColourData : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColourData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColourData");
protected:
	wxColourData& _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxColourData() = delete;
	explicit Value_wxColourData(const wxColourData& entity, VType& vtype = VTYPE_wxColourData) :
		Value_wxObject(entity, vtype), _entity(const_cast<wxColourData&>(entity)) {}
	// Copy constructor/operator
	Value_wxColourData(const Value_wxColourData& src) = delete;
	Value_wxColourData& operator=(const Value_wxColourData& src) = delete;
	// Move constructor/operator
	Value_wxColourData(Value_wxColourData&& src) noexcept = delete;
	Value_wxColourData& operator=(Value_wxColourData&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColourData() = default;
public:
	wxColourData& GetEntity() { return _entity; }
	const wxColourData& GetEntity() const { return _entity; }
	wxColourData* GetEntityPtr() { return &_entity; }
	const wxColourData* GetEntityPtr() const { return &_entity; }
public:
	static wxColourData& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColourData&>(value).GetEntity();
	}
	static const wxColourData& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColourData&>(value).GetEntity();
	}
	static wxColourData* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColourData&>(value).GetEntityPtr();
	}
	static const wxColourData* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColourData&>(value).GetEntityPtr();
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
