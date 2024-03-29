﻿//==============================================================================
// VType_wxListItemAttr.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXLISTITEMATTR_H
#define GURAX_MODULE_WX_VTYPE_WXLISTITEMATTR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxListItemAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxListItemAttr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxListItemAttr VTYPE_wxListItemAttr;

//------------------------------------------------------------------------------
// Value_wxListItemAttr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxListItemAttr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxListItemAttr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxListItemAttr");
protected:
	wxListItemAttr _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxListItemAttr() = delete;
	explicit Value_wxListItemAttr(const wxListItemAttr& entity, VType& vtype = VTYPE_wxListItemAttr) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxListItemAttr(const Value_wxListItemAttr& src) = delete;
	Value_wxListItemAttr& operator=(const Value_wxListItemAttr& src) = delete;
	// Move constructor/operator
	Value_wxListItemAttr(Value_wxListItemAttr&& src) noexcept = delete;
	Value_wxListItemAttr& operator=(Value_wxListItemAttr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxListItemAttr() = default;
public:
	wxListItemAttr& GetEntity() { return _entity; }
	const wxListItemAttr& GetEntity() const { return _entity; }
	wxListItemAttr* GetEntityPtr() { return &_entity; }
	const wxListItemAttr* GetEntityPtr() const { return &_entity; }
public:
	static wxListItemAttr& GetEntity(Value& value) {
		return dynamic_cast<Value_wxListItemAttr&>(value).GetEntity();
	}
	static const wxListItemAttr& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxListItemAttr&>(value).GetEntity();
	}
	static wxListItemAttr* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxListItemAttr&>(value).GetEntityPtr();
	}
	static const wxListItemAttr* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxListItemAttr&>(value).GetEntityPtr();
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
