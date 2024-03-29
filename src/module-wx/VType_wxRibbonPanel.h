﻿//==============================================================================
// VType_wxRibbonPanel.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONPANEL_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONPANEL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/ribbon/panel.h>
#include "Util.h"
#include "VType_wxRibbonControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonPanel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonPanel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonPanel VTYPE_wxRibbonPanel;

//------------------------------------------------------------------------------
// Value_wxRibbonPanel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonPanel : public Value_wxRibbonControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonPanel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonPanel");
protected:
	wxWeakRef<wxRibbonPanel> _pEntity;
public:
	class EntityT : public wxRibbonPanel {
	public:
		using wxRibbonPanel::wxRibbonPanel;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRibbonPanel() = delete;
	explicit Value_wxRibbonPanel(wxRibbonPanel* pEntity, VType& vtype = VTYPE_wxRibbonPanel) :
		Value_wxRibbonControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRibbonPanel(const Value_wxRibbonPanel& src) = delete;
	Value_wxRibbonPanel& operator=(const Value_wxRibbonPanel& src) = delete;
	// Move constructor/operator
	Value_wxRibbonPanel(Value_wxRibbonPanel&& src) noexcept = delete;
	Value_wxRibbonPanel& operator=(Value_wxRibbonPanel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonPanel() = default;
public:
	wxRibbonPanel& GetEntity() { return *_pEntity; }
	const wxRibbonPanel& GetEntity() const { return *_pEntity; }
	wxRibbonPanel* GetEntityPtr() { return _pEntity.get(); }
	const wxRibbonPanel* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRibbonPanel& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonPanel&>(value).GetEntity();
	}
	static const wxRibbonPanel& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonPanel&>(value).GetEntity();
	}
	static wxRibbonPanel* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonPanel&>(value).GetEntityPtr();
	}
	static const wxRibbonPanel* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonPanel&>(value).GetEntityPtr();
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
