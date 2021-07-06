//==============================================================================
// VType_wxFont.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONT_H
#define GURAX_MODULE_WX_VTYPE_WXFONT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxGDIObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFont
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFont : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFont VTYPE_wxFont;

//------------------------------------------------------------------------------
// Value_wxFont
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFont : public Value_wxGDIObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFont);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFont");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFont() = delete;
	explicit Value_wxFont(const wxObject& entity, VType& vtype = VTYPE_wxFont) :
		Value_wxGDIObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxFont(const Value_wxFont& src) = delete;
	Value_wxFont& operator=(const Value_wxFont& src) = delete;
	// Move constructor/operator
	Value_wxFont(Value_wxFont&& src) noexcept = delete;
	Value_wxFont& operator=(Value_wxFont&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFont() = default;
public:
	wxFont& GetEntity() {
		return reinterpret_cast<wxFont&>(Value_wxObject::GetEntity());
	}
	const wxFont& GetEntity() const {
		return reinterpret_cast<const wxFont&>(Value_wxObject::GetEntity());
	}
	wxFont* GetEntityPtr() {
		return reinterpret_cast<wxFont*>(Value_wxObject::GetEntityPtr());
	}
	const wxFont* GetEntityPtr() const {
		return reinterpret_cast<const wxFont*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxFont& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFont&>(value).GetEntity();
	}
	static const wxFont& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFont&>(value).GetEntity();
	}
	static wxFont* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFont&>(value).GetEntityPtr();
	}
	static const wxFont* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFont&>(value).GetEntityPtr();
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