//==============================================================================
// VType_SDL_Joystick.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JOYSTICK_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JOYSTICK_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Joystick
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Joystick : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Joystick VTYPE_SDL_Joystick;

//------------------------------------------------------------------------------
// Value_SDL_Joystick
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Joystick : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Joystick);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Joystick");
protected:
	SDL_Joystick* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Joystick(VType& vtype = VTYPE_SDL_Joystick) : Value_Object(vtype) {}
	explicit Value_SDL_Joystick(SDL_Joystick* entity, VType& vtype = VTYPE_SDL_Joystick) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Joystick(const Value_SDL_Joystick& src) = delete;
	Value_SDL_Joystick& operator=(const Value_SDL_Joystick& src) = delete;
	// Move constructor/operator
	Value_SDL_Joystick(Value_SDL_Joystick&& src) noexcept = delete;
	Value_SDL_Joystick& operator=(Value_SDL_Joystick&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Joystick() = default;
public:
	SDL_Joystick& GetEntity() { return *_entity; }
	const SDL_Joystick& GetEntity() const { return *_entity; }
	SDL_Joystick* GetEntityPtr() { return _entity; }
	const SDL_Joystick* GetEntityPtr() const { return _entity; }
public:
	static SDL_Joystick& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Joystick&>(value).GetEntity();
	}
	static const SDL_Joystick& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Joystick&>(value).GetEntity();
	}
	static SDL_Joystick* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Joystick&>(value).GetEntityPtr();
	}
	static const SDL_Joystick* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Joystick&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Joystick::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Joystick::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
