//==============================================================================
// VType_wxFontProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONTPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXFONTPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/advprops.h>
#include "Util.h"
#include "VType_wxPGProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFontProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFontProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFontProperty VTYPE_wxFontProperty;

//------------------------------------------------------------------------------
// Value_wxFontProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFontProperty : public Value_wxPGProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFontProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFontProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFontProperty() = delete;
	explicit Value_wxFontProperty(const wxFontProperty& entity, VType& vtype = VTYPE_wxFontProperty) :
		Value_wxPGProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxFontProperty(const Value_wxFontProperty& src) = delete;
	Value_wxFontProperty& operator=(const Value_wxFontProperty& src) = delete;
	// Move constructor/operator
	Value_wxFontProperty(Value_wxFontProperty&& src) noexcept = delete;
	Value_wxFontProperty& operator=(Value_wxFontProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFontProperty() = default;
public:
	wxFontProperty& GetEntity() { return reinterpret_cast<wxFontProperty&>(Value_wxPGProperty::GetEntity()); }
	const wxFontProperty& GetEntity() const { return reinterpret_cast<const wxFontProperty&>(Value_wxPGProperty::GetEntity()); }
	wxFontProperty* GetEntityPtr() { return reinterpret_cast<wxFontProperty*>(Value_wxPGProperty::GetEntityPtr()); }\
	const wxFontProperty* GetEntityPtr() const { return reinterpret_cast<const wxFontProperty*>(Value_wxPGProperty::GetEntityPtr()); }
public:
	static wxFontProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFontProperty&>(value).GetEntity();
	}
	static const wxFontProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFontProperty&>(value).GetEntity();
	}
	static wxFontProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFontProperty&>(value).GetEntityPtr();
	}
	static const wxFontProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFontProperty&>(value).GetEntityPtr();
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