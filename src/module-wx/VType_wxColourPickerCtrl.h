﻿//==============================================================================
// VType_wxColourPickerCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOURPICKERCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOURPICKERCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/clrpicker.h>
#include "Util.h"
#include "VType_wxPickerBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColourPickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColourPickerCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxColourPickerCtrl VTYPE_wxColourPickerCtrl;

//------------------------------------------------------------------------------
// Value_wxColourPickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColourPickerCtrl : public Value_wxPickerBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColourPickerCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColourPickerCtrl");
protected:
	wxWeakRef<wxColourPickerCtrl> _pEntity;
public:
	class EntityT : public wxColourPickerCtrl {
	public:
		using wxColourPickerCtrl::wxColourPickerCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxColourPickerCtrl() = delete;
	explicit Value_wxColourPickerCtrl(wxColourPickerCtrl* pEntity, VType& vtype = VTYPE_wxColourPickerCtrl) :
		Value_wxPickerBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxColourPickerCtrl(const Value_wxColourPickerCtrl& src) = delete;
	Value_wxColourPickerCtrl& operator=(const Value_wxColourPickerCtrl& src) = delete;
	// Move constructor/operator
	Value_wxColourPickerCtrl(Value_wxColourPickerCtrl&& src) noexcept = delete;
	Value_wxColourPickerCtrl& operator=(Value_wxColourPickerCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColourPickerCtrl() = default;
public:
	wxColourPickerCtrl& GetEntity() { return *_pEntity; }
	const wxColourPickerCtrl& GetEntity() const { return *_pEntity; }
	wxColourPickerCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxColourPickerCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxColourPickerCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColourPickerCtrl&>(value).GetEntity();
	}
	static const wxColourPickerCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColourPickerCtrl&>(value).GetEntity();
	}
	static wxColourPickerCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColourPickerCtrl&>(value).GetEntityPtr();
	}
	static const wxColourPickerCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColourPickerCtrl&>(value).GetEntityPtr();
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
