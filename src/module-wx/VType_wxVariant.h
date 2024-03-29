﻿//==============================================================================
// VType_wxVariant.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXVARIANT_H
#define GURAX_MODULE_WX_VTYPE_WXVARIANT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxVariant
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxVariant : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_wxVariant VTYPE_wxVariant;

//------------------------------------------------------------------------------
// Value_wxVariant
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxVariant : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxVariant);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxVariant");
protected:
	wxVariant _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxVariant() = delete;
	explicit Value_wxVariant(const wxVariant& entity, VType& vtype = VTYPE_wxVariant) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_wxVariant(const Value_wxVariant& src) = delete;
	Value_wxVariant& operator=(const Value_wxVariant& src) = delete;
	// Move constructor/operator
	Value_wxVariant(Value_wxVariant&& src) noexcept = delete;
	Value_wxVariant& operator=(Value_wxVariant&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxVariant() = default;
public:
	wxVariant& GetEntity() { return _entity; }
	const wxVariant& GetEntity() const { return _entity; }
	wxVariant* GetEntityPtr() { return &_entity; }
	const wxVariant* GetEntityPtr() const { return &_entity; }
public:
	static wxVariant& GetEntity(Value& value) {
		return dynamic_cast<Value_wxVariant&>(value).GetEntity();
	}
	static const wxVariant& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxVariant&>(value).GetEntity();
	}
	static wxVariant* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxVariant&>(value).GetEntityPtr();
	}
	static const wxVariant* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxVariant&>(value).GetEntityPtr();
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
