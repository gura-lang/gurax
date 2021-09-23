//==============================================================================
// VType_wxMouseCaptureLostEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXMOUSECAPTURELOSTEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXMOUSECAPTURELOSTEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxMouseCaptureLostEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxMouseCaptureLostEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxMouseCaptureLostEvent VTYPE_wxMouseCaptureLostEvent;

//------------------------------------------------------------------------------
// Value_wxMouseCaptureLostEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxMouseCaptureLostEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxMouseCaptureLostEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxMouseCaptureLostEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxMouseCaptureLostEvent> eventValueFactory;
public:
	// Constructor
	Value_wxMouseCaptureLostEvent() = delete;
	Value_wxMouseCaptureLostEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxMouseCaptureLostEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxMouseCaptureLostEvent(const Value_wxMouseCaptureLostEvent& src) = delete;
	Value_wxMouseCaptureLostEvent& operator=(const Value_wxMouseCaptureLostEvent& src) = delete;
	// Move constructor/operator
	Value_wxMouseCaptureLostEvent(Value_wxMouseCaptureLostEvent&& src) noexcept = delete;
	Value_wxMouseCaptureLostEvent& operator=(Value_wxMouseCaptureLostEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxMouseCaptureLostEvent() = default;
public:
	wxMouseCaptureLostEvent& GetEntity() { return reinterpret_cast<wxMouseCaptureLostEvent&>(Value_wxEvent::GetEntity()); }
	const wxMouseCaptureLostEvent& GetEntity() const { return reinterpret_cast<const wxMouseCaptureLostEvent&>(Value_wxEvent::GetEntity()); }
	wxMouseCaptureLostEvent* GetEntityPtr() { return reinterpret_cast<wxMouseCaptureLostEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxMouseCaptureLostEvent* GetEntityPtr() const { return reinterpret_cast<const wxMouseCaptureLostEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxMouseCaptureLostEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxMouseCaptureLostEvent&>(value).GetEntity();
	}
	static const wxMouseCaptureLostEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxMouseCaptureLostEvent&>(value).GetEntity();
	}
	static wxMouseCaptureLostEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxMouseCaptureLostEvent&>(value).GetEntityPtr();
	}
	static const wxMouseCaptureLostEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxMouseCaptureLostEvent&>(value).GetEntityPtr();
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
