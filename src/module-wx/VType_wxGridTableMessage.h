﻿//==============================================================================
// VType_wxGridTableMessage.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXGRIDTABLEMESSAGE_H
#define GURAX_MODULE_WX_VTYPE_WXGRIDTABLEMESSAGE_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Util.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxGridTableMessage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxGridTableMessage : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxGridTableMessage VTYPE_wxGridTableMessage;

//------------------------------------------------------------------------------
// Value_wxGridTableMessage
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxGridTableMessage : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxGridTableMessage);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxGridTableMessage");
protected:
	wxGridTableMessage _entity;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxGridTableMessage() = delete;
	explicit Value_wxGridTableMessage(VType& vtype = VTYPE_wxGridTableMessage) : Value_Object(vtype) {}
	// Copy constructor/operator
	Value_wxGridTableMessage(const Value_wxGridTableMessage& src) = delete;
	Value_wxGridTableMessage& operator=(const Value_wxGridTableMessage& src) = delete;
	// Move constructor/operator
	Value_wxGridTableMessage(Value_wxGridTableMessage&& src) noexcept = delete;
	Value_wxGridTableMessage& operator=(Value_wxGridTableMessage&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxGridTableMessage() = default;
public:
	wxGridTableMessage& GetEntity() { return _entity; }
	const wxGridTableMessage& GetEntity() const { return _entity; }
	wxGridTableMessage* GetEntityPtr() { return &_entity; }
	const wxGridTableMessage* GetEntityPtr() const { return &_entity; }
public:
	static wxGridTableMessage& GetEntity(Value& value) {
		return dynamic_cast<Value_wxGridTableMessage&>(value).GetEntity();
	}
	static const wxGridTableMessage& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxGridTableMessage&>(value).GetEntity();
	}
	static wxGridTableMessage* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxGridTableMessage&>(value).GetEntityPtr();
	}
	static const wxGridTableMessage* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxGridTableMessage&>(value).GetEntityPtr();
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
