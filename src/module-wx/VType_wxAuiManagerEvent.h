﻿//==============================================================================
// VType_wxAuiManagerEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXAUIMANAGEREVENT_H
#define GURAX_MODULE_WX_VTYPE_WXAUIMANAGEREVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxAuiManagerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxAuiManagerEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxAuiManagerEvent VTYPE_wxAuiManagerEvent;

//------------------------------------------------------------------------------
// Value_wxAuiManagerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxAuiManagerEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxAuiManagerEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxAuiManagerEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxAuiManagerEvent> eventValueFactory;
public:
	// Constructor
	Value_wxAuiManagerEvent() = delete;
	Value_wxAuiManagerEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxAuiManagerEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxAuiManagerEvent(const Value_wxAuiManagerEvent& src) = delete;
	Value_wxAuiManagerEvent& operator=(const Value_wxAuiManagerEvent& src) = delete;
	// Move constructor/operator
	Value_wxAuiManagerEvent(Value_wxAuiManagerEvent&& src) noexcept = delete;
	Value_wxAuiManagerEvent& operator=(Value_wxAuiManagerEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxAuiManagerEvent() = default;
public:
	wxAuiManagerEvent& GetEntity() { return reinterpret_cast<wxAuiManagerEvent&>(Value_wxEvent::GetEntity()); }
	const wxAuiManagerEvent& GetEntity() const { return reinterpret_cast<const wxAuiManagerEvent&>(Value_wxEvent::GetEntity()); }
	wxAuiManagerEvent* GetEntityPtr() { return reinterpret_cast<wxAuiManagerEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxAuiManagerEvent* GetEntityPtr() const { return reinterpret_cast<const wxAuiManagerEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxAuiManagerEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxAuiManagerEvent&>(value).GetEntity();
	}
	static const wxAuiManagerEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxAuiManagerEvent&>(value).GetEntity();
	}
	static wxAuiManagerEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxAuiManagerEvent&>(value).GetEntityPtr();
	}
	static const wxAuiManagerEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxAuiManagerEvent&>(value).GetEntityPtr();
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
