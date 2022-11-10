﻿//==============================================================================
// VType_wxFocusEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFOCUSEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXFOCUSEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFocusEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFocusEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFocusEvent VTYPE_wxFocusEvent;

//------------------------------------------------------------------------------
// Value_wxFocusEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFocusEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFocusEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFocusEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxFocusEvent> eventValueFactory;
public:
	// Constructor
	Value_wxFocusEvent() = delete;
	Value_wxFocusEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxFocusEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxFocusEvent(const Value_wxFocusEvent& src) = delete;
	Value_wxFocusEvent& operator=(const Value_wxFocusEvent& src) = delete;
	// Move constructor/operator
	Value_wxFocusEvent(Value_wxFocusEvent&& src) noexcept = delete;
	Value_wxFocusEvent& operator=(Value_wxFocusEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFocusEvent() = default;
public:
	wxFocusEvent& GetEntity() { return reinterpret_cast<wxFocusEvent&>(Value_wxEvent::GetEntity()); }
	const wxFocusEvent& GetEntity() const { return reinterpret_cast<const wxFocusEvent&>(Value_wxEvent::GetEntity()); }
	wxFocusEvent* GetEntityPtr() { return reinterpret_cast<wxFocusEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxFocusEvent* GetEntityPtr() const { return reinterpret_cast<const wxFocusEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxFocusEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFocusEvent&>(value).GetEntity();
	}
	static const wxFocusEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFocusEvent&>(value).GetEntity();
	}
	static wxFocusEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFocusEvent&>(value).GetEntityPtr();
	}
	static const wxFocusEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFocusEvent&>(value).GetEntityPtr();
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
