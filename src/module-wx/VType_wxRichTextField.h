//==============================================================================
// VType_wxRichTextField.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTFIELD_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTFIELD_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextbuffer.h>
#include "Util.h"
#include "VType_wxRichTextParagraphLayoutBox.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextField
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextField : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextField VTYPE_wxRichTextField;

//------------------------------------------------------------------------------
// Value_wxRichTextField
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextField : public Value_wxRichTextParagraphLayoutBox {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextField);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextField");
protected:
	wxRichTextField* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextField() = delete;
	explicit Value_wxRichTextField(wxRichTextField* pEntity, VType& vtype = VTYPE_wxRichTextField) :
		Value_wxRichTextParagraphLayoutBox(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRichTextField(const Value_wxRichTextField& src) = delete;
	Value_wxRichTextField& operator=(const Value_wxRichTextField& src) = delete;
	// Move constructor/operator
	Value_wxRichTextField(Value_wxRichTextField&& src) noexcept = delete;
	Value_wxRichTextField& operator=(Value_wxRichTextField&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextField() = default;
public:
	wxRichTextField& GetEntity() { return *_pEntity; }
	const wxRichTextField& GetEntity() const { return *_pEntity; }
	wxRichTextField* GetEntityPtr() { return _pEntity; }
	const wxRichTextField* GetEntityPtr() const { return _pEntity; }
public:
	static wxRichTextField& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextField&>(value).GetEntity();
	}
	static const wxRichTextField& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextField&>(value).GetEntity();
	}
	static wxRichTextField* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextField&>(value).GetEntityPtr();
	}
	static const wxRichTextField* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextField&>(value).GetEntityPtr();
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