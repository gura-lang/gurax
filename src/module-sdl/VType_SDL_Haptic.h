//==============================================================================
// VType_SDL_Haptic.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTIC_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTIC_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Haptic
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Haptic : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Haptic VTYPE_SDL_Haptic;

//------------------------------------------------------------------------------
// Value_SDL_Haptic
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Haptic : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Haptic);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Haptic");
protected:
	SDL_Haptic* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Haptic(VType& vtype = VTYPE_SDL_Haptic) : Value_Object(vtype) {}
	explicit Value_SDL_Haptic(SDL_Haptic* entity, VType& vtype = VTYPE_SDL_Haptic) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Haptic(const Value_SDL_Haptic& src) = delete;
	Value_SDL_Haptic& operator=(const Value_SDL_Haptic& src) = delete;
	// Move constructor/operator
	Value_SDL_Haptic(Value_SDL_Haptic&& src) noexcept = delete;
	Value_SDL_Haptic& operator=(Value_SDL_Haptic&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Haptic() = default;
public:
	SDL_Haptic& GetEntity() { return *_entity; }
	const SDL_Haptic& GetEntity() const { return *_entity; }
	SDL_Haptic* GetEntityPtr() { return _entity; }
	const SDL_Haptic* GetEntityPtr() const { return _entity; }
public:
	static SDL_Haptic& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Haptic&>(value).GetEntity();
	}
	static const SDL_Haptic& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Haptic&>(value).GetEntity();
	}
	static SDL_Haptic* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Haptic&>(value).GetEntityPtr();
	}
	static const SDL_Haptic* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Haptic&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Haptic::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Haptic::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
