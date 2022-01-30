//==============================================================================
// VType_wxEditEnumProperty.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEDITENUMPROPERTY_H
#define GURAX_MODULE_WX_VTYPE_WXEDITENUMPROPERTY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/props.h>
#include "Util.h"
#include "VType_wxEnumProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxEditEnumProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxEditEnumProperty : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxEditEnumProperty VTYPE_wxEditEnumProperty;

//------------------------------------------------------------------------------
// Value_wxEditEnumProperty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxEditEnumProperty : public Value_wxEnumProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEditEnumProperty);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEditEnumProperty");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxEditEnumProperty() = delete;
	explicit Value_wxEditEnumProperty(const wxEditEnumProperty& entity, VType& vtype = VTYPE_wxEditEnumProperty) :
		Value_wxEnumProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxEditEnumProperty(const Value_wxEditEnumProperty& src) = delete;
	Value_wxEditEnumProperty& operator=(const Value_wxEditEnumProperty& src) = delete;
	// Move constructor/operator
	Value_wxEditEnumProperty(Value_wxEditEnumProperty&& src) noexcept = delete;
	Value_wxEditEnumProperty& operator=(Value_wxEditEnumProperty&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxEditEnumProperty() = default;
public:
	wxEditEnumProperty& GetEntity() { return reinterpret_cast<wxEditEnumProperty&>(Value_wxEnumProperty::GetEntity()); }
	const wxEditEnumProperty& GetEntity() const { return reinterpret_cast<const wxEditEnumProperty&>(Value_wxEnumProperty::GetEntity()); }
	wxEditEnumProperty* GetEntityPtr() { return reinterpret_cast<wxEditEnumProperty*>(Value_wxEnumProperty::GetEntityPtr()); }\
	const wxEditEnumProperty* GetEntityPtr() const { return reinterpret_cast<const wxEditEnumProperty*>(Value_wxEnumProperty::GetEntityPtr()); }
public:
	static wxEditEnumProperty& GetEntity(Value& value) {
		return dynamic_cast<Value_wxEditEnumProperty&>(value).GetEntity();
	}
	static const wxEditEnumProperty& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEditEnumProperty&>(value).GetEntity();
	}
	static wxEditEnumProperty* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxEditEnumProperty&>(value).GetEntityPtr();
	}
	static const wxEditEnumProperty* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxEditEnumProperty&>(value).GetEntityPtr();
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
