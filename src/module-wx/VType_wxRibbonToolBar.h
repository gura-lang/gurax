﻿//==============================================================================
// VType_wxRibbonToolBar.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONTOOLBAR_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONTOOLBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/ribbon/toolbar.h>
#include "Util.h"
#include "VType_wxRibbonControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonToolBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonToolBar VTYPE_wxRibbonToolBar;

//------------------------------------------------------------------------------
// Value_wxRibbonToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonToolBar : public Value_wxRibbonControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonToolBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonToolBar");
protected:
	wxWeakRef<wxRibbonToolBar> _pEntity;
public:
	class EntityT : public wxRibbonToolBar {
	public:
		using wxRibbonToolBar::wxRibbonToolBar;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRibbonToolBar() = delete;
	explicit Value_wxRibbonToolBar(wxRibbonToolBar* pEntity, VType& vtype = VTYPE_wxRibbonToolBar) :
		Value_wxRibbonControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRibbonToolBar(const Value_wxRibbonToolBar& src) = delete;
	Value_wxRibbonToolBar& operator=(const Value_wxRibbonToolBar& src) = delete;
	// Move constructor/operator
	Value_wxRibbonToolBar(Value_wxRibbonToolBar&& src) noexcept = delete;
	Value_wxRibbonToolBar& operator=(Value_wxRibbonToolBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonToolBar() = default;
public:
	wxRibbonToolBar& GetEntity() { return *_pEntity; }
	const wxRibbonToolBar& GetEntity() const { return *_pEntity; }
	wxRibbonToolBar* GetEntityPtr() { return _pEntity.get(); }
	const wxRibbonToolBar* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRibbonToolBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonToolBar&>(value).GetEntity();
	}
	static const wxRibbonToolBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonToolBar&>(value).GetEntity();
	}
	static wxRibbonToolBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonToolBar&>(value).GetEntityPtr();
	}
	static const wxRibbonToolBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonToolBar&>(value).GetEntityPtr();
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
