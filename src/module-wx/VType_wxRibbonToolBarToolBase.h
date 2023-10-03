﻿//==============================================================================
// VType_wxRibbonToolBarToolBase.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXRIBBONTOOLBARTOOLBASE_H
#define GURAX_MODULE_WX_VTYPE_WXRIBBONTOOLBARTOOLBASE_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRibbonToolBarToolBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRibbonToolBarToolBase : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxRibbonToolBarToolBase VTYPE_wxRibbonToolBarToolBase;

//------------------------------------------------------------------------------
// Value_wxRibbonToolBarToolBase
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRibbonToolBarToolBase : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRibbonToolBarToolBase);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRibbonToolBarToolBase");
protected:
	wxRibbonToolBarToolBase* _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRibbonToolBarToolBase() = delete;
	explicit Value_wxRibbonToolBarToolBase(wxRibbonToolBarToolBase* pEntity, VType& vtype = VTYPE_wxRibbonToolBarToolBase) :
		Value_Object(vtype), _pEntity(pEntity) {}
	explicit Value_wxRibbonToolBarToolBase(const wxRibbonToolBarToolBase& entity, VType& vtype = VTYPE_wxRibbonToolBarToolBase) :
		Value_Object(vtype), _pEntity(const_cast<wxRibbonToolBarToolBase*>(&entity)) {}
	// Copy constructor/operator
	Value_wxRibbonToolBarToolBase(const Value_wxRibbonToolBarToolBase& src) = delete;
	Value_wxRibbonToolBarToolBase& operator=(const Value_wxRibbonToolBarToolBase& src) = delete;
	// Move constructor/operator
	Value_wxRibbonToolBarToolBase(Value_wxRibbonToolBarToolBase&& src) noexcept = delete;
	Value_wxRibbonToolBarToolBase& operator=(Value_wxRibbonToolBarToolBase&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRibbonToolBarToolBase() = default;
public:
	wxRibbonToolBarToolBase& GetEntity() { return *_pEntity; }
	const wxRibbonToolBarToolBase& GetEntity() const { return *_pEntity; }
	wxRibbonToolBarToolBase* GetEntityPtr() { return _pEntity; }
	const wxRibbonToolBarToolBase* GetEntityPtr() const { return _pEntity; }
public:
	static wxRibbonToolBarToolBase& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRibbonToolBarToolBase&>(value).GetEntity();
	}
	static const wxRibbonToolBarToolBase& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRibbonToolBarToolBase&>(value).GetEntity();
	}
	static wxRibbonToolBarToolBase* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRibbonToolBarToolBase&>(value).GetEntityPtr();
	}
	static const wxRibbonToolBarToolBase* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRibbonToolBarToolBase&>(value).GetEntityPtr();
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
