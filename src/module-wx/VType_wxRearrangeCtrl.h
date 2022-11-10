﻿//==============================================================================
// VType_wxRearrangeCtrl.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREARRANGECTRL_H
#define GURAX_MODULE_WX_VTYPE_WXREARRANGECTRL_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/rearrangectrl.h>
#include "Util.h"
#include "VType_wxPanel.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRearrangeCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRearrangeCtrl : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRearrangeCtrl VTYPE_wxRearrangeCtrl;

//------------------------------------------------------------------------------
// Value_wxRearrangeCtrl
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRearrangeCtrl : public Value_wxPanel {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRearrangeCtrl);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRearrangeCtrl");
protected:
	wxWeakRef<wxRearrangeCtrl> _pEntity;
public:
	class EntityT : public wxRearrangeCtrl {
	public:
		using wxRearrangeCtrl::wxRearrangeCtrl;
	public:
		EntityCore core_gurax;
	};
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRearrangeCtrl() = delete;
	explicit Value_wxRearrangeCtrl(wxRearrangeCtrl* pEntity, VType& vtype = VTYPE_wxRearrangeCtrl) :
		Value_wxPanel(pEntity, vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_wxRearrangeCtrl(const Value_wxRearrangeCtrl& src) = delete;
	Value_wxRearrangeCtrl& operator=(const Value_wxRearrangeCtrl& src) = delete;
	// Move constructor/operator
	Value_wxRearrangeCtrl(Value_wxRearrangeCtrl&& src) noexcept = delete;
	Value_wxRearrangeCtrl& operator=(Value_wxRearrangeCtrl&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRearrangeCtrl() = default;
public:
	wxRearrangeCtrl& GetEntity() { return *_pEntity; }
	const wxRearrangeCtrl& GetEntity() const { return *_pEntity; }
	wxRearrangeCtrl* GetEntityPtr() { return _pEntity.get(); }
	const wxRearrangeCtrl* GetEntityPtr() const { return _pEntity.get(); }
public:
	static wxRearrangeCtrl& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRearrangeCtrl&>(value).GetEntity();
	}
	static const wxRearrangeCtrl& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeCtrl&>(value).GetEntity();
	}
	static wxRearrangeCtrl* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRearrangeCtrl&>(value).GetEntityPtr();
	}
	static const wxRearrangeCtrl* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRearrangeCtrl&>(value).GetEntityPtr();
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
