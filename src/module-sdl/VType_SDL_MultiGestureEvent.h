//==============================================================================
// VType_SDL_MultiGestureEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_MultiGestureEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_MultiGestureEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_MultiGestureEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_MultiGestureEvent VTYPE_SDL_MultiGestureEvent;

//------------------------------------------------------------------------------
// Value_SDL_MultiGestureEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_MultiGestureEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_MultiGestureEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_MultiGestureEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_MultiGestureEvent(VType& vtype = VTYPE_SDL_MultiGestureEvent) : Value_Object(vtype) {}
	explicit Value_SDL_MultiGestureEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_MultiGestureEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_MultiGestureEvent(const Value_SDL_MultiGestureEvent& src) = delete;
	Value_SDL_MultiGestureEvent& operator=(const Value_SDL_MultiGestureEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_MultiGestureEvent(Value_SDL_MultiGestureEvent&& src) noexcept = delete;
	Value_SDL_MultiGestureEvent& operator=(Value_SDL_MultiGestureEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_MultiGestureEvent() = default;
public:
	SDL_MultiGestureEvent& GetEntity() { return _pValue->GetEntity().mgesture; }
	const SDL_MultiGestureEvent& GetEntity() const { return _pValue->GetEntity().mgesture; }
	SDL_MultiGestureEvent* GetEntityPtr() { return &_pValue->GetEntity().mgesture; }
	const SDL_MultiGestureEvent* GetEntityPtr() const { return &_pValue->GetEntity().mgesture; }
public:
	static SDL_MultiGestureEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_MultiGestureEvent&>(value).GetEntity();
	}
	static const SDL_MultiGestureEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_MultiGestureEvent&>(value).GetEntity();
	}
	static SDL_MultiGestureEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_MultiGestureEvent&>(value).GetEntityPtr();
	}
	static const SDL_MultiGestureEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_MultiGestureEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_MultiGestureEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_MultiGestureEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
