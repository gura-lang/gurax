//==============================================================================
// VType_SDL_MouseButtonEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_MouseButtonEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_MouseButtonEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_MouseButtonEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_MouseButtonEvent VTYPE_SDL_MouseButtonEvent;

//------------------------------------------------------------------------------
// Value_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_MouseButtonEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_MouseButtonEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_MouseButtonEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_MouseButtonEvent(VType& vtype = VTYPE_SDL_MouseButtonEvent) : Value_Object(vtype) {}
	explicit Value_SDL_MouseButtonEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_MouseButtonEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_MouseButtonEvent(const Value_SDL_MouseButtonEvent& src) = delete;
	Value_SDL_MouseButtonEvent& operator=(const Value_SDL_MouseButtonEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_MouseButtonEvent(Value_SDL_MouseButtonEvent&& src) noexcept = delete;
	Value_SDL_MouseButtonEvent& operator=(Value_SDL_MouseButtonEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_MouseButtonEvent() = default;
public:
	SDL_MouseButtonEvent& GetEntity() { return reinterpret_cast<SDL_MouseButtonEvent&>(_pValue->GetEntity()); }
	const SDL_MouseButtonEvent& GetEntity() const { return reinterpret_cast<SDL_MouseButtonEvent&>(_pValue->GetEntity()); }
	SDL_MouseButtonEvent* GetEntityPtr() { return &reinterpret_cast<SDL_MouseButtonEvent&>(_pValue->GetEntity()); }
	const SDL_MouseButtonEvent* GetEntityPtr() const { return &reinterpret_cast<SDL_MouseButtonEvent&>(_pValue->GetEntity()); }
public:
	static SDL_MouseButtonEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_MouseButtonEvent&>(value).GetEntity();
	}
	static const SDL_MouseButtonEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseButtonEvent&>(value).GetEntity();
	}
	static SDL_MouseButtonEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_MouseButtonEvent&>(value).GetEntityPtr();
	}
	static const SDL_MouseButtonEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseButtonEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_MouseButtonEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_MouseButtonEvent::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
