//==============================================================================
// VType_wxDialUpEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDIALUPEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXDIALUPEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dialup.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDialUpEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDialUpEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDialUpEvent VTYPE_wxDialUpEvent;

//------------------------------------------------------------------------------
// Value_wxDialUpEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDialUpEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDialUpEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDialUpEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxDialUpEvent> eventValueFactory;
public:
	// Constructor
	Value_wxDialUpEvent() = delete;
	Value_wxDialUpEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxDialUpEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxDialUpEvent(const Value_wxDialUpEvent& src) = delete;
	Value_wxDialUpEvent& operator=(const Value_wxDialUpEvent& src) = delete;
	// Move constructor/operator
	Value_wxDialUpEvent(Value_wxDialUpEvent&& src) noexcept = delete;
	Value_wxDialUpEvent& operator=(Value_wxDialUpEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDialUpEvent() = default;
public:
	wxDialUpEvent& GetEntity() { return reinterpret_cast<wxDialUpEvent&>(Value_wxEvent::GetEntity()); }
	const wxDialUpEvent& GetEntity() const { return reinterpret_cast<const wxDialUpEvent&>(Value_wxEvent::GetEntity()); }
	wxDialUpEvent* GetEntityPtr() { return reinterpret_cast<wxDialUpEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxDialUpEvent* GetEntityPtr() const { return reinterpret_cast<const wxDialUpEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxDialUpEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDialUpEvent&>(value).GetEntity();
	}
	static const wxDialUpEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDialUpEvent&>(value).GetEntity();
	}
	static wxDialUpEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDialUpEvent&>(value).GetEntityPtr();
	}
	static const wxDialUpEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDialUpEvent&>(value).GetEntityPtr();
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
