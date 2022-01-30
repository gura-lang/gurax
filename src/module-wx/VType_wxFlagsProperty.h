//==============================================================================
// VType_wxFlagsProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFLAGSPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXFLAGSPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/props.h>
#include "Util.h"
#include "VType_wxPGProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFlagsProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFlagsProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFlagsProperty VTYPE_wxFlagsProperty;

//------------------------------------------------------------------------------
// Value_wxFlagsProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFlagsProperty : public Value_wxPGProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFlagsProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFlagsProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFlagsProperty() = delete;
	explicit Value_wxFlagsProperty(const wxFlagsProperty& entity, VType& vtype = VTYPE_wxFlagsProperty) :
		Value_wxPGProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxFlagsProperty(const Value_wxFlagsProperty& src) = delete;
	Value_wxFlagsProperty& operator=(const Value_wxFlagsProperty& src) = delete;
	// Move constructor/operator
	Value_wxFlagsProperty(Value_wxFlagsProperty&& src) noexcept = delete;
	Value_wxFlagsProperty& operator=(Value_wxFlagsProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFlagsProperty() = default;
public:
	wxFlagsProperty& GetEntity() { return reinterpret_cast<wxFlagsProperty&>(Value_wxPGProperty::GetEntity()); }
	const wxFlagsProperty& GetEntity() const { return reinterpret_cast<const wxFlagsProperty&>(Value_wxPGProperty::GetEntity()); }
	wxFlagsProperty* GetEntityPtr() { return reinterpret_cast<wxFlagsProperty*>(Value_wxPGProperty::GetEntityPtr()); }\
	const wxFlagsProperty* GetEntityPtr() const { return reinterpret_cast<const wxFlagsProperty*>(Value_wxPGProperty::GetEntityPtr()); }
public:
	static wxFlagsProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFlagsProperty&>(value).GetEntity();
	}
	static const wxFlagsProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFlagsProperty&>(value).GetEntity();
	}
	static wxFlagsProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFlagsProperty&>(value).GetEntityPtr();
	}
	static const wxFlagsProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFlagsProperty&>(value).GetEntityPtr();
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
