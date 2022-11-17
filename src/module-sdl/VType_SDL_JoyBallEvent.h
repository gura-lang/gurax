//==============================================================================
// VType_SDL_JoyBallEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JoyBallEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JoyBallEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoyBallEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoyBallEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoyBallEvent VTYPE_SDL_JoyBallEvent;

//------------------------------------------------------------------------------
// Value_SDL_JoyBallEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoyBallEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoyBallEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoyBallEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoyBallEvent(VType& vtype = VTYPE_SDL_JoyBallEvent) : Value_Object(vtype) {}
	explicit Value_SDL_JoyBallEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_JoyBallEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_JoyBallEvent(const Value_SDL_JoyBallEvent& src) = delete;
	Value_SDL_JoyBallEvent& operator=(const Value_SDL_JoyBallEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_JoyBallEvent(Value_SDL_JoyBallEvent&& src) noexcept = delete;
	Value_SDL_JoyBallEvent& operator=(Value_SDL_JoyBallEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoyBallEvent() = default;
public:
	SDL_JoyBallEvent& GetEntity() { return _pValue->GetEntity().jball; }
	const SDL_JoyBallEvent& GetEntity() const { return _pValue->GetEntity().jball; }
	SDL_JoyBallEvent* GetEntityPtr() { return &_pValue->GetEntity().jball; }
	const SDL_JoyBallEvent* GetEntityPtr() const { return &_pValue->GetEntity().jball; }
public:
	static SDL_JoyBallEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoyBallEvent&>(value).GetEntity();
	}
	static const SDL_JoyBallEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyBallEvent&>(value).GetEntity();
	}
	static SDL_JoyBallEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoyBallEvent&>(value).GetEntityPtr();
	}
	static const SDL_JoyBallEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyBallEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoyBallEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoyBallEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
