﻿//==============================================================================
// VType_wxFileDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFILEDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXFILEDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFileDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFileDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFileDialog VTYPE_wxFileDialog;

//------------------------------------------------------------------------------
// Value_wxFileDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFileDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFileDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFileDialog");
protected:
	wxWeakRef<wxFileDialog> _pEntity;
public:
	class EntityT : public wxFileDialog {
	public:
		using wxFileDialog::wxFileDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFileDialog() = delete;
	explicit Value_wxFileDialog(wxFileDialog* pEntity, VType& vtype = VTYPE_wxFileDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxFileDialog(const Value_wxFileDialog& src) = delete;
	Value_wxFileDialog& operator=(const Value_wxFileDialog& src) = delete;
	// Move constructor/operator
	Value_wxFileDialog(Value_wxFileDialog&& src) noexcept = delete;
	Value_wxFileDialog& operator=(Value_wxFileDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFileDialog() = default;
public:
	wxFileDialog& GetEntity() { return *_pEntity; }
	const wxFileDialog& GetEntity() const { return *_pEntity; }
	wxFileDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxFileDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxFileDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFileDialog&>(value).GetEntity();
	}
	static const wxFileDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFileDialog&>(value).GetEntity();
	}
	static wxFileDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFileDialog&>(value).GetEntityPtr();
	}
	static const wxFileDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFileDialog&>(value).GetEntityPtr();
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
