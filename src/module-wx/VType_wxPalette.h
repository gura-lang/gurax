//==============================================================================
// VType_wxPalette.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPALETTE_H
#define GURAX_MODULE_WX_VTYPE_WXPALETTE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxGDIObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPalette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPalette : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPalette VTYPE_wxPalette;

//------------------------------------------------------------------------------
// Value_wxPalette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPalette : public Value_wxGDIObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPalette);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPalette");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPalette() = delete;
	explicit Value_wxPalette(const wxPalette& entity, VType& vtype = VTYPE_wxPalette) :
		Value_wxGDIObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxPalette(const Value_wxPalette& src) = delete;
	Value_wxPalette& operator=(const Value_wxPalette& src) = delete;
	// Move constructor/operator
	Value_wxPalette(Value_wxPalette&& src) noexcept = delete;
	Value_wxPalette& operator=(Value_wxPalette&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPalette() = default;
public:
	wxPalette& GetEntity() { return reinterpret_cast<wxPalette&>(Value_wxGDIObject::GetEntity()); }
	const wxPalette& GetEntity() const { return reinterpret_cast<const wxPalette&>(Value_wxGDIObject::GetEntity()); }
	wxPalette* GetEntityPtr() { return reinterpret_cast<wxPalette*>(Value_wxGDIObject::GetEntityPtr()); }\
	const wxPalette* GetEntityPtr() const { return reinterpret_cast<const wxPalette*>(Value_wxGDIObject::GetEntityPtr()); }
public:
	static wxPalette& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPalette&>(value).GetEntity();
	}
	static const wxPalette& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPalette&>(value).GetEntity();
	}
	static wxPalette* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPalette&>(value).GetEntityPtr();
	}
	static const wxPalette* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPalette&>(value).GetEntityPtr();
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
