//==============================================================================
// VType_wxColourProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOURPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOURPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/advprops.h>
#include "Util.h"
#include "VType_wxSystemColourProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColourProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColourProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxColourProperty VTYPE_wxColourProperty;

//------------------------------------------------------------------------------
// Value_wxColourProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColourProperty : public Value_wxSystemColourProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColourProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColourProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxColourProperty() = delete;
	explicit Value_wxColourProperty(const wxColourProperty& entity, VType& vtype = VTYPE_wxColourProperty) :
		Value_wxSystemColourProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxColourProperty(const Value_wxColourProperty& src) = delete;
	Value_wxColourProperty& operator=(const Value_wxColourProperty& src) = delete;
	// Move constructor/operator
	Value_wxColourProperty(Value_wxColourProperty&& src) noexcept = delete;
	Value_wxColourProperty& operator=(Value_wxColourProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColourProperty() = default;
public:
	wxColourProperty& GetEntity() { return reinterpret_cast<wxColourProperty&>(Value_wxSystemColourProperty::GetEntity()); }
	const wxColourProperty& GetEntity() const { return reinterpret_cast<const wxColourProperty&>(Value_wxSystemColourProperty::GetEntity()); }
	wxColourProperty* GetEntityPtr() { return reinterpret_cast<wxColourProperty*>(Value_wxSystemColourProperty::GetEntityPtr()); }\
	const wxColourProperty* GetEntityPtr() const { return reinterpret_cast<const wxColourProperty*>(Value_wxSystemColourProperty::GetEntityPtr()); }
public:
	static wxColourProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColourProperty&>(value).GetEntity();
	}
	static const wxColourProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColourProperty&>(value).GetEntity();
	}
	static wxColourProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColourProperty&>(value).GetEntityPtr();
	}
	static const wxColourProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColourProperty&>(value).GetEntityPtr();
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
