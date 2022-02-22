//==============================================================================
// VType_wxSplitterEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXSPLITTEREVENT_H
#define GURAX_MODULE_WX_VTYPE_WXSPLITTEREVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/splitter.h>
#include "Util.h"
#include "VType_wxNotifyEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxSplitterEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxSplitterEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxSplitterEvent VTYPE_wxSplitterEvent;

//------------------------------------------------------------------------------
// Value_wxSplitterEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxSplitterEvent : public Value_wxNotifyEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxSplitterEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxSplitterEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxSplitterEvent> eventValueFactory;
public:
	// Constructor
	Value_wxSplitterEvent() = delete;
	Value_wxSplitterEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxSplitterEvent) :
		Value_wxNotifyEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxSplitterEvent(const Value_wxSplitterEvent& src) = delete;
	Value_wxSplitterEvent& operator=(const Value_wxSplitterEvent& src) = delete;
	// Move constructor/operator
	Value_wxSplitterEvent(Value_wxSplitterEvent&& src) noexcept = delete;
	Value_wxSplitterEvent& operator=(Value_wxSplitterEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxSplitterEvent() = default;
public:
	wxSplitterEvent& GetEntity() { return reinterpret_cast<wxSplitterEvent&>(Value_wxNotifyEvent::GetEntity()); }
	const wxSplitterEvent& GetEntity() const { return reinterpret_cast<const wxSplitterEvent&>(Value_wxNotifyEvent::GetEntity()); }
	wxSplitterEvent* GetEntityPtr() { return reinterpret_cast<wxSplitterEvent*>(Value_wxNotifyEvent::GetEntityPtr()); }\
	const wxSplitterEvent* GetEntityPtr() const { return reinterpret_cast<const wxSplitterEvent*>(Value_wxNotifyEvent::GetEntityPtr()); }
public:
	static wxSplitterEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxSplitterEvent&>(value).GetEntity();
	}
	static const wxSplitterEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxSplitterEvent&>(value).GetEntity();
	}
	static wxSplitterEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxSplitterEvent&>(value).GetEntityPtr();
	}
	static const wxSplitterEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxSplitterEvent&>(value).GetEntityPtr();
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