//==============================================================================
// VType_wxFloatProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFLOATPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXFLOATPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/props.h>
#include "Util.h"
#include "VType_wxPGProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFloatProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFloatProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFloatProperty VTYPE_wxFloatProperty;

//------------------------------------------------------------------------------
// Value_wxFloatProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFloatProperty : public Value_wxPGProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFloatProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFloatProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFloatProperty() = delete;
	explicit Value_wxFloatProperty(const wxFloatProperty& entity, VType& vtype = VTYPE_wxFloatProperty) :
		Value_wxPGProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxFloatProperty(const Value_wxFloatProperty& src) = delete;
	Value_wxFloatProperty& operator=(const Value_wxFloatProperty& src) = delete;
	// Move constructor/operator
	Value_wxFloatProperty(Value_wxFloatProperty&& src) noexcept = delete;
	Value_wxFloatProperty& operator=(Value_wxFloatProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFloatProperty() = default;
public:
	wxFloatProperty& GetEntity() { return reinterpret_cast<wxFloatProperty&>(Value_wxPGProperty::GetEntity()); }
	const wxFloatProperty& GetEntity() const { return reinterpret_cast<const wxFloatProperty&>(Value_wxPGProperty::GetEntity()); }
	wxFloatProperty* GetEntityPtr() { return reinterpret_cast<wxFloatProperty*>(Value_wxPGProperty::GetEntityPtr()); }\
	const wxFloatProperty* GetEntityPtr() const { return reinterpret_cast<const wxFloatProperty*>(Value_wxPGProperty::GetEntityPtr()); }
public:
	static wxFloatProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFloatProperty&>(value).GetEntity();
	}
	static const wxFloatProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFloatProperty&>(value).GetEntity();
	}
	static wxFloatProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFloatProperty&>(value).GetEntityPtr();
	}
	static const wxFloatProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFloatProperty&>(value).GetEntityPtr();
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
