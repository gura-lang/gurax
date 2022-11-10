﻿//==============================================================================
// VType_wxDatePickerCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDATEPICKERCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXDATEPICKERCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/datectrl.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDatePickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDatePickerCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDatePickerCtrl VTYPE_wxDatePickerCtrl;

//------------------------------------------------------------------------------
// Value_wxDatePickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDatePickerCtrl : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDatePickerCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDatePickerCtrl");
protected:
	wxWeakRef<wxDatePickerCtrl> _pEntity;
public:
	class EntityT : public wxDatePickerCtrl {
	public:
		using wxDatePickerCtrl::wxDatePickerCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxDatePickerCtrl() = delete;
	explicit Value_wxDatePickerCtrl(wxDatePickerCtrl* pEntity, VType& vtype = VTYPE_wxDatePickerCtrl) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxDatePickerCtrl(const Value_wxDatePickerCtrl& src) = delete;
	Value_wxDatePickerCtrl& operator=(const Value_wxDatePickerCtrl& src) = delete;
	// Move constructor/operator
	Value_wxDatePickerCtrl(Value_wxDatePickerCtrl&& src) noexcept = delete;
	Value_wxDatePickerCtrl& operator=(Value_wxDatePickerCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDatePickerCtrl() = default;
public:
	wxDatePickerCtrl& GetEntity() { return *_pEntity; }
	const wxDatePickerCtrl& GetEntity() const { return *_pEntity; }
	wxDatePickerCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxDatePickerCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxDatePickerCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDatePickerCtrl&>(value).GetEntity();
	}
	static const wxDatePickerCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDatePickerCtrl&>(value).GetEntity();
	}
	static wxDatePickerCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDatePickerCtrl&>(value).GetEntityPtr();
	}
	static const wxDatePickerCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDatePickerCtrl&>(value).GetEntityPtr();
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
