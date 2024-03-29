﻿//==============================================================================
// VType_wxTreeListCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTREELISTCTRL_H
#define GURAX_MODULE_WX_VTYPE_WXTREELISTCTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/treelist.h>
#include "Util.h"
#include "VType_wxWindow.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTreeListCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTreeListCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTreeListCtrl VTYPE_wxTreeListCtrl;

//------------------------------------------------------------------------------
// Value_wxTreeListCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTreeListCtrl : public Value_wxWindow {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTreeListCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTreeListCtrl");
protected:
	wxWeakRef<wxTreeListCtrl> _pEntity;
public:
	class EntityT : public wxTreeListCtrl {
	public:
		using wxTreeListCtrl::wxTreeListCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxTreeListCtrl() = delete;
	explicit Value_wxTreeListCtrl(wxTreeListCtrl* pEntity, VType& vtype = VTYPE_wxTreeListCtrl) :
		Value_wxWindow(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxTreeListCtrl(const Value_wxTreeListCtrl& src) = delete;
	Value_wxTreeListCtrl& operator=(const Value_wxTreeListCtrl& src) = delete;
	// Move constructor/operator
	Value_wxTreeListCtrl(Value_wxTreeListCtrl&& src) noexcept = delete;
	Value_wxTreeListCtrl& operator=(Value_wxTreeListCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTreeListCtrl() = default;
public:
	wxTreeListCtrl& GetEntity() { return *_pEntity; }
	const wxTreeListCtrl& GetEntity() const { return *_pEntity; }
	wxTreeListCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxTreeListCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxTreeListCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxTreeListCtrl&>(value).GetEntity();
	}
	static const wxTreeListCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTreeListCtrl&>(value).GetEntity();
	}
	static wxTreeListCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxTreeListCtrl&>(value).GetEntityPtr();
	}
	static const wxTreeListCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxTreeListCtrl&>(value).GetEntityPtr();
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
