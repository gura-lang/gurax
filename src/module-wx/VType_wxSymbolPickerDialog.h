﻿//==============================================================================
// VType_wxSymbolPickerDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSYMBOLPICKERDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXSYMBOLPICKERDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/richtext/richtextsymboldlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSymbolPickerDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSymbolPickerDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSymbolPickerDialog VTYPE_wxSymbolPickerDialog;

//------------------------------------------------------------------------------
// Value_wxSymbolPickerDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSymbolPickerDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSymbolPickerDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSymbolPickerDialog");
protected:
	wxWeakRef<wxSymbolPickerDialog> _pEntity;
public:
	class EntityT : public wxSymbolPickerDialog {
	public:
		using wxSymbolPickerDialog::wxSymbolPickerDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxSymbolPickerDialog() = delete;
	explicit Value_wxSymbolPickerDialog(wxSymbolPickerDialog* pEntity, VType& vtype = VTYPE_wxSymbolPickerDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxSymbolPickerDialog(const Value_wxSymbolPickerDialog& src) = delete;
	Value_wxSymbolPickerDialog& operator=(const Value_wxSymbolPickerDialog& src) = delete;
	// Move constructor/operator
	Value_wxSymbolPickerDialog(Value_wxSymbolPickerDialog&& src) noexcept = delete;
	Value_wxSymbolPickerDialog& operator=(Value_wxSymbolPickerDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSymbolPickerDialog() = default;
public:
	wxSymbolPickerDialog& GetEntity() { return *_pEntity; }
	const wxSymbolPickerDialog& GetEntity() const { return *_pEntity; }
	wxSymbolPickerDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxSymbolPickerDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxSymbolPickerDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSymbolPickerDialog&>(value).GetEntity();
	}
	static const wxSymbolPickerDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSymbolPickerDialog&>(value).GetEntity();
	}
	static wxSymbolPickerDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSymbolPickerDialog&>(value).GetEntityPtr();
	}
	static const wxSymbolPickerDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSymbolPickerDialog&>(value).GetEntityPtr();
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
