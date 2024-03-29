﻿//==============================================================================
// VType_wxImageHandler.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXIMAGEHANDLER_H
#define GURAX_MODULE_WX_VTYPE_WXIMAGEHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxImageHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxImageHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxImageHandler VTYPE_wxImageHandler;

//------------------------------------------------------------------------------
// Value_wxImageHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxImageHandler : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxImageHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxImageHandler");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxImageHandler() = delete;
	explicit Value_wxImageHandler(const wxImageHandler& entity, VType& vtype = VTYPE_wxImageHandler) :
		Value_wxObject(entity, vtype) {}
	// Copy constructor/operator
	Value_wxImageHandler(const Value_wxImageHandler& src) = delete;
	Value_wxImageHandler& operator=(const Value_wxImageHandler& src) = delete;
	// Move constructor/operator
	Value_wxImageHandler(Value_wxImageHandler&& src) noexcept = delete;
	Value_wxImageHandler& operator=(Value_wxImageHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxImageHandler() = default;
public:
	wxImageHandler& GetEntity() { return reinterpret_cast<wxImageHandler&>(Value_wxObject::GetEntity()); }
	const wxImageHandler& GetEntity() const { return reinterpret_cast<const wxImageHandler&>(Value_wxObject::GetEntity()); }
	wxImageHandler* GetEntityPtr() { return reinterpret_cast<wxImageHandler*>(Value_wxObject::GetEntityPtr()); }\
	const wxImageHandler* GetEntityPtr() const { return reinterpret_cast<const wxImageHandler*>(Value_wxObject::GetEntityPtr()); }
public:
	static wxImageHandler& GetEntity(Value& value) {
		return dynamic_cast<Value_wxImageHandler&>(value).GetEntity();
	}
	static const wxImageHandler& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxImageHandler&>(value).GetEntity();
	}
	static wxImageHandler* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxImageHandler&>(value).GetEntityPtr();
	}
	static const wxImageHandler* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxImageHandler&>(value).GetEntityPtr();
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
