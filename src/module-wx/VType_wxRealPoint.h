﻿//==============================================================================
// VType_wxRealPoint.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXREALPOINT_H
#define GURAX_MODULE_WX_VTYPE_WXREALPOINT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxRealPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxRealPoint : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_wxRealPoint VTYPE_wxRealPoint;

//------------------------------------------------------------------------------
// Value_wxRealPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxRealPoint : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxRealPoint);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxRealPoint");
protected:
	wxRealPoint _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxRealPoint() = delete;
	explicit Value_wxRealPoint(const wxRealPoint& entity, VType& vtype = VTYPE_wxRealPoint) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxRealPoint(const Value_wxRealPoint& src) = delete;
	Value_wxRealPoint& operator=(const Value_wxRealPoint& src) = delete;
	// Move constructor/operator
	Value_wxRealPoint(Value_wxRealPoint&& src) noexcept = delete;
	Value_wxRealPoint& operator=(Value_wxRealPoint&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxRealPoint() = default;
public:
	wxRealPoint& GetEntity() { return _entity; }
	const wxRealPoint& GetEntity() const { return _entity; }
	wxRealPoint* GetEntityPtr() { return &_entity; }
	const wxRealPoint* GetEntityPtr() const { return &_entity; }
public:
	static wxRealPoint& GetEntity(Value& value) {
		return dynamic_cast<Value_wxRealPoint&>(value).GetEntity();
	}
	static const wxRealPoint& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxRealPoint&>(value).GetEntity();
	}
	static wxRealPoint* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxRealPoint&>(value).GetEntityPtr();
	}
	static const wxRealPoint* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxRealPoint&>(value).GetEntityPtr();
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
