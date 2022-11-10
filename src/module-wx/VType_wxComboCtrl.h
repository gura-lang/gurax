﻿//==============================================================================
// VType_wxComboCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOMBOCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXCOMBOCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/combo.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxComboCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxComboCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxComboCtrl VTYPE_wxComboCtrl;

//------------------------------------------------------------------------------
// Value_wxComboCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxComboCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxComboCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxComboCtrl");
protected:
	wxWeakRef<wxComboCtrl> _pEntity;
public:
	class EntityT : public wxComboCtrl {
	public:
		using wxComboCtrl::wxComboCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxComboCtrl() = delete;
	explicit Value_wxComboCtrl(wxComboCtrl* pEntity, VType& vtype = VTYPE_wxComboCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxComboCtrl(const Value_wxComboCtrl& src) = delete;
	Value_wxComboCtrl& operator=(const Value_wxComboCtrl& src) = delete;
	// Move constructor/operator
	Value_wxComboCtrl(Value_wxComboCtrl&& src) noexcept = delete;
	Value_wxComboCtrl& operator=(Value_wxComboCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxComboCtrl() = default;
public:
	wxComboCtrl& GetEntity() { return *_pEntity; }
	const wxComboCtrl& GetEntity() const { return *_pEntity; }
	wxComboCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxComboCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxComboCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxComboCtrl&>(value).GetEntity();
	}
	static const wxComboCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxComboCtrl&>(value).GetEntity();
	}
	static wxComboCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxComboCtrl&>(value).GetEntityPtr();
	}
	static const wxComboCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxComboCtrl&>(value).GetEntityPtr();
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
