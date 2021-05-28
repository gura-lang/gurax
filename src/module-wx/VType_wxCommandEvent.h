//==============================================================================
// VType_wxCommandEvent.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXCOMMANDEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXCOMMANDEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_wxEvent.h"
#include "VType_wxEventType.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxCommandEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxCommandEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxCommandEvent VTYPE_wxCommandEvent;

//------------------------------------------------------------------------------
// Value_wxCommandEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxCommandEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxCommandEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxCommandEvent");
public:
	using EntityT = wxCommandEvent;
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxCommandEvent> eventValueFactory;
public:
	// Constructor
	Value_wxCommandEvent() = delete;
	Value_wxCommandEvent(const wxObject& entity, Value* pValueUserData, VType& vtype = VTYPE_wxCommandEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxCommandEvent(const Value_wxCommandEvent& src) = delete;
	Value_wxCommandEvent& operator=(const Value_wxCommandEvent& src) = delete;
	// Move constructor/operator
	Value_wxCommandEvent(Value_wxCommandEvent&& src) noexcept = delete;
	Value_wxCommandEvent& operator=(Value_wxCommandEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxCommandEvent() = default;
public:
	EntityT& GetEntity() { return dynamic_cast<EntityT&>(Value_wxEvent::GetEntity()); }
	const EntityT& GetEntity() const { return dynamic_cast<const EntityT&>(Value_wxEvent::GetEntity()); }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_wxCommandEvent&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxCommandEvent&>(value).GetEntity();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(&GetEntity(*this));
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) && &GetEntity(*this) == &GetEntity(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			(&GetEntity(*this) < &GetEntity(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(wx)

#endif
