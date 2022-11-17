//==============================================================================
// VType_SDL_Event.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_EVENT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_EVENT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Event
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Event : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Event VTYPE_SDL_Event;

//------------------------------------------------------------------------------
// Value_SDL_Event
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Event : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Event);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Event");
protected:
	SDL_Event _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Event(VType& vtype = VTYPE_SDL_Event) : Value_Object(vtype) {}
	explicit Value_SDL_Event(const SDL_Event& entity, VType& vtype = VTYPE_SDL_Event) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Event(const Value_SDL_Event& src) = delete;
	Value_SDL_Event& operator=(const Value_SDL_Event& src) = delete;
	// Move constructor/operator
	Value_SDL_Event(Value_SDL_Event&& src) noexcept = delete;
	Value_SDL_Event& operator=(Value_SDL_Event&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Event() = default;
public:
	SDL_Event& GetEntity() { return _entity; }
	const SDL_Event& GetEntity() const { return _entity; }
	SDL_Event* GetEntityPtr() { return &_entity; }
	const SDL_Event* GetEntityPtr() const { return &_entity; }
public:
	static SDL_Event& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Event&>(value).GetEntity();
	}
	static const SDL_Event& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Event&>(value).GetEntity();
	}
	static SDL_Event* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Event&>(value).GetEntityPtr();
	}
	static const SDL_Event* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Event&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Event::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Event::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
