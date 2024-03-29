﻿//==============================================================================
// VType_wxCloseEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCLOSEEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXCLOSEEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/event.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCloseEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCloseEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCloseEvent VTYPE_wxCloseEvent;

//------------------------------------------------------------------------------
// Value_wxCloseEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCloseEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCloseEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCloseEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxCloseEvent> eventValueFactory;
public:
	// Constructor
	Value_wxCloseEvent() = delete;
	Value_wxCloseEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxCloseEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxCloseEvent(const Value_wxCloseEvent& src) = delete;
	Value_wxCloseEvent& operator=(const Value_wxCloseEvent& src) = delete;
	// Move constructor/operator
	Value_wxCloseEvent(Value_wxCloseEvent&& src) noexcept = delete;
	Value_wxCloseEvent& operator=(Value_wxCloseEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCloseEvent() = default;
public:
	wxCloseEvent& GetEntity() { return reinterpret_cast<wxCloseEvent&>(Value_wxEvent::GetEntity()); }
	const wxCloseEvent& GetEntity() const { return reinterpret_cast<const wxCloseEvent&>(Value_wxEvent::GetEntity()); }
	wxCloseEvent* GetEntityPtr() { return reinterpret_cast<wxCloseEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxCloseEvent* GetEntityPtr() const { return reinterpret_cast<const wxCloseEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxCloseEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCloseEvent&>(value).GetEntity();
	}
	static const wxCloseEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCloseEvent&>(value).GetEntity();
	}
	static wxCloseEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCloseEvent&>(value).GetEntityPtr();
	}
	static const wxCloseEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCloseEvent&>(value).GetEntityPtr();
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
