//==============================================================================
// VType_SDL_RWops.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_RWOPS_H
#define GURAX_MODULE_SDL_VTYPE_SDL_RWOPS_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_RWops
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_RWops : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_RWops VTYPE_SDL_RWops;

//------------------------------------------------------------------------------
// Value_SDL_RWops
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_RWops : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_RWops);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_RWops");
protected:
	SDL_RWops* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_RWops(VType& vtype = VTYPE_SDL_RWops) : Value_Object(vtype) {}
	explicit Value_SDL_RWops(SDL_RWops* entity, VType& vtype = VTYPE_SDL_RWops) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_RWops(const Value_SDL_RWops& src) = delete;
	Value_SDL_RWops& operator=(const Value_SDL_RWops& src) = delete;
	// Move constructor/operator
	Value_SDL_RWops(Value_SDL_RWops&& src) noexcept = delete;
	Value_SDL_RWops& operator=(Value_SDL_RWops&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_RWops() = default;
public:
	SDL_RWops& GetEntity() { return *_entity; }
	const SDL_RWops& GetEntity() const { return *_entity; }
	SDL_RWops* GetEntityPtr() { return _entity; }
	const SDL_RWops* GetEntityPtr() const { return _entity; }
public:
	static SDL_RWops& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_RWops&>(value).GetEntity();
	}
	static const SDL_RWops& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_RWops&>(value).GetEntity();
	}
	static SDL_RWops* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_RWops&>(value).GetEntityPtr();
	}
	static const SDL_RWops* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_RWops&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_RWops::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_RWops::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
