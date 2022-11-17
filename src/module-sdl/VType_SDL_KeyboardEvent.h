//==============================================================================
// VType_SDL_KeyboardEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_KeyboardEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_KeyboardEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_KeyboardEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_KeyboardEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_KeyboardEvent VTYPE_SDL_KeyboardEvent;

//------------------------------------------------------------------------------
// Value_SDL_KeyboardEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_KeyboardEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_KeyboardEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_KeyboardEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_KeyboardEvent(VType& vtype = VTYPE_SDL_KeyboardEvent) : Value_Object(vtype) {}
	explicit Value_SDL_KeyboardEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_KeyboardEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_KeyboardEvent(const Value_SDL_KeyboardEvent& src) = delete;
	Value_SDL_KeyboardEvent& operator=(const Value_SDL_KeyboardEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_KeyboardEvent(Value_SDL_KeyboardEvent&& src) noexcept = delete;
	Value_SDL_KeyboardEvent& operator=(Value_SDL_KeyboardEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_KeyboardEvent() = default;
public:
	SDL_KeyboardEvent& GetEntity() { return _pValue->GetEntity().key; }
	const SDL_KeyboardEvent& GetEntity() const { return _pValue->GetEntity().key; }
	SDL_KeyboardEvent* GetEntityPtr() { return &_pValue->GetEntity().key; }
	const SDL_KeyboardEvent* GetEntityPtr() const { return &_pValue->GetEntity().key; }
public:
	static SDL_KeyboardEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_KeyboardEvent&>(value).GetEntity();
	}
	static const SDL_KeyboardEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_KeyboardEvent&>(value).GetEntity();
	}
	static SDL_KeyboardEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_KeyboardEvent&>(value).GetEntityPtr();
	}
	static const SDL_KeyboardEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_KeyboardEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_KeyboardEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_KeyboardEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
