//==============================================================================
// VType_wxMouseCaptureChangedEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMOUSECAPTURECHANGEDEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXMOUSECAPTURECHANGEDEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMouseCaptureChangedEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMouseCaptureChangedEvent VTYPE_wxMouseCaptureChangedEvent;

//------------------------------------------------------------------------------
// Value_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMouseCaptureChangedEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMouseCaptureChangedEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMouseCaptureChangedEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxMouseCaptureChangedEvent> eventValueFactory;
public:
	// Constructor
	Value_wxMouseCaptureChangedEvent() = delete;
	Value_wxMouseCaptureChangedEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxMouseCaptureChangedEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxMouseCaptureChangedEvent(const Value_wxMouseCaptureChangedEvent& src) = delete;
	Value_wxMouseCaptureChangedEvent& operator=(const Value_wxMouseCaptureChangedEvent& src) = delete;
	// Move constructor/operator
	Value_wxMouseCaptureChangedEvent(Value_wxMouseCaptureChangedEvent&& src) noexcept = delete;
	Value_wxMouseCaptureChangedEvent& operator=(Value_wxMouseCaptureChangedEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMouseCaptureChangedEvent() = default;
public:
	wxMouseCaptureChangedEvent& GetEntity() { return reinterpret_cast<wxMouseCaptureChangedEvent&>(Value_wxEvent::GetEntity()); }
	const wxMouseCaptureChangedEvent& GetEntity() const { return reinterpret_cast<const wxMouseCaptureChangedEvent&>(Value_wxEvent::GetEntity()); }
	wxMouseCaptureChangedEvent* GetEntityPtr() { return reinterpret_cast<wxMouseCaptureChangedEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxMouseCaptureChangedEvent* GetEntityPtr() const { return reinterpret_cast<const wxMouseCaptureChangedEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxMouseCaptureChangedEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMouseCaptureChangedEvent&>(value).GetEntity();
	}
	static const wxMouseCaptureChangedEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMouseCaptureChangedEvent&>(value).GetEntity();
	}
	static wxMouseCaptureChangedEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMouseCaptureChangedEvent&>(value).GetEntityPtr();
	}
	static const wxMouseCaptureChangedEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMouseCaptureChangedEvent&>(value).GetEntityPtr();
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
