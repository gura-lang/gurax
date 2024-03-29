﻿//==============================================================================
// VType_wxDirDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDIRDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXDIRDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dirdlg.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDirDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDirDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDirDialog VTYPE_wxDirDialog;

//------------------------------------------------------------------------------
// Value_wxDirDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDirDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDirDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDirDialog");
protected:
	wxWeakRef<wxDirDialog> _pEntity;
public:
	class EntityT : public wxDirDialog {
	public:
		using wxDirDialog::wxDirDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDirDialog() = delete;
	explicit Value_wxDirDialog(wxDirDialog* pEntity, VType& vtype = VTYPE_wxDirDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDirDialog(const Value_wxDirDialog& src) = delete;
	Value_wxDirDialog& operator=(const Value_wxDirDialog& src) = delete;
	// Move constructor/operator
	Value_wxDirDialog(Value_wxDirDialog&& src) noexcept = delete;
	Value_wxDirDialog& operator=(Value_wxDirDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDirDialog() = default;
public:
	wxDirDialog& GetEntity() { return *_pEntity; }
	const wxDirDialog& GetEntity() const { return *_pEntity; }
	wxDirDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxDirDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxDirDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDirDialog&>(value).GetEntity();
	}
	static const wxDirDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDirDialog&>(value).GetEntity();
	}
	static wxDirDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDirDialog&>(value).GetEntityPtr();
	}
	static const wxDirDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDirDialog&>(value).GetEntityPtr();
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
