//==============================================================================
// VType_CommandEvent.h
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_COMMANDEVENT_H
#define GURAX_MODULE_WX_VTYPE_COMMANDEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include "Util.h"
#include "VType_Event.h"
#include "VType_EventType.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_CommandEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_CommandEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_CommandEvent VTYPE_CommandEvent;

//------------------------------------------------------------------------------
// Value_CommandEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_CommandEvent : public Value_Event {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_CommandEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_CommandEvent");
public:
	using EntityT = wxCommandEvent;
public:
	static VType& vtype;
	//static EventValueFactoryDeriv<Value_CommandEvent> eventValueFactory;
public:
	// Constructor
	Value_CommandEvent() = delete;
	explicit Value_CommandEvent(wxEvent* pEntity, Value* pValueUserData, VType& vtype = VTYPE_CommandEvent) :
		Value_Event(pEntity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_CommandEvent(const Value_CommandEvent& src) = delete;
	Value_CommandEvent& operator=(const Value_CommandEvent& src) = delete;
	// Move constructor/operator
	Value_CommandEvent(Value_CommandEvent&& src) noexcept = delete;
	Value_CommandEvent& operator=(Value_CommandEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_CommandEvent() = default;
public:
	EntityT& GetEntity() { return dynamic_cast<EntityT&>(Value_Event::GetEntity()); }
	const EntityT& GetEntity() const { return dynamic_cast<const EntityT&>(Value_Event::GetEntity()); }
public:
	static EntityT& GetEntity(Value& value) {
		return dynamic_cast<Value_CommandEvent&>(value).GetEntity();
	}
	static const EntityT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_CommandEvent&>(value).GetEntity();
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
