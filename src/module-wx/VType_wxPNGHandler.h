﻿//==============================================================================
// VType_wxPNGHandler.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPNGHANDLER_H
#define GURAX_MODULE_WX_VTYPE_WXPNGHANDLER_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxImageHandler.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPNGHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPNGHandler : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPNGHandler VTYPE_wxPNGHandler;

//------------------------------------------------------------------------------
// Value_wxPNGHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPNGHandler : public Value_wxImageHandler {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPNGHandler);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPNGHandler");
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxPNGHandler() = delete;
	explicit Value_wxPNGHandler(const wxPNGHandler& entity, VType& vtype = VTYPE_wxPNGHandler) :
		Value_wxImageHandler(entity, vtype) {}
	// Copy constructor/operator
	Value_wxPNGHandler(const Value_wxPNGHandler& src) = delete;
	Value_wxPNGHandler& operator=(const Value_wxPNGHandler& src) = delete;
	// Move constructor/operator
	Value_wxPNGHandler(Value_wxPNGHandler&& src) noexcept = delete;
	Value_wxPNGHandler& operator=(Value_wxPNGHandler&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPNGHandler() = default;
public:
	wxPNGHandler& GetEntity() { return reinterpret_cast<wxPNGHandler&>(Value_wxImageHandler::GetEntity()); }
	const wxPNGHandler& GetEntity() const { return reinterpret_cast<const wxPNGHandler&>(Value_wxImageHandler::GetEntity()); }
	wxPNGHandler* GetEntityPtr() { return reinterpret_cast<wxPNGHandler*>(Value_wxImageHandler::GetEntityPtr()); }\
	const wxPNGHandler* GetEntityPtr() const { return reinterpret_cast<const wxPNGHandler*>(Value_wxImageHandler::GetEntityPtr()); }
public:
	static wxPNGHandler& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPNGHandler&>(value).GetEntity();
	}
	static const wxPNGHandler& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPNGHandler&>(value).GetEntity();
	}
	static wxPNGHandler* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPNGHandler&>(value).GetEntityPtr();
	}
	static const wxPNGHandler* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPNGHandler&>(value).GetEntityPtr();
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
