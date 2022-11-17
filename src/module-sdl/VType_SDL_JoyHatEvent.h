//==============================================================================
// VType_SDL_JoyHatEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JoyHatEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JoyHatEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoyHatEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoyHatEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoyHatEvent VTYPE_SDL_JoyHatEvent;

//------------------------------------------------------------------------------
// Value_SDL_JoyHatEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoyHatEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoyHatEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoyHatEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoyHatEvent(VType& vtype = VTYPE_SDL_JoyHatEvent) : Value_Object(vtype) {}
	explicit Value_SDL_JoyHatEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_JoyHatEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_JoyHatEvent(const Value_SDL_JoyHatEvent& src) = delete;
	Value_SDL_JoyHatEvent& operator=(const Value_SDL_JoyHatEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_JoyHatEvent(Value_SDL_JoyHatEvent&& src) noexcept = delete;
	Value_SDL_JoyHatEvent& operator=(Value_SDL_JoyHatEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoyHatEvent() = default;
public:
	SDL_JoyHatEvent& GetEntity() { return _pValue->GetEntity().jhat; }
	const SDL_JoyHatEvent& GetEntity() const { return _pValue->GetEntity().jhat; }
	SDL_JoyHatEvent* GetEntityPtr() { return &_pValue->GetEntity().jhat; }
	const SDL_JoyHatEvent* GetEntityPtr() const { return &_pValue->GetEntity().jhat; }
public:
	static SDL_JoyHatEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoyHatEvent&>(value).GetEntity();
	}
	static const SDL_JoyHatEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyHatEvent&>(value).GetEntity();
	}
	static SDL_JoyHatEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoyHatEvent&>(value).GetEntityPtr();
	}
	static const SDL_JoyHatEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyHatEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoyHatEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoyHatEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
