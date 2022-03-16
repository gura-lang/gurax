//==============================================================================
// VType_wxQueryNewPaletteEvent.h
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#ifndef GURAX_MODULE_WX_VTYPE_WXQUERYNEWPALETTEEVENT_H
#define GURAX_MODULE_WX_VTYPE_WXQUERYNEWPALETTEEVENT_H
#include <gurax.h>
#include <wx/wx.h>
#include <wx/event.h>
#include "Util.h"
#include "VType_wxEvent.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// VType_wxQueryNewPaletteEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_wxQueryNewPaletteEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_wxQueryNewPaletteEvent VTYPE_wxQueryNewPaletteEvent;

//------------------------------------------------------------------------------
// Value_wxQueryNewPaletteEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_wxQueryNewPaletteEvent : public Value_wxEvent {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_wxQueryNewPaletteEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_wxQueryNewPaletteEvent");
public:
	static VType& vtype;
	static EventValueFactoryDeriv<Value_wxQueryNewPaletteEvent> eventValueFactory;
public:
	// Constructor
	Value_wxQueryNewPaletteEvent() = delete;
	Value_wxQueryNewPaletteEvent(wxEvent& entity, Value* pValueUserData, VType& vtype = VTYPE_wxQueryNewPaletteEvent) :
		Value_wxEvent(entity, pValueUserData, vtype) {}
	// Copy constructor/operator
	Value_wxQueryNewPaletteEvent(const Value_wxQueryNewPaletteEvent& src) = delete;
	Value_wxQueryNewPaletteEvent& operator=(const Value_wxQueryNewPaletteEvent& src) = delete;
	// Move constructor/operator
	Value_wxQueryNewPaletteEvent(Value_wxQueryNewPaletteEvent&& src) noexcept = delete;
	Value_wxQueryNewPaletteEvent& operator=(Value_wxQueryNewPaletteEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_wxQueryNewPaletteEvent() = default;
public:
	wxQueryNewPaletteEvent& GetEntity() { return reinterpret_cast<wxQueryNewPaletteEvent&>(Value_wxEvent::GetEntity()); }
	const wxQueryNewPaletteEvent& GetEntity() const { return reinterpret_cast<const wxQueryNewPaletteEvent&>(Value_wxEvent::GetEntity()); }
	wxQueryNewPaletteEvent* GetEntityPtr() { return reinterpret_cast<wxQueryNewPaletteEvent*>(Value_wxEvent::GetEntityPtr()); }\
	const wxQueryNewPaletteEvent* GetEntityPtr() const { return reinterpret_cast<const wxQueryNewPaletteEvent*>(Value_wxEvent::GetEntityPtr()); }
public:
	static wxQueryNewPaletteEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_wxQueryNewPaletteEvent&>(value).GetEntity();
	}
	static const wxQueryNewPaletteEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_wxQueryNewPaletteEvent&>(value).GetEntity();
	}
	static wxQueryNewPaletteEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_wxQueryNewPaletteEvent&>(value).GetEntityPtr();
	}
	static const wxQueryNewPaletteEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_wxQueryNewPaletteEvent&>(value).GetEntityPtr();
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