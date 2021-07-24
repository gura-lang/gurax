//==============================================================================
// VType_wxRichTextAttr.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTATTR_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTATTR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "Util.h"
#include "VType_wxTextAttr.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextAttr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextAttr VTYPE_wxRichTextAttr;

//------------------------------------------------------------------------------
// Value_wxRichTextAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextAttr : public Value_wxTextAttr {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextAttr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextAttr");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextAttr() = delete;
	explicit Value_wxRichTextAttr(const wxTextAttr& entity, VType& vtype = VTYPE_wxRichTextAttr) :
		Value_wxTextAttr(entity, vtype) {}
	// Copy constructor/operator
	Value_wxRichTextAttr(const Value_wxRichTextAttr& src) = delete;
	Value_wxRichTextAttr& operator=(const Value_wxRichTextAttr& src) = delete;
	// Move constructor/operator
	Value_wxRichTextAttr(Value_wxRichTextAttr&& src) noexcept = delete;
	Value_wxRichTextAttr& operator=(Value_wxRichTextAttr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextAttr() = default;
public:
	wxRichTextAttr& GetEntity() {
		return reinterpret_cast<wxRichTextAttr&>(Value_wxTextAttr::GetEntity());
	}
	const wxRichTextAttr& GetEntity() const {
		return reinterpret_cast<const wxRichTextAttr&>(Value_wxTextAttr::GetEntity());
	}
	wxRichTextAttr* GetEntityPtr() {
		return reinterpret_cast<wxRichTextAttr*>(Value_wxTextAttr::GetEntityPtr());
	}
	const wxRichTextAttr* GetEntityPtr() const {
		return reinterpret_cast<const wxRichTextAttr*>(Value_wxTextAttr::GetEntityPtr());
	}
public:
	static wxRichTextAttr& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextAttr&>(value).GetEntity();
	}
	static const wxRichTextAttr& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextAttr&>(value).GetEntity();
	}
	static wxRichTextAttr* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextAttr&>(value).GetEntityPtr();
	}
	static const wxRichTextAttr* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextAttr&>(value).GetEntityPtr();
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
