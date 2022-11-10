﻿//==============================================================================
// VType_wxFontPickerCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFONTPICKERCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXFONTPICKERCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/fontpicker.h>
#include "Util.h"
#include "VType_wxPickerBase.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFontPickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFontPickerCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFontPickerCtrl VTYPE_wxFontPickerCtrl;

//------------------------------------------------------------------------------
// Value_wxFontPickerCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFontPickerCtrl : public Value_wxPickerBase {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFontPickerCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFontPickerCtrl");
protected:
	wxWeakRef<wxFontPickerCtrl> _pEntity;
public:
	class EntityT : public wxFontPickerCtrl {
	public:
		using wxFontPickerCtrl::wxFontPickerCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxFontPickerCtrl() = delete;
	explicit Value_wxFontPickerCtrl(wxFontPickerCtrl* pEntity, VType& vtype = VTYPE_wxFontPickerCtrl) :
		Value_wxPickerBase(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxFontPickerCtrl(const Value_wxFontPickerCtrl& src) = delete;
	Value_wxFontPickerCtrl& operator=(const Value_wxFontPickerCtrl& src) = delete;
	// Move constructor/operator
	Value_wxFontPickerCtrl(Value_wxFontPickerCtrl&& src) noexcept = delete;
	Value_wxFontPickerCtrl& operator=(Value_wxFontPickerCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFontPickerCtrl() = default;
public:
	wxFontPickerCtrl& GetEntity() { return *_pEntity; }
	const wxFontPickerCtrl& GetEntity() const { return *_pEntity; }
	wxFontPickerCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxFontPickerCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxFontPickerCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFontPickerCtrl&>(value).GetEntity();
	}
	static const wxFontPickerCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFontPickerCtrl&>(value).GetEntity();
	}
	static wxFontPickerCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFontPickerCtrl&>(value).GetEntityPtr();
	}
	static const wxFontPickerCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFontPickerCtrl&>(value).GetEntityPtr();
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
