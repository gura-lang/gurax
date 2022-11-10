﻿//==============================================================================
// VType_wxColourPickerEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLOURPICKEREVENT_H
#define GURAX_MODULE_WX_VTYPE_WXCOLOURPICKEREVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/clrpicker.h>
#include "Util.h"
#include "VType_wxCommandEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxColourPickerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxColourPickerEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxColourPickerEvent VTYPE_wxColourPickerEvent;

//------------------------------------------------------------------------------
// Value_wxColourPickerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxColourPickerEvent : public Value_wxCommandEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxColourPickerEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxColourPickerEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxColourPickerEvent> eventValueFactory;
public:
	// Constructor
	Value_wxColourPickerEvent() = delete;
	Value_wxColourPickerEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxColourPickerEvent) :
		Value_wxCommandEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxColourPickerEvent(const Value_wxColourPickerEvent& src) = delete;
	Value_wxColourPickerEvent& operator=(const Value_wxColourPickerEvent& src) = delete;
	// Move constructor/operator
	Value_wxColourPickerEvent(Value_wxColourPickerEvent&& src) noexcept = delete;
	Value_wxColourPickerEvent& operator=(Value_wxColourPickerEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxColourPickerEvent() = default;
public:
	wxColourPickerEvent& GetEntity() { return reinterpret_cast<wxColourPickerEvent&>(Value_wxCommandEvent::GetEntity()); }
	const wxColourPickerEvent& GetEntity() const { return reinterpret_cast<const wxColourPickerEvent&>(Value_wxCommandEvent::GetEntity()); }
	wxColourPickerEvent* GetEntityPtr() { return reinterpret_cast<wxColourPickerEvent*>(Value_wxCommandEvent::GetEntityPtr()); }\
	const wxColourPickerEvent* GetEntityPtr() const { return reinterpret_cast<const wxColourPickerEvent*>(Value_wxCommandEvent::GetEntityPtr()); }
public:
	static wxColourPickerEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxColourPickerEvent&>(value).GetEntity();
	}
	static const wxColourPickerEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxColourPickerEvent&>(value).GetEntity();
	}
	static wxColourPickerEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxColourPickerEvent&>(value).GetEntityPtr();
	}
	static const wxColourPickerEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxColourPickerEvent&>(value).GetEntityPtr();
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
