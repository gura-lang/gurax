//==============================================================================
// VType_SDL_JoyButtonEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JoyButtonEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JoyButtonEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoyButtonEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoyButtonEvent VTYPE_SDL_JoyButtonEvent;

//------------------------------------------------------------------------------
// Value_SDL_JoyButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoyButtonEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoyButtonEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoyButtonEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoyButtonEvent(VType& vtype = VTYPE_SDL_JoyButtonEvent) : Value_Object(vtype) {}
	explicit Value_SDL_JoyButtonEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_JoyButtonEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_JoyButtonEvent(const Value_SDL_JoyButtonEvent& src) = delete;
	Value_SDL_JoyButtonEvent& operator=(const Value_SDL_JoyButtonEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_JoyButtonEvent(Value_SDL_JoyButtonEvent&& src) noexcept = delete;
	Value_SDL_JoyButtonEvent& operator=(Value_SDL_JoyButtonEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoyButtonEvent() = default;
public:
	SDL_JoyButtonEvent& GetEntity() { return _pValue->GetEntity().jbutton; }
	const SDL_JoyButtonEvent& GetEntity() const { return _pValue->GetEntity().jbutton; }
	SDL_JoyButtonEvent* GetEntityPtr() { return &_pValue->GetEntity().jbutton; }
	const SDL_JoyButtonEvent* GetEntityPtr() const { return &_pValue->GetEntity().jbutton; }
public:
	static SDL_JoyButtonEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoyButtonEvent&>(value).GetEntity();
	}
	static const SDL_JoyButtonEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyButtonEvent&>(value).GetEntity();
	}
	static SDL_JoyButtonEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoyButtonEvent&>(value).GetEntityPtr();
	}
	static const SDL_JoyButtonEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyButtonEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoyButtonEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoyButtonEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
