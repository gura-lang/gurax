﻿//==============================================================================
// VType_wxRearrangeDialog.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREARRANGEDIALOG_H
#define GURAX_MODULE_WX_VTYPE_WXREARRANGEDIALOG_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/rearrangectrl.h>
#include "Util.h"
#include "VType_wxDialog.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRearrangeDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRearrangeDialog : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRearrangeDialog VTYPE_wxRearrangeDialog;

//------------------------------------------------------------------------------
// Value_wxRearrangeDialog
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRearrangeDialog : public Value_wxDialog {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRearrangeDialog);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRearrangeDialog");
protected:
	wxWeakRef<wxRearrangeDialog> _pEntity;
public:
	class EntityT : public wxRearrangeDialog {
	public:
		using wxRearrangeDialog::wxRearrangeDialog;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRearrangeDialog() = delete;
	explicit Value_wxRearrangeDialog(wxRearrangeDialog* pEntity, VType& vtype = VTYPE_wxRearrangeDialog) :
		Value_wxDialog(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRearrangeDialog(const Value_wxRearrangeDialog& src) = delete;
	Value_wxRearrangeDialog& operator=(const Value_wxRearrangeDialog& src) = delete;
	// Move constructor/operator
	Value_wxRearrangeDialog(Value_wxRearrangeDialog&& src) noexcept = delete;
	Value_wxRearrangeDialog& operator=(Value_wxRearrangeDialog&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRearrangeDialog() = default;
public:
	wxRearrangeDialog& GetEntity() { return *_pEntity; }
	const wxRearrangeDialog& GetEntity() const { return *_pEntity; }
	wxRearrangeDialog* GetEntityPtr() { return _pEntity.get(); }
	const wxRearrangeDialog* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRearrangeDialog& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRearrangeDialog&>(value).GetEntity();
	}
	static const wxRearrangeDialog& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeDialog&>(value).GetEntity();
	}
	static wxRearrangeDialog* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRearrangeDialog&>(value).GetEntityPtr();
	}
	static const wxRearrangeDialog* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeDialog&>(value).GetEntityPtr();
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
