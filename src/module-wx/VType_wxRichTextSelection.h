//==============================================================================
// VType_wxRichTextSelection.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTSELECTION_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTSELECTION_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextbuffer.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextSelection
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextSelection : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextSelection VTYPE_wxRichTextSelection;

//------------------------------------------------------------------------------
// Value_wxRichTextSelection
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextSelection : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextSelection);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextSelection");
protected:
	wxRichTextSelection _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextSelection() = delete;
	explicit Value_wxRichTextSelection(const wxRichTextSelection& entity, VType& vtype = VTYPE_wxRichTextSelection) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxRichTextSelection(const Value_wxRichTextSelection& src) = delete;
	Value_wxRichTextSelection& operator=(const Value_wxRichTextSelection& src) = delete;
	// Move constructor/operator
	Value_wxRichTextSelection(Value_wxRichTextSelection&& src) noexcept = delete;
	Value_wxRichTextSelection& operator=(Value_wxRichTextSelection&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextSelection() = default;
public:
	wxRichTextSelection& GetEntity() { return _entity; }
	const wxRichTextSelection& GetEntity() const { return _entity; }
	wxRichTextSelection* GetEntityPtr() { return &_entity; }
	const wxRichTextSelection* GetEntityPtr() const { return &_entity; }
public:
	static wxRichTextSelection& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextSelection&>(value).GetEntity();
	}
	static const wxRichTextSelection& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextSelection&>(value).GetEntity();
	}
	static wxRichTextSelection* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextSelection&>(value).GetEntityPtr();
	}
	static const wxRichTextSelection* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextSelection&>(value).GetEntityPtr();
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
