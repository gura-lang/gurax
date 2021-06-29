//==============================================================================
// VType_wxScrollWinEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSCROLLWINEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXSCROLLWINEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxScrollWinEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxScrollWinEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxScrollWinEvent VTYPE_wxScrollWinEvent;

//------------------------------------------------------------------------------
// Value_wxScrollWinEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxScrollWinEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxScrollWinEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxScrollWinEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxScrollWinEvent> eventValueFactory;
public:
	// Constructor
	Value_wxScrollWinEvent() = delete;
	Value_wxScrollWinEvent(const wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxScrollWinEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxScrollWinEvent(const Value_wxScrollWinEvent& src) = delete;
	Value_wxScrollWinEvent& operator=(const Value_wxScrollWinEvent& src) = delete;
	// Move constructor/operator
	Value_wxScrollWinEvent(Value_wxScrollWinEvent&& src) noexcept = delete;
	Value_wxScrollWinEvent& operator=(Value_wxScrollWinEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxScrollWinEvent() = default;
public:
	wxScrollWinEvent& GetEntity() {
		return reinterpret_cast<wxScrollWinEvent&>(Value_wxEvent::GetEntity());
	}
	const wxScrollWinEvent& GetEntity() const {
		return reinterpret_cast<const wxScrollWinEvent&>(Value_wxEvent::GetEntity());
	}
	wxScrollWinEvent* GetEntityPtr() {
		return reinterpret_cast<wxScrollWinEvent*>(Value_wxEvent::GetEntityPtr());
	}
	const wxScrollWinEvent* GetEntityPtr() const {
		return reinterpret_cast<const wxScrollWinEvent*>(Value_wxEvent::GetEntityPtr());
	}
public:
	static wxScrollWinEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxScrollWinEvent&>(value).GetEntity();
	}
	static const wxScrollWinEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxScrollWinEvent&>(value).GetEntity();
	}
	static wxScrollWinEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxScrollWinEvent&>(value).GetEntityPtr();
	}
	static const wxScrollWinEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxScrollWinEvent&>(value).GetEntityPtr();
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
