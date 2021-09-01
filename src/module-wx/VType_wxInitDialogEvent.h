//==============================================================================
// VType_wxInitDialogEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXINITDIALOGEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXINITDIALOGEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxInitDialogEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxInitDialogEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxInitDialogEvent VTYPE_wxInitDialogEvent;

//------------------------------------------------------------------------------
// Value_wxInitDialogEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxInitDialogEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxInitDialogEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxInitDialogEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxInitDialogEvent> eventValueFactory;
public:
	// Constructor
	Value_wxInitDialogEvent() = delete;
	Value_wxInitDialogEvent(const wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxInitDialogEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxInitDialogEvent(const Value_wxInitDialogEvent& src) = delete;
	Value_wxInitDialogEvent& operator=(const Value_wxInitDialogEvent& src) = delete;
	// Move constructor/operator
	Value_wxInitDialogEvent(Value_wxInitDialogEvent&& src) noexcept = delete;
	Value_wxInitDialogEvent& operator=(Value_wxInitDialogEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxInitDialogEvent() = default;
public:
	wxInitDialogEvent& GetEntity() {
		return reinterpret_cast<wxInitDialogEvent&>(Value_wxEvent::GetEntity());
	}
	const wxInitDialogEvent& GetEntity() const {
		return reinterpret_cast<const wxInitDialogEvent&>(Value_wxEvent::GetEntity());
	}
	wxInitDialogEvent* GetEntityPtr() {
		return reinterpret_cast<wxInitDialogEvent*>(Value_wxEvent::GetEntityPtr());
	}
	const wxInitDialogEvent* GetEntityPtr() const {
		return reinterpret_cast<const wxInitDialogEvent*>(Value_wxEvent::GetEntityPtr());
	}
public:
	static wxInitDialogEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxInitDialogEvent&>(value).GetEntity();
	}
	static const wxInitDialogEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxInitDialogEvent&>(value).GetEntity();
	}
	static wxInitDialogEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxInitDialogEvent&>(value).GetEntityPtr();
	}
	static const wxInitDialogEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxInitDialogEvent&>(value).GetEntityPtr();
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