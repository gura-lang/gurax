//==============================================================================
// VType_SDL_ControllerAxisEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_ControllerAxisEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_ControllerAxisEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_ControllerAxisEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_ControllerAxisEvent VTYPE_SDL_ControllerAxisEvent;

//------------------------------------------------------------------------------
// Value_SDL_ControllerAxisEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_ControllerAxisEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_ControllerAxisEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_ControllerAxisEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_ControllerAxisEvent(VType& vtype = VTYPE_SDL_ControllerAxisEvent) : Value_Object(vtype) {}
	explicit Value_SDL_ControllerAxisEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_ControllerAxisEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_ControllerAxisEvent(const Value_SDL_ControllerAxisEvent& src) = delete;
	Value_SDL_ControllerAxisEvent& operator=(const Value_SDL_ControllerAxisEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_ControllerAxisEvent(Value_SDL_ControllerAxisEvent&& src) noexcept = delete;
	Value_SDL_ControllerAxisEvent& operator=(Value_SDL_ControllerAxisEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_ControllerAxisEvent() = default;
public:
	SDL_ControllerAxisEvent& GetEntity() { return _pValue->GetEntity().caxis; }
	const SDL_ControllerAxisEvent& GetEntity() const { return _pValue->GetEntity().caxis; }
	SDL_ControllerAxisEvent* GetEntityPtr() { return &_pValue->GetEntity().caxis; }
	const SDL_ControllerAxisEvent* GetEntityPtr() const { return &_pValue->GetEntity().caxis; }
public:
	static SDL_ControllerAxisEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_ControllerAxisEvent&>(value).GetEntity();
	}
	static const SDL_ControllerAxisEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerAxisEvent&>(value).GetEntity();
	}
	static SDL_ControllerAxisEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_ControllerAxisEvent&>(value).GetEntityPtr();
	}
	static const SDL_ControllerAxisEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerAxisEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_ControllerAxisEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_ControllerAxisEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
