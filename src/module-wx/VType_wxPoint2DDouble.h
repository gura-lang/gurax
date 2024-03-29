﻿//==============================================================================
// VType_wxPoint2DDouble.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPOINT2DDOUBLE_H
#define GURAX_MODULE_WX_VTYPE_WXPOINT2DDOUBLE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPoint2DDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPoint2DDouble : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPoint2DDouble VTYPE_wxPoint2DDouble;

//------------------------------------------------------------------------------
// Value_wxPoint2DDouble
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPoint2DDouble : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPoint2DDouble);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPoint2DDouble");
protected:
	wxPoint2DDouble _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPoint2DDouble() = delete;
	explicit Value_wxPoint2DDouble(const wxPoint2DDouble& entity, VType& vtype = VTYPE_wxPoint2DDouble) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxPoint2DDouble(const Value_wxPoint2DDouble& src) = delete;
	Value_wxPoint2DDouble& operator=(const Value_wxPoint2DDouble& src) = delete;
	// Move constructor/operator
	Value_wxPoint2DDouble(Value_wxPoint2DDouble&& src) noexcept = delete;
	Value_wxPoint2DDouble& operator=(Value_wxPoint2DDouble&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPoint2DDouble() = default;
public:
	wxPoint2DDouble& GetEntity() { return _entity; }
	const wxPoint2DDouble& GetEntity() const { return _entity; }
	wxPoint2DDouble* GetEntityPtr() { return &_entity; }
	const wxPoint2DDouble* GetEntityPtr() const { return &_entity; }
public:
	static wxPoint2DDouble& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPoint2DDouble&>(value).GetEntity();
	}
	static const wxPoint2DDouble& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPoint2DDouble&>(value).GetEntity();
	}
	static wxPoint2DDouble* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPoint2DDouble&>(value).GetEntityPtr();
	}
	static const wxPoint2DDouble* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPoint2DDouble&>(value).GetEntityPtr();
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
