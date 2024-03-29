﻿//==============================================================================
// VType_wxActivateEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXACTIVATEEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXACTIVATEEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/event.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxActivateEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxActivateEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxActivateEvent VTYPE_wxActivateEvent;

//------------------------------------------------------------------------------
// Value_wxActivateEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxActivateEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxActivateEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxActivateEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxActivateEvent> eventValueFactory;
public:
	// Constructor
	Value_wxActivateEvent() = delete;
	Value_wxActivateEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxActivateEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxActivateEvent(const Value_wxActivateEvent& src) = delete;
	Value_wxActivateEvent& operator=(const Value_wxActivateEvent& src) = delete;
	// Move constructor/operator
	Value_wxActivateEvent(Value_wxActivateEvent&& src) noexcept = delete;
	Value_wxActivateEvent& operator=(Value_wxActivateEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxActivateEvent() = default;
public:
	wxActivateEvent& GetEntity() { return reinterpret_cast<wxActivateEvent&>(Value_wxEvent::GetEntity()); }
	const wxActivateEvent& GetEntity() const { return reinterpret_cast<const wxActivateEvent&>(Value_wxEvent::GetEntity()); }
	wxActivateEvent* GetEntityPtr() { return reinterpret_cast<wxActivateEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxActivateEvent* GetEntityPtr() const { return reinterpret_cast<const wxActivateEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxActivateEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxActivateEvent&>(value).GetEntity();
	}
	static const wxActivateEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxActivateEvent&>(value).GetEntity();
	}
	static wxActivateEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxActivateEvent&>(value).GetEntityPtr();
	}
	static const wxActivateEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxActivateEvent&>(value).GetEntityPtr();
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
