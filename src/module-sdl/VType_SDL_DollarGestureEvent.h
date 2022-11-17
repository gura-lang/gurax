//==============================================================================
// VType_SDL_DollarGestureEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_DollarGestureEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_DollarGestureEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_DollarGestureEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_DollarGestureEvent VTYPE_SDL_DollarGestureEvent;

//------------------------------------------------------------------------------
// Value_SDL_DollarGestureEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_DollarGestureEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_DollarGestureEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_DollarGestureEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_DollarGestureEvent(VType& vtype = VTYPE_SDL_DollarGestureEvent) : Value_Object(vtype) {}
	explicit Value_SDL_DollarGestureEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_DollarGestureEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_DollarGestureEvent(const Value_SDL_DollarGestureEvent& src) = delete;
	Value_SDL_DollarGestureEvent& operator=(const Value_SDL_DollarGestureEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_DollarGestureEvent(Value_SDL_DollarGestureEvent&& src) noexcept = delete;
	Value_SDL_DollarGestureEvent& operator=(Value_SDL_DollarGestureEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_DollarGestureEvent() = default;
public:
	SDL_DollarGestureEvent& GetEntity() { return _pValue->GetEntity().dgesture; }
	const SDL_DollarGestureEvent& GetEntity() const { return _pValue->GetEntity().dgesture; }
	SDL_DollarGestureEvent* GetEntityPtr() { return &_pValue->GetEntity().dgesture; }
	const SDL_DollarGestureEvent* GetEntityPtr() const { return &_pValue->GetEntity().dgesture; }
public:
	static SDL_DollarGestureEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_DollarGestureEvent&>(value).GetEntity();
	}
	static const SDL_DollarGestureEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_DollarGestureEvent&>(value).GetEntity();
	}
	static SDL_DollarGestureEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_DollarGestureEvent&>(value).GetEntityPtr();
	}
	static const SDL_DollarGestureEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_DollarGestureEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_DollarGestureEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_DollarGestureEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
