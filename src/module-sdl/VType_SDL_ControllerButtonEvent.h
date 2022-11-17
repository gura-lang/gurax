//==============================================================================
// VType_SDL_ControllerButtonEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_ControllerButtonEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_ControllerButtonEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_ControllerButtonEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_ControllerButtonEvent VTYPE_SDL_ControllerButtonEvent;

//------------------------------------------------------------------------------
// Value_SDL_ControllerButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_ControllerButtonEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_ControllerButtonEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_ControllerButtonEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_ControllerButtonEvent(VType& vtype = VTYPE_SDL_ControllerButtonEvent) : Value_Object(vtype) {}
	explicit Value_SDL_ControllerButtonEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_ControllerButtonEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_ControllerButtonEvent(const Value_SDL_ControllerButtonEvent& src) = delete;
	Value_SDL_ControllerButtonEvent& operator=(const Value_SDL_ControllerButtonEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_ControllerButtonEvent(Value_SDL_ControllerButtonEvent&& src) noexcept = delete;
	Value_SDL_ControllerButtonEvent& operator=(Value_SDL_ControllerButtonEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_ControllerButtonEvent() = default;
public:
	SDL_ControllerButtonEvent& GetEntity() { return _pValue->GetEntity().cbutton; }
	const SDL_ControllerButtonEvent& GetEntity() const { return _pValue->GetEntity().cbutton; }
	SDL_ControllerButtonEvent* GetEntityPtr() { return &_pValue->GetEntity().cbutton; }
	const SDL_ControllerButtonEvent* GetEntityPtr() const { return &_pValue->GetEntity().cbutton; }
public:
	static SDL_ControllerButtonEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_ControllerButtonEvent&>(value).GetEntity();
	}
	static const SDL_ControllerButtonEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerButtonEvent&>(value).GetEntity();
	}
	static SDL_ControllerButtonEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_ControllerButtonEvent&>(value).GetEntityPtr();
	}
	static const SDL_ControllerButtonEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerButtonEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_ControllerButtonEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_ControllerButtonEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
