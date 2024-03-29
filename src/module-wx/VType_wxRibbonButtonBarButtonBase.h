﻿//==============================================================================
// VType_wxRibbonButtonBarButtonBase.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONBUTTONBARBUTTONBASE_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONBUTTONBARBUTTONBASE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/ribbon/buttonbar.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonButtonBarButtonBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonButtonBarButtonBase : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonButtonBarButtonBase VTYPE_wxRibbonButtonBarButtonBase;

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBarButtonBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonButtonBarButtonBase : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonButtonBarButtonBase);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonButtonBarButtonBase");
protected:
	wxRibbonButtonBarButtonBase* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRibbonButtonBarButtonBase() = delete;
	explicit Value_wxRibbonButtonBarButtonBase(wxRibbonButtonBarButtonBase* pEntity, VType& vtype = VTYPE_wxRibbonButtonBarButtonBase) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxRibbonButtonBarButtonBase(const wxRibbonButtonBarButtonBase& entity, VType& vtype = VTYPE_wxRibbonButtonBarButtonBase) :
		Value_Object(vtype), _pEntity(const_cast<wxRibbonButtonBarButtonBase*>(&entity)) {}
	// Copy constructor/operator
	Value_wxRibbonButtonBarButtonBase(const Value_wxRibbonButtonBarButtonBase& src) = delete;
	Value_wxRibbonButtonBarButtonBase& operator=(const Value_wxRibbonButtonBarButtonBase& src) = delete;
	// Move constructor/operator
	Value_wxRibbonButtonBarButtonBase(Value_wxRibbonButtonBarButtonBase&& src) noexcept = delete;
	Value_wxRibbonButtonBarButtonBase& operator=(Value_wxRibbonButtonBarButtonBase&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonButtonBarButtonBase() = default;
public:
	wxRibbonButtonBarButtonBase& GetEntity() { return *_pEntity; }
	const wxRibbonButtonBarButtonBase& GetEntity() const { return *_pEntity; }
	wxRibbonButtonBarButtonBase* GetEntityPtr() { return _pEntity; }
	const wxRibbonButtonBarButtonBase* GetEntityPtr() const { return _pEntity; }
public:
	static wxRibbonButtonBarButtonBase& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonButtonBarButtonBase&>(value).GetEntity();
	}
	static const wxRibbonButtonBarButtonBase& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonButtonBarButtonBase&>(value).GetEntity();
	}
	static wxRibbonButtonBarButtonBase* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonButtonBarButtonBase&>(value).GetEntityPtr();
	}
	static const wxRibbonButtonBarButtonBase* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonButtonBarButtonBase&>(value).GetEntityPtr();
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
