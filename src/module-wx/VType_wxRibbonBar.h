﻿//==============================================================================
// VType_wxRibbonBar.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONBAR_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/ribbon/bar.h>
#include "Util.h"
#include "VType_wxRibbonControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonBar VTYPE_wxRibbonBar;

//------------------------------------------------------------------------------
// Value_wxRibbonBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonBar : public Value_wxRibbonControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonBar");
protected:
	wxWeakRef<wxRibbonBar> _pEntity;
public:
	class EntityT : public wxRibbonBar {
	public:
		using wxRibbonBar::wxRibbonBar;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRibbonBar() = delete;
	explicit Value_wxRibbonBar(wxRibbonBar* pEntity, VType& vtype = VTYPE_wxRibbonBar) :
		Value_wxRibbonControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRibbonBar(const Value_wxRibbonBar& src) = delete;
	Value_wxRibbonBar& operator=(const Value_wxRibbonBar& src) = delete;
	// Move constructor/operator
	Value_wxRibbonBar(Value_wxRibbonBar&& src) noexcept = delete;
	Value_wxRibbonBar& operator=(Value_wxRibbonBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonBar() = default;
public:
	wxRibbonBar& GetEntity() { return *_pEntity; }
	const wxRibbonBar& GetEntity() const { return *_pEntity; }
	wxRibbonBar* GetEntityPtr() { return _pEntity.get(); }
	const wxRibbonBar* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRibbonBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonBar&>(value).GetEntity();
	}
	static const wxRibbonBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonBar&>(value).GetEntity();
	}
	static wxRibbonBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonBar&>(value).GetEntityPtr();
	}
	static const wxRibbonBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonBar&>(value).GetEntityPtr();
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
