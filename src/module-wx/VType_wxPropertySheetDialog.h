﻿//==============================================================================
// VType_wxPropertySheetDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPROPERTYSHEETDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXPROPERTYSHEETDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propdlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPropertySheetDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPropertySheetDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPropertySheetDialog VTYPE_wxPropertySheetDialog;

//------------------------------------------------------------------------------
// Value_wxPropertySheetDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPropertySheetDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPropertySheetDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPropertySheetDialog");
protected:
	wxWeakRef<wxPropertySheetDialog> _pEntity;
public:
	class EntityT : public wxPropertySheetDialog {
	public:
		using wxPropertySheetDialog::wxPropertySheetDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPropertySheetDialog() = delete;
	explicit Value_wxPropertySheetDialog(wxPropertySheetDialog* pEntity, VType& vtype = VTYPE_wxPropertySheetDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxPropertySheetDialog(const Value_wxPropertySheetDialog& src) = delete;
	Value_wxPropertySheetDialog& operator=(const Value_wxPropertySheetDialog& src) = delete;
	// Move constructor/operator
	Value_wxPropertySheetDialog(Value_wxPropertySheetDialog&& src) noexcept = delete;
	Value_wxPropertySheetDialog& operator=(Value_wxPropertySheetDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPropertySheetDialog() = default;
public:
	wxPropertySheetDialog& GetEntity() { return *_pEntity; }
	const wxPropertySheetDialog& GetEntity() const { return *_pEntity; }
	wxPropertySheetDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxPropertySheetDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxPropertySheetDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPropertySheetDialog&>(value).GetEntity();
	}
	static const wxPropertySheetDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPropertySheetDialog&>(value).GetEntity();
	}
	static wxPropertySheetDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPropertySheetDialog&>(value).GetEntityPtr();
	}
	static const wxPropertySheetDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPropertySheetDialog&>(value).GetEntityPtr();
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
