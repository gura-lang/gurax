﻿//==============================================================================
// VType_wxPaletteChangedEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXPALETTECHANGEDEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXPALETTECHANGEDEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxPaletteChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxPaletteChangedEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxPaletteChangedEvent VTYPE_wxPaletteChangedEvent;

//------------------------------------------------------------------------------
// Value_wxPaletteChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxPaletteChangedEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxPaletteChangedEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxPaletteChangedEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxPaletteChangedEvent> eventValueFactory;
public:
	// Constructor
	Value_wxPaletteChangedEvent() = delete;
	Value_wxPaletteChangedEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxPaletteChangedEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxPaletteChangedEvent(const Value_wxPaletteChangedEvent& src) = delete;
	Value_wxPaletteChangedEvent& operator=(const Value_wxPaletteChangedEvent& src) = delete;
	// Move constructor/operator
	Value_wxPaletteChangedEvent(Value_wxPaletteChangedEvent&& src) noexcept = delete;
	Value_wxPaletteChangedEvent& operator=(Value_wxPaletteChangedEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxPaletteChangedEvent() = default;
public:
	wxPaletteChangedEvent& GetEntity() { return reinterpret_cast<wxPaletteChangedEvent&>(Value_wxEvent::GetEntity()); }
	const wxPaletteChangedEvent& GetEntity() const { return reinterpret_cast<const wxPaletteChangedEvent&>(Value_wxEvent::GetEntity()); }
	wxPaletteChangedEvent* GetEntityPtr() { return reinterpret_cast<wxPaletteChangedEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxPaletteChangedEvent* GetEntityPtr() const { return reinterpret_cast<const wxPaletteChangedEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxPaletteChangedEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxPaletteChangedEvent&>(value).GetEntity();
	}
	static const wxPaletteChangedEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxPaletteChangedEvent&>(value).GetEntity();
	}
	static wxPaletteChangedEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxPaletteChangedEvent&>(value).GetEntityPtr();
	}
	static const wxPaletteChangedEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxPaletteChangedEvent&>(value).GetEntityPtr();
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
