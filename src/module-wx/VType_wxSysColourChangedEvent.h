﻿//==============================================================================
// VType_wxSysColourChangedEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSYSCOLOURCHANGEDEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXSYSCOLOURCHANGEDEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/event.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSysColourChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSysColourChangedEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSysColourChangedEvent VTYPE_wxSysColourChangedEvent;

//------------------------------------------------------------------------------
// Value_wxSysColourChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSysColourChangedEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSysColourChangedEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSysColourChangedEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxSysColourChangedEvent> eventValueFactory;
public:
	// Constructor
	Value_wxSysColourChangedEvent() = delete;
	Value_wxSysColourChangedEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxSysColourChangedEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxSysColourChangedEvent(const Value_wxSysColourChangedEvent& src) = delete;
	Value_wxSysColourChangedEvent& operator=(const Value_wxSysColourChangedEvent& src) = delete;
	// Move constructor/operator
	Value_wxSysColourChangedEvent(Value_wxSysColourChangedEvent&& src) noexcept = delete;
	Value_wxSysColourChangedEvent& operator=(Value_wxSysColourChangedEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSysColourChangedEvent() = default;
public:
	wxSysColourChangedEvent& GetEntity() { return reinterpret_cast<wxSysColourChangedEvent&>(Value_wxEvent::GetEntity()); }
	const wxSysColourChangedEvent& GetEntity() const { return reinterpret_cast<const wxSysColourChangedEvent&>(Value_wxEvent::GetEntity()); }
	wxSysColourChangedEvent* GetEntityPtr() { return reinterpret_cast<wxSysColourChangedEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxSysColourChangedEvent* GetEntityPtr() const { return reinterpret_cast<const wxSysColourChangedEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxSysColourChangedEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSysColourChangedEvent&>(value).GetEntity();
	}
	static const wxSysColourChangedEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSysColourChangedEvent&>(value).GetEntity();
	}
	static wxSysColourChangedEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSysColourChangedEvent&>(value).GetEntityPtr();
	}
	static const wxSysColourChangedEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSysColourChangedEvent&>(value).GetEntityPtr();
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
