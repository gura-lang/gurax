﻿//==============================================================================
// VType_wxScrollEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSCROLLEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXSCROLLEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxCommandEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxScrollEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxScrollEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxScrollEvent VTYPE_wxScrollEvent;

//------------------------------------------------------------------------------
// Value_wxScrollEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxScrollEvent : public Value_wxCommandEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxScrollEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxScrollEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxScrollEvent> eventValueFactory;
public:
	// Constructor
	Value_wxScrollEvent() = delete;
	Value_wxScrollEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxScrollEvent) :
		Value_wxCommandEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxScrollEvent(const Value_wxScrollEvent& src) = delete;
	Value_wxScrollEvent& operator=(const Value_wxScrollEvent& src) = delete;
	// Move constructor/operator
	Value_wxScrollEvent(Value_wxScrollEvent&& src) noexcept = delete;
	Value_wxScrollEvent& operator=(Value_wxScrollEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxScrollEvent() = default;
public:
	wxScrollEvent& GetEntity() { return reinterpret_cast<wxScrollEvent&>(Value_wxCommandEvent::GetEntity()); }
	const wxScrollEvent& GetEntity() const { return reinterpret_cast<const wxScrollEvent&>(Value_wxCommandEvent::GetEntity()); }
	wxScrollEvent* GetEntityPtr() { return reinterpret_cast<wxScrollEvent*>(Value_wxCommandEvent::GetEntityPtr()); }\
	const wxScrollEvent* GetEntityPtr() const { return reinterpret_cast<const wxScrollEvent*>(Value_wxCommandEvent::GetEntityPtr()); }
public:
	static wxScrollEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxScrollEvent&>(value).GetEntity();
	}
	static const wxScrollEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxScrollEvent&>(value).GetEntity();
	}
	static wxScrollEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxScrollEvent&>(value).GetEntityPtr();
	}
	static const wxScrollEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxScrollEvent&>(value).GetEntityPtr();
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
