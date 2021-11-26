//==============================================================================
// VType_wxCollapsiblePaneEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOLLAPSIBLEPANEEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXCOLLAPSIBLEPANEEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxCommandEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCollapsiblePaneEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCollapsiblePaneEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCollapsiblePaneEvent VTYPE_wxCollapsiblePaneEvent;

//------------------------------------------------------------------------------
// Value_wxCollapsiblePaneEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCollapsiblePaneEvent : public Value_wxCommandEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCollapsiblePaneEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCollapsiblePaneEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxCollapsiblePaneEvent> eventValueFactory;
public:
	// Constructor
	Value_wxCollapsiblePaneEvent() = delete;
	Value_wxCollapsiblePaneEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxCollapsiblePaneEvent) :
		Value_wxCommandEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxCollapsiblePaneEvent(const Value_wxCollapsiblePaneEvent& src) = delete;
	Value_wxCollapsiblePaneEvent& operator=(const Value_wxCollapsiblePaneEvent& src) = delete;
	// Move constructor/operator
	Value_wxCollapsiblePaneEvent(Value_wxCollapsiblePaneEvent&& src) noexcept = delete;
	Value_wxCollapsiblePaneEvent& operator=(Value_wxCollapsiblePaneEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCollapsiblePaneEvent() = default;
public:
	wxCollapsiblePaneEvent& GetEntity() { return reinterpret_cast<wxCollapsiblePaneEvent&>(Value_wxCommandEvent::GetEntity()); }
	const wxCollapsiblePaneEvent& GetEntity() const { return reinterpret_cast<const wxCollapsiblePaneEvent&>(Value_wxCommandEvent::GetEntity()); }
	wxCollapsiblePaneEvent* GetEntityPtr() { return reinterpret_cast<wxCollapsiblePaneEvent*>(Value_wxCommandEvent::GetEntityPtr()); }\
	const wxCollapsiblePaneEvent* GetEntityPtr() const { return reinterpret_cast<const wxCollapsiblePaneEvent*>(Value_wxCommandEvent::GetEntityPtr()); }
public:
	static wxCollapsiblePaneEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCollapsiblePaneEvent&>(value).GetEntity();
	}
	static const wxCollapsiblePaneEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCollapsiblePaneEvent&>(value).GetEntity();
	}
	static wxCollapsiblePaneEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxCollapsiblePaneEvent&>(value).GetEntityPtr();
	}
	static const wxCollapsiblePaneEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxCollapsiblePaneEvent&>(value).GetEntityPtr();
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