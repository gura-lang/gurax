//==============================================================================
// VType_wxDataViewEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXDATAVIEWEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXDATAVIEWEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/dataview.h>
#include "Util.h"
#include "VType_wxNotifyEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxDataViewEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxDataViewEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxDataViewEvent VTYPE_wxDataViewEvent;

//------------------------------------------------------------------------------
// Value_wxDataViewEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxDataViewEvent : public Value_wxNotifyEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxDataViewEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxDataViewEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxDataViewEvent> eventValueFactory;
public:
	// Constructor
	Value_wxDataViewEvent() = delete;
	Value_wxDataViewEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxDataViewEvent) :
		Value_wxNotifyEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxDataViewEvent(const Value_wxDataViewEvent& src) = delete;
	Value_wxDataViewEvent& operator=(const Value_wxDataViewEvent& src) = delete;
	// Move constructor/operator
	Value_wxDataViewEvent(Value_wxDataViewEvent&& src) noexcept = delete;
	Value_wxDataViewEvent& operator=(Value_wxDataViewEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxDataViewEvent() = default;
public:
	wxDataViewEvent& GetEntity() { return reinterpret_cast<wxDataViewEvent&>(Value_wxNotifyEvent::GetEntity()); }
	const wxDataViewEvent& GetEntity() const { return reinterpret_cast<const wxDataViewEvent&>(Value_wxNotifyEvent::GetEntity()); }
	wxDataViewEvent* GetEntityPtr() { return reinterpret_cast<wxDataViewEvent*>(Value_wxNotifyEvent::GetEntityPtr()); }\
	const wxDataViewEvent* GetEntityPtr() const { return reinterpret_cast<const wxDataViewEvent*>(Value_wxNotifyEvent::GetEntityPtr()); }
public:
	static wxDataViewEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxDataViewEvent&>(value).GetEntity();
	}
	static const wxDataViewEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxDataViewEvent&>(value).GetEntity();
	}
	static wxDataViewEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxDataViewEvent&>(value).GetEntityPtr();
	}
	static const wxDataViewEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxDataViewEvent&>(value).GetEntityPtr();
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
