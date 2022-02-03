//==============================================================================
// VType_wxRichTextStyleSheet.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTSTYLESHEET_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTSTYLESHEET_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextstyles.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextStyleSheet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextStyleSheet : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextStyleSheet VTYPE_wxRichTextStyleSheet;

//------------------------------------------------------------------------------
// Value_wxRichTextStyleSheet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextStyleSheet : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextStyleSheet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextStyleSheet");
protected:
	wxRichTextStyleSheet _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextStyleSheet() = delete;
	explicit Value_wxRichTextStyleSheet(const wxRichTextStyleSheet& entity, VType& vtype = VTYPE_wxRichTextStyleSheet) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxRichTextStyleSheet(const Value_wxRichTextStyleSheet& src) = delete;
	Value_wxRichTextStyleSheet& operator=(const Value_wxRichTextStyleSheet& src) = delete;
	// Move constructor/operator
	Value_wxRichTextStyleSheet(Value_wxRichTextStyleSheet&& src) noexcept = delete;
	Value_wxRichTextStyleSheet& operator=(Value_wxRichTextStyleSheet&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextStyleSheet() = default;
public:
	wxRichTextStyleSheet& GetEntity() { return _entity; }
	const wxRichTextStyleSheet& GetEntity() const { return _entity; }
	wxRichTextStyleSheet* GetEntityPtr() { return &_entity; }
	const wxRichTextStyleSheet* GetEntityPtr() const { return &_entity; }
public:
	static wxRichTextStyleSheet& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextStyleSheet&>(value).GetEntity();
	}
	static const wxRichTextStyleSheet& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextStyleSheet&>(value).GetEntity();
	}
	static wxRichTextStyleSheet* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextStyleSheet&>(value).GetEntityPtr();
	}
	static const wxRichTextStyleSheet* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextStyleSheet&>(value).GetEntityPtr();
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
