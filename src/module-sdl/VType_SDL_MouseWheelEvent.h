//==============================================================================
// VType_SDL_MouseWheelEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_MouseWheelEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_MouseWheelEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_MouseWheelEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_MouseWheelEvent VTYPE_SDL_MouseWheelEvent;

//------------------------------------------------------------------------------
// Value_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_MouseWheelEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_MouseWheelEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_MouseWheelEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_MouseWheelEvent(VType& vtype = VTYPE_SDL_MouseWheelEvent) : Value_Object(vtype) {}
	explicit Value_SDL_MouseWheelEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_MouseWheelEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_MouseWheelEvent(const Value_SDL_MouseWheelEvent& src) = delete;
	Value_SDL_MouseWheelEvent& operator=(const Value_SDL_MouseWheelEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_MouseWheelEvent(Value_SDL_MouseWheelEvent&& src) noexcept = delete;
	Value_SDL_MouseWheelEvent& operator=(Value_SDL_MouseWheelEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_MouseWheelEvent() = default;
public:
	SDL_MouseWheelEvent& GetEntity() { return _pValue->GetEntity().wheel; }
	const SDL_MouseWheelEvent& GetEntity() const { return _pValue->GetEntity().wheel; }
	SDL_MouseWheelEvent* GetEntityPtr() { return &_pValue->GetEntity().wheel; }
	const SDL_MouseWheelEvent* GetEntityPtr() const { return &_pValue->GetEntity().wheel; }
public:
	static SDL_MouseWheelEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_MouseWheelEvent&>(value).GetEntity();
	}
	static const SDL_MouseWheelEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseWheelEvent&>(value).GetEntity();
	}
	static SDL_MouseWheelEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_MouseWheelEvent&>(value).GetEntityPtr();
	}
	static const SDL_MouseWheelEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseWheelEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_MouseWheelEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_MouseWheelEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
