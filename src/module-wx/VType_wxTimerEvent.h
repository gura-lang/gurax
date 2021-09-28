//==============================================================================
// VType_wxTimerEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXTIMEREVENT_H
#define GURAX_MODULE_WX_VTYPE_WXTIMEREVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxTimerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxTimerEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxTimerEvent VTYPE_wxTimerEvent;

//------------------------------------------------------------------------------
// Value_wxTimerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxTimerEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxTimerEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxTimerEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxTimerEvent> eventValueFactory;
public:
	// Constructor
	Value_wxTimerEvent() = delete;
	Value_wxTimerEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxTimerEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxTimerEvent(const Value_wxTimerEvent& src) = delete;
	Value_wxTimerEvent& operator=(const Value_wxTimerEvent& src) = delete;
	// Move constructor/operator
	Value_wxTimerEvent(Value_wxTimerEvent&& src) noexcept = delete;
	Value_wxTimerEvent& operator=(Value_wxTimerEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxTimerEvent() = default;
public:
	wxTimerEvent& GetEntity() { return reinterpret_cast<wxTimerEvent&>(Value_wxEvent::GetEntity()); }
	const wxTimerEvent& GetEntity() const { return reinterpret_cast<const wxTimerEvent&>(Value_wxEvent::GetEntity()); }
	wxTimerEvent* GetEntityPtr() { return reinterpret_cast<wxTimerEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxTimerEvent* GetEntityPtr() const { return reinterpret_cast<const wxTimerEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxTimerEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxTimerEvent&>(value).GetEntity();
	}
	static const wxTimerEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxTimerEvent&>(value).GetEntity();
	}
	static wxTimerEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxTimerEvent&>(value).GetEntityPtr();
	}
	static const wxTimerEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxTimerEvent&>(value).GetEntityPtr();
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