//==============================================================================
// VType_wxRichTextFormattingDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRICHTEXTFORMATTINGDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXRICHTEXTFORMATTINGDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextformatdlg.h>
#include "Util.h"
#include "VType_wxPropertySheetDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRichTextFormattingDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRichTextFormattingDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRichTextFormattingDialog VTYPE_wxRichTextFormattingDialog;

//------------------------------------------------------------------------------
// Value_wxRichTextFormattingDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRichTextFormattingDialog : public Value_wxPropertySheetDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRichTextFormattingDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRichTextFormattingDialog");
protected:
	wxWeakRef<wxRichTextFormattingDialog> _pEntity;
public:
	class EntityT : public wxRichTextFormattingDialog {
	public:
		using wxRichTextFormattingDialog::wxRichTextFormattingDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRichTextFormattingDialog() = delete;
	explicit Value_wxRichTextFormattingDialog(wxRichTextFormattingDialog* pEntity, VType& vtype = VTYPE_wxRichTextFormattingDialog) :
		Value_wxPropertySheetDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRichTextFormattingDialog(const Value_wxRichTextFormattingDialog& src) = delete;
	Value_wxRichTextFormattingDialog& operator=(const Value_wxRichTextFormattingDialog& src) = delete;
	// Move constructor/operator
	Value_wxRichTextFormattingDialog(Value_wxRichTextFormattingDialog&& src) noexcept = delete;
	Value_wxRichTextFormattingDialog& operator=(Value_wxRichTextFormattingDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRichTextFormattingDialog() = default;
public:
	wxRichTextFormattingDialog& GetEntity() { return *_pEntity; }
	const wxRichTextFormattingDialog& GetEntity() const { return *_pEntity; }
	wxRichTextFormattingDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxRichTextFormattingDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRichTextFormattingDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRichTextFormattingDialog&>(value).GetEntity();
	}
	static const wxRichTextFormattingDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRichTextFormattingDialog&>(value).GetEntity();
	}
	static wxRichTextFormattingDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRichTextFormattingDialog&>(value).GetEntityPtr();
	}
	static const wxRichTextFormattingDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRichTextFormattingDialog&>(value).GetEntityPtr();
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