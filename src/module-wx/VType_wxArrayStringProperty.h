//==============================================================================
// VType_wxArrayStringProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXARRAYSTRINGPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXARRAYSTRINGPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/props.h>
#include "Util.h"
#include "VType_wxPGProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxArrayStringProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxArrayStringProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxArrayStringProperty VTYPE_wxArrayStringProperty;

//------------------------------------------------------------------------------
// Value_wxArrayStringProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxArrayStringProperty : public Value_wxPGProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxArrayStringProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxArrayStringProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxArrayStringProperty() = delete;
	explicit Value_wxArrayStringProperty(const wxArrayStringProperty& entity, VType& vtype = VTYPE_wxArrayStringProperty) :
		Value_wxPGProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxArrayStringProperty(const Value_wxArrayStringProperty& src) = delete;
	Value_wxArrayStringProperty& operator=(const Value_wxArrayStringProperty& src) = delete;
	// Move constructor/operator
	Value_wxArrayStringProperty(Value_wxArrayStringProperty&& src) noexcept = delete;
	Value_wxArrayStringProperty& operator=(Value_wxArrayStringProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxArrayStringProperty() = default;
public:
	wxArrayStringProperty& GetEntity() { return reinterpret_cast<wxArrayStringProperty&>(Value_wxPGProperty::GetEntity()); }
	const wxArrayStringProperty& GetEntity() const { return reinterpret_cast<const wxArrayStringProperty&>(Value_wxPGProperty::GetEntity()); }
	wxArrayStringProperty* GetEntityPtr() { return reinterpret_cast<wxArrayStringProperty*>(Value_wxPGProperty::GetEntityPtr()); }\
	const wxArrayStringProperty* GetEntityPtr() const { return reinterpret_cast<const wxArrayStringProperty*>(Value_wxPGProperty::GetEntityPtr()); }
public:
	static wxArrayStringProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxArrayStringProperty&>(value).GetEntity();
	}
	static const wxArrayStringProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxArrayStringProperty&>(value).GetEntity();
	}
	static wxArrayStringProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxArrayStringProperty&>(value).GetEntityPtr();
	}
	static const wxArrayStringProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxArrayStringProperty&>(value).GetEntityPtr();
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