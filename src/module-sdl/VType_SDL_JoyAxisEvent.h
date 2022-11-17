//==============================================================================
// VType_SDL_JoyAxisEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JoyAxisEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JoyAxisEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoyAxisEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoyAxisEvent VTYPE_SDL_JoyAxisEvent;

//------------------------------------------------------------------------------
// Value_SDL_JoyAxisEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoyAxisEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoyAxisEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoyAxisEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoyAxisEvent(VType& vtype = VTYPE_SDL_JoyAxisEvent) : Value_Object(vtype) {}
	explicit Value_SDL_JoyAxisEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_JoyAxisEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_JoyAxisEvent(const Value_SDL_JoyAxisEvent& src) = delete;
	Value_SDL_JoyAxisEvent& operator=(const Value_SDL_JoyAxisEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_JoyAxisEvent(Value_SDL_JoyAxisEvent&& src) noexcept = delete;
	Value_SDL_JoyAxisEvent& operator=(Value_SDL_JoyAxisEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoyAxisEvent() = default;
public:
	SDL_JoyAxisEvent& GetEntity() { return _pValue->GetEntity().jaxis; }
	const SDL_JoyAxisEvent& GetEntity() const { return _pValue->GetEntity().jaxis; }
	SDL_JoyAxisEvent* GetEntityPtr() { return &_pValue->GetEntity().jaxis; }
	const SDL_JoyAxisEvent* GetEntityPtr() const { return &_pValue->GetEntity().jaxis; }
public:
	static SDL_JoyAxisEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoyAxisEvent&>(value).GetEntity();
	}
	static const SDL_JoyAxisEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyAxisEvent&>(value).GetEntity();
	}
	static SDL_JoyAxisEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoyAxisEvent&>(value).GetEntityPtr();
	}
	static const SDL_JoyAxisEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyAxisEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoyAxisEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoyAxisEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
