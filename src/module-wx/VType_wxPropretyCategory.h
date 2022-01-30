//==============================================================================
// VType_wxPropretyCategory.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPROPRETYCATEGORY_H
#define GURAX_MODULE_WX_VTYPE_WXPROPRETYCATEGORY_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/property.h>
#include "Util.h"
#include "VType_wxPGProperty.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPropretyCategory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPropretyCategory : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPropretyCategory VTYPE_wxPropretyCategory;

//------------------------------------------------------------------------------
// Value_wxPropretyCategory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPropretyCategory : public Value_wxPGProperty {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPropretyCategory);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPropretyCategory");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPropretyCategory() = delete;
	explicit Value_wxPropretyCategory(const wxPropretyCategory& entity, VType& vtype = VTYPE_wxPropretyCategory) :
		Value_wxPGProperty(entity, vtype) {}
	// Copy constructor/operator
	Value_wxPropretyCategory(const Value_wxPropretyCategory& src) = delete;
	Value_wxPropretyCategory& operator=(const Value_wxPropretyCategory& src) = delete;
	// Move constructor/operator
	Value_wxPropretyCategory(Value_wxPropretyCategory&& src) noexcept = delete;
	Value_wxPropretyCategory& operator=(Value_wxPropretyCategory&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPropretyCategory() = default;
public:
	wxPropretyCategory& GetEntity() { return reinterpret_cast<wxPropretyCategory&>(Value_wxPGProperty::GetEntity()); }
	const wxPropretyCategory& GetEntity() const { return reinterpret_cast<const wxPropretyCategory&>(Value_wxPGProperty::GetEntity()); }
	wxPropretyCategory* GetEntityPtr() { return reinterpret_cast<wxPropretyCategory*>(Value_wxPGProperty::GetEntityPtr()); }\
	const wxPropretyCategory* GetEntityPtr() const { return reinterpret_cast<const wxPropretyCategory*>(Value_wxPGProperty::GetEntityPtr()); }
public:
	static wxPropretyCategory& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPropretyCategory&>(value).GetEntity();
	}
	static const wxPropretyCategory& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPropretyCategory&>(value).GetEntity();
	}
	static wxPropretyCategory* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPropretyCategory&>(value).GetEntityPtr();
	}
	static const wxPropretyCategory* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPropretyCategory&>(value).GetEntityPtr();
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
