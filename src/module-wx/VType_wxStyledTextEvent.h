﻿//==============================================================================
// VType_wxStyledTextEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSTYLEDTEXTEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXSTYLEDTEXTEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/stc/stc.h>
#include "Util.h"
#include "VType_wxCommandEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxStyledTextEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxStyledTextEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxStyledTextEvent VTYPE_wxStyledTextEvent;

//------------------------------------------------------------------------------
// Value_wxStyledTextEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxStyledTextEvent : public Value_wxCommandEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxStyledTextEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxStyledTextEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxStyledTextEvent> eventValueFactory;
public:
	// Constructor
	Value_wxStyledTextEvent() = delete;
	Value_wxStyledTextEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxStyledTextEvent) :
		Value_wxCommandEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxStyledTextEvent(const Value_wxStyledTextEvent& src) = delete;
	Value_wxStyledTextEvent& operator=(const Value_wxStyledTextEvent& src) = delete;
	// Move constructor/operator
	Value_wxStyledTextEvent(Value_wxStyledTextEvent&& src) noexcept = delete;
	Value_wxStyledTextEvent& operator=(Value_wxStyledTextEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxStyledTextEvent() = default;
public:
	wxStyledTextEvent& GetEntity() { return reinterpret_cast<wxStyledTextEvent&>(Value_wxCommandEvent::GetEntity()); }
	const wxStyledTextEvent& GetEntity() const { return reinterpret_cast<const wxStyledTextEvent&>(Value_wxCommandEvent::GetEntity()); }
	wxStyledTextEvent* GetEntityPtr() { return reinterpret_cast<wxStyledTextEvent*>(Value_wxCommandEvent::GetEntityPtr()); }\
	const wxStyledTextEvent* GetEntityPtr() const { return reinterpret_cast<const wxStyledTextEvent*>(Value_wxCommandEvent::GetEntityPtr()); }
public:
	static wxStyledTextEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxStyledTextEvent&>(value).GetEntity();
	}
	static const wxStyledTextEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxStyledTextEvent&>(value).GetEntity();
	}
	static wxStyledTextEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxStyledTextEvent&>(value).GetEntityPtr();
	}
	static const wxStyledTextEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxStyledTextEvent&>(value).GetEntityPtr();
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
