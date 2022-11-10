﻿//==============================================================================
// VType_wxPGArrayStringEditorDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPGARRAYSTRINGEDITORDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXPGARRAYSTRINGEDITORDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/propgrid/props.h>
#include "Util.h"
#include "VType_wxPGArrayEditorDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPGArrayStringEditorDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPGArrayStringEditorDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPGArrayStringEditorDialog VTYPE_wxPGArrayStringEditorDialog;

//------------------------------------------------------------------------------
// Value_wxPGArrayStringEditorDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPGArrayStringEditorDialog : public Value_wxPGArrayEditorDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPGArrayStringEditorDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPGArrayStringEditorDialog");
protected:
	wxWeakRef<wxPGArrayStringEditorDialog> _pEntity;
public:
	class EntityT : public wxPGArrayStringEditorDialog {
	public:
		using wxPGArrayStringEditorDialog::wxPGArrayStringEditorDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPGArrayStringEditorDialog() = delete;
	explicit Value_wxPGArrayStringEditorDialog(wxPGArrayStringEditorDialog* pEntity, VType& vtype = VTYPE_wxPGArrayStringEditorDialog) :
		Value_wxPGArrayEditorDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxPGArrayStringEditorDialog(const Value_wxPGArrayStringEditorDialog& src) = delete;
	Value_wxPGArrayStringEditorDialog& operator=(const Value_wxPGArrayStringEditorDialog& src) = delete;
	// Move constructor/operator
	Value_wxPGArrayStringEditorDialog(Value_wxPGArrayStringEditorDialog&& src) noexcept = delete;
	Value_wxPGArrayStringEditorDialog& operator=(Value_wxPGArrayStringEditorDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPGArrayStringEditorDialog() = default;
public:
	wxPGArrayStringEditorDialog& GetEntity() { return *_pEntity; }
	const wxPGArrayStringEditorDialog& GetEntity() const { return *_pEntity; }
	wxPGArrayStringEditorDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxPGArrayStringEditorDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxPGArrayStringEditorDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPGArrayStringEditorDialog&>(value).GetEntity();
	}
	static const wxPGArrayStringEditorDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPGArrayStringEditorDialog&>(value).GetEntity();
	}
	static wxPGArrayStringEditorDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPGArrayStringEditorDialog&>(value).GetEntityPtr();
	}
	static const wxPGArrayStringEditorDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPGArrayStringEditorDialog&>(value).GetEntityPtr();
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
