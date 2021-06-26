//==============================================================================
// VType_wxKeyEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXKEYEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXKEYEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxKeyEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxKeyEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxKeyEvent VTYPE_wxKeyEvent;

//------------------------------------------------------------------------------
// Value_wxKeyEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxKeyEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxKeyEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxKeyEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxKeyEvent> eventValueFactory;
public:
	// Constructor
	Value_wxKeyEvent() = delete;
	Value_wxKeyEvent(const wxObject& entity, Value* pValueUserData, VType& vtype = VTYPE_wxKeyEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxKeyEvent(const Value_wxKeyEvent& src) = delete;
	Value_wxKeyEvent& operator=(const Value_wxKeyEvent& src) = delete;
	// Move constructor/operator
	Value_wxKeyEvent(Value_wxKeyEvent&& src) noexcept = delete;
	Value_wxKeyEvent& operator=(Value_wxKeyEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxKeyEvent() = default;
public:
	wxKeyEvent& GetEntity() {
		return reinterpret_cast<wxKeyEvent&>(Value_wxObject::GetEntity());
	}
	const wxKeyEvent& GetEntity() const {
		return reinterpret_cast<const wxKeyEvent&>(Value_wxObject::GetEntity());
	}
	wxKeyEvent* GetEntityPtr() {
		return reinterpret_cast<wxKeyEvent*>(Value_wxObject::GetEntityPtr());
	}
	const wxKeyEvent* GetEntityPtr() const {
		return reinterpret_cast<const wxKeyEvent*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxKeyEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxKeyEvent&>(value).GetEntity();
	}
	static const wxKeyEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxKeyEvent&>(value).GetEntity();
	}
	static wxKeyEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxKeyEvent&>(value).GetEntityPtr();
	}
	static const wxKeyEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxKeyEvent&>(value).GetEntityPtr();
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