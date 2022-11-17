//==============================================================================
// VType_SDL_TouchFingerEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_TouchFingerEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_TouchFingerEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_TouchFingerEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_TouchFingerEvent VTYPE_SDL_TouchFingerEvent;

//------------------------------------------------------------------------------
// Value_SDL_TouchFingerEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_TouchFingerEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_TouchFingerEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_TouchFingerEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_TouchFingerEvent(VType& vtype = VTYPE_SDL_TouchFingerEvent) : Value_Object(vtype) {}
	explicit Value_SDL_TouchFingerEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_TouchFingerEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_TouchFingerEvent(const Value_SDL_TouchFingerEvent& src) = delete;
	Value_SDL_TouchFingerEvent& operator=(const Value_SDL_TouchFingerEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_TouchFingerEvent(Value_SDL_TouchFingerEvent&& src) noexcept = delete;
	Value_SDL_TouchFingerEvent& operator=(Value_SDL_TouchFingerEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_TouchFingerEvent() = default;
public:
	SDL_TouchFingerEvent& GetEntity() { return _pValue->GetEntity().tfinger; }
	const SDL_TouchFingerEvent& GetEntity() const { return _pValue->GetEntity().tfinger; }
	SDL_TouchFingerEvent* GetEntityPtr() { return &_pValue->GetEntity().tfinger; }
	const SDL_TouchFingerEvent* GetEntityPtr() const { return &_pValue->GetEntity().tfinger; }
public:
	static SDL_TouchFingerEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_TouchFingerEvent&>(value).GetEntity();
	}
	static const SDL_TouchFingerEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_TouchFingerEvent&>(value).GetEntity();
	}
	static SDL_TouchFingerEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_TouchFingerEvent&>(value).GetEntityPtr();
	}
	static const SDL_TouchFingerEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_TouchFingerEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_TouchFingerEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_TouchFingerEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
