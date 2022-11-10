﻿//==============================================================================
// VType_wxCursorProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCURSORPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXCURSORPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/advprops.h>
#include "Util.h"
#include "VType_wxEnumProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCursorProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCursorProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCursorProperty VTYPE_wxCursorProperty;

//------------------------------------------------------------------------------
// Value_wxCursorProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCursorProperty : public Value_wxEnumProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCursorProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCursorProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxCursorProperty() = delete;
	explicit Value_wxCursorProperty(const wxCursorProperty& entity, VType& vtype = VTYPE_wxCursorProperty) :
		Value_wxEnumProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxCursorProperty(const Value_wxCursorProperty& src) = delete;
	Value_wxCursorProperty& operator=(const Value_wxCursorProperty& src) = delete;
	// Move constructor/operator
	Value_wxCursorProperty(Value_wxCursorProperty&& src) noexcept = delete;
	Value_wxCursorProperty& operator=(Value_wxCursorProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCursorProperty() = default;
public:
	wxCursorProperty& GetEntity() { return reinterpret_cast<wxCursorProperty&>(Value_wxEnumProperty::GetEntity()); }
	const wxCursorProperty& GetEntity() const { return reinterpret_cast<const wxCursorProperty&>(Value_wxEnumProperty::GetEntity()); }
	wxCursorProperty* GetEntityPtr() { return reinterpret_cast<wxCursorProperty*>(Value_wxEnumProperty::GetEntityPtr()); }\
	const wxCursorProperty* GetEntityPtr() const { return reinterpret_cast<const wxCursorProperty*>(Value_wxEnumProperty::GetEntityPtr()); }
public:
	static wxCursorProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCursorProperty&>(value).GetEntity();
	}
	static const wxCursorProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCursorProperty&>(value).GetEntity();
	}
	static wxCursorProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCursorProperty&>(value).GetEntityPtr();
	}
	static const wxCursorProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCursorProperty&>(value).GetEntityPtr();
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
