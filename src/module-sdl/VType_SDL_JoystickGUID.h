//==============================================================================
// VType_SDL_JoystickGUID.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JOYSTICKGUID_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JOYSTICKGUID_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoystickGUID
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoystickGUID : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoystickGUID VTYPE_SDL_JoystickGUID;

//------------------------------------------------------------------------------
// Value_SDL_JoystickGUID
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoystickGUID : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoystickGUID);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoystickGUID");
protected:
	SDL_JoystickGUID _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoystickGUID(VType& vtype = VTYPE_SDL_JoystickGUID) : Value_Object(vtype) {}
	explicit Value_SDL_JoystickGUID(const SDL_JoystickGUID& entity, VType& vtype = VTYPE_SDL_JoystickGUID) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_JoystickGUID(const Value_SDL_JoystickGUID& src) = delete;
	Value_SDL_JoystickGUID& operator=(const Value_SDL_JoystickGUID& src) = delete;
	// Move constructor/operator
	Value_SDL_JoystickGUID(Value_SDL_JoystickGUID&& src) noexcept = delete;
	Value_SDL_JoystickGUID& operator=(Value_SDL_JoystickGUID&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoystickGUID() = default;
public:
	SDL_JoystickGUID& GetEntity() { return _entity; }
	const SDL_JoystickGUID& GetEntity() const { return _entity; }
	SDL_JoystickGUID* GetEntityPtr() { return &_entity; }
	const SDL_JoystickGUID* GetEntityPtr() const { return &_entity; }
public:
	static SDL_JoystickGUID& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoystickGUID&>(value).GetEntity();
	}
	static const SDL_JoystickGUID& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoystickGUID&>(value).GetEntity();
	}
	static SDL_JoystickGUID* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoystickGUID&>(value).GetEntityPtr();
	}
	static const SDL_JoystickGUID* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoystickGUID&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoystickGUID::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoystickGUID::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
