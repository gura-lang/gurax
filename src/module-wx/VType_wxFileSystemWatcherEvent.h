﻿//==============================================================================
// VType_wxFileSystemWatcherEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXFILESYSTEMWATCHEREVENT_H
#define GURAX_MODULE_WX_VTYPE_WXFILESYSTEMWATCHEREVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/fswatcher.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxFileSystemWatcherEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxFileSystemWatcherEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxFileSystemWatcherEvent VTYPE_wxFileSystemWatcherEvent;

//------------------------------------------------------------------------------
// Value_wxFileSystemWatcherEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxFileSystemWatcherEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxFileSystemWatcherEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxFileSystemWatcherEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxFileSystemWatcherEvent> eventValueFactory;
public:
	// Constructor
	Value_wxFileSystemWatcherEvent() = delete;
	Value_wxFileSystemWatcherEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxFileSystemWatcherEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxFileSystemWatcherEvent(const Value_wxFileSystemWatcherEvent& src) = delete;
	Value_wxFileSystemWatcherEvent& operator=(const Value_wxFileSystemWatcherEvent& src) = delete;
	// Move constructor/operator
	Value_wxFileSystemWatcherEvent(Value_wxFileSystemWatcherEvent&& src) noexcept = delete;
	Value_wxFileSystemWatcherEvent& operator=(Value_wxFileSystemWatcherEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxFileSystemWatcherEvent() = default;
public:
	wxFileSystemWatcherEvent& GetEntity() { return reinterpret_cast<wxFileSystemWatcherEvent&>(Value_wxEvent::GetEntity()); }
	const wxFileSystemWatcherEvent& GetEntity() const { return reinterpret_cast<const wxFileSystemWatcherEvent&>(Value_wxEvent::GetEntity()); }
	wxFileSystemWatcherEvent* GetEntityPtr() { return reinterpret_cast<wxFileSystemWatcherEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxFileSystemWatcherEvent* GetEntityPtr() const { return reinterpret_cast<const wxFileSystemWatcherEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxFileSystemWatcherEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxFileSystemWatcherEvent&>(value).GetEntity();
	}
	static const wxFileSystemWatcherEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxFileSystemWatcherEvent&>(value).GetEntity();
	}
	static wxFileSystemWatcherEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxFileSystemWatcherEvent&>(value).GetEntityPtr();
	}
	static const wxFileSystemWatcherEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxFileSystemWatcherEvent&>(value).GetEntityPtr();
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
