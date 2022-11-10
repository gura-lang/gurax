﻿//==============================================================================
// VType_wxAuiToolBar.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUITOOLBAR_H
#define GURAX_MODULE_WX_VTYPE_WXAUITOOLBAR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/auibar.h>
#include "Util.h"
#include "VType_wxControl.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiToolBar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiToolBar VTYPE_wxAuiToolBar;

//------------------------------------------------------------------------------
// Value_wxAuiToolBar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiToolBar : public Value_wxControl {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiToolBar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiToolBar");
protected:
	wxWeakRef<wxAuiToolBar> _pEntity;
public:
	class EntityT : public wxAuiToolBar {
	public:
		using wxAuiToolBar::wxAuiToolBar;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxAuiToolBar() = delete;
	explicit Value_wxAuiToolBar(wxAuiToolBar* pEntity, VType& vtype = VTYPE_wxAuiToolBar) :
		Value_wxControl(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxAuiToolBar(const Value_wxAuiToolBar& src) = delete;
	Value_wxAuiToolBar& operator=(const Value_wxAuiToolBar& src) = delete;
	// Move constructor/operator
	Value_wxAuiToolBar(Value_wxAuiToolBar&& src) noexcept = delete;
	Value_wxAuiToolBar& operator=(Value_wxAuiToolBar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiToolBar() = default;
public:
	wxAuiToolBar& GetEntity() { return *_pEntity; }
	const wxAuiToolBar& GetEntity() const { return *_pEntity; }
	wxAuiToolBar* GetEntityPtr() { return _pEntity.get(); }
	const wxAuiToolBar* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxAuiToolBar& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiToolBar&>(value).GetEntity();
	}
	static const wxAuiToolBar& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiToolBar&>(value).GetEntity();
	}
	static wxAuiToolBar* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiToolBar&>(value).GetEntityPtr();
	}
	static const wxAuiToolBar* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiToolBar&>(value).GetEntityPtr();
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
