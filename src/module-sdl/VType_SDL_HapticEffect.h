//==============================================================================
// VType_SDL_HapticEffect.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICEFFECT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICEFFECT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticEffect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticEffect : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticEffect VTYPE_SDL_HapticEffect;

//------------------------------------------------------------------------------
// Value_SDL_HapticEffect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticEffect : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticEffect);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticEffect");
protected:
	SDL_HapticEffect _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticEffect(VType& vtype = VTYPE_SDL_HapticEffect) : Value_Object(vtype) {}
	explicit Value_SDL_HapticEffect(const SDL_HapticEffect& entity, VType& vtype = VTYPE_SDL_HapticEffect) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_HapticEffect(const Value_SDL_HapticEffect& src) = delete;
	Value_SDL_HapticEffect& operator=(const Value_SDL_HapticEffect& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticEffect(Value_SDL_HapticEffect&& src) noexcept = delete;
	Value_SDL_HapticEffect& operator=(Value_SDL_HapticEffect&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticEffect() = default;
public:
	SDL_HapticEffect& GetEntity() { return _entity; }
	const SDL_HapticEffect& GetEntity() const { return _entity; }
	SDL_HapticEffect* GetEntityPtr() { return &_entity; }
	const SDL_HapticEffect* GetEntityPtr() const { return &_entity; }
public:
	static SDL_HapticEffect& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticEffect&>(value).GetEntity();
	}
	static const SDL_HapticEffect& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticEffect&>(value).GetEntity();
	}
	static SDL_HapticEffect* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticEffect&>(value).GetEntityPtr();
	}
	static const SDL_HapticEffect* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticEffect&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_HapticEffect::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticEffect::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
