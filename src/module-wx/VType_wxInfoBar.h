﻿//==============================================================================
// VType_wxInfoBar.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXINFOBAR_H
#define GURAX_MODULE_WX_VTYPE_WXINFOBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/infobar.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxInfoBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxInfoBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxInfoBar VTYPE_wxInfoBar;

//------------------------------------------------------------------------------
// Value_wxInfoBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxInfoBar : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxInfoBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxInfoBar");
protected:
	wxWeakRef<wxInfoBar> _pEntity;
public:
	class EntityT : public wxInfoBar {
	public:
		using wxInfoBar::wxInfoBar;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxInfoBar() = delete;
	explicit Value_wxInfoBar(wxInfoBar* pEntity, VType& vtype = VTYPE_wxInfoBar) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxInfoBar(const Value_wxInfoBar& src) = delete;
	Value_wxInfoBar& operator=(const Value_wxInfoBar& src) = delete;
	// Move constructor/operator
	Value_wxInfoBar(Value_wxInfoBar&& src) noexcept = delete;
	Value_wxInfoBar& operator=(Value_wxInfoBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxInfoBar() = default;
public:
	wxInfoBar& GetEntity() { return *_pEntity; }
	const wxInfoBar& GetEntity() const { return *_pEntity; }
	wxInfoBar* GetEntityPtr() { return _pEntity.get(); }
	const wxInfoBar* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxInfoBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxInfoBar&>(value).GetEntity();
	}
	static const wxInfoBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxInfoBar&>(value).GetEntity();
	}
	static wxInfoBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxInfoBar&>(value).GetEntityPtr();
	}
	static const wxInfoBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxInfoBar&>(value).GetEntityPtr();
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
