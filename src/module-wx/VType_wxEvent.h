//==============================================================================
// VType_wxEvent.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxObject.h"
#include "VType_wxEventType.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxEvent VTYPE_wxEvent;

//------------------------------------------------------------------------------
// Value_wxEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxEvent : public Value_wxObject {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxEvent");
protected:
	RefPtr<Value> _pValueUserData;
public:
	static VType& vtype;
public:
	// Constructor
	Value_wxEvent() = delete;
	explicit Value_wxEvent(const wxObject& entity, Value* pValueUserData, VType& vtype = VTYPE_wxEvent) :
		Value_wxObject(entity, vtype), _pValueUserData(pValueUserData) {}
	// Copy constructor/operator
	Value_wxEvent(const Value_wxEvent& src) = delete;
	Value_wxEvent& operator=(const Value_wxEvent& src) = delete;
	// Move constructor/operator
	Value_wxEvent(Value_wxEvent&& src) noexcept = delete;
	Value_wxEvent& operator=(Value_wxEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxEvent() = default;
public:
	wxEvent& GetEntity() {
		return reinterpret_cast<wxEvent&>(Value_wxObject::GetEntity());
	}
	const wxEvent& GetEntity() const {
		return reinterpret_cast<const wxEvent&>(Value_wxObject::GetEntity());
	}
	wxEvent* GetEntityPtr() {
		return reinterpret_cast<wxEvent*>(Value_wxObject::GetEntityPtr());
	}
	const wxEvent* GetEntityPtr() const {
		return reinterpret_cast<const wxEvent*>(Value_wxObject::GetEntityPtr());
	}
public:
	static wxEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxEvent&>(value).GetEntity();
	}
	static const wxEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxEvent&>(value).GetEntity();
	}
	static wxEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxEvent&>(value).GetEntityPtr();
	}
	static const wxEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxEvent&>(value).GetEntityPtr();
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
