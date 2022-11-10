﻿//==============================================================================
// VType_wxColour.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOUR_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOUR_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/colour.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColour
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColour : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_wxColour VTYPE_wxColour;

//------------------------------------------------------------------------------
// Value_wxColour
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColour : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColour);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColour");
protected:
	wxColour _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxColour() = delete;
	explicit Value_wxColour(const wxColour& entity, VType& vtype = VTYPE_wxColour) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxColour(const Value_wxColour& src) = delete;
	Value_wxColour& operator=(const Value_wxColour& src) = delete;
	// Move constructor/operator
	Value_wxColour(Value_wxColour&& src) noexcept = delete;
	Value_wxColour& operator=(Value_wxColour&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColour() = default;
public:
	wxColour& GetEntity() { return _entity; }
	const wxColour& GetEntity() const { return _entity; }
	wxColour* GetEntityPtr() { return &_entity; }
	const wxColour* GetEntityPtr() const { return &_entity; }
public:
	static wxColour& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColour&>(value).GetEntity();
	}
	static const wxColour& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColour&>(value).GetEntity();
	}
	static wxColour* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColour&>(value).GetEntityPtr();
	}
	static const wxColour* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColour&>(value).GetEntityPtr();
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
