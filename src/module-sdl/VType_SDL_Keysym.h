//==============================================================================
// VType_SDL_Keysym.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_KEYSYM_H
#define GURAX_MODULE_SDL_VTYPE_SDL_KEYSYM_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Keysym
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Keysym : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Keysym VTYPE_SDL_Keysym;

//------------------------------------------------------------------------------
// Value_SDL_Keysym
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Keysym : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Keysym);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Keysym");
protected:
	SDL_Keysym _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Keysym(VType& vtype = VTYPE_SDL_Keysym) : Value_Object(vtype) {}
	explicit Value_SDL_Keysym(const SDL_Keysym& entity, VType& vtype = VTYPE_SDL_Keysym) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Keysym(const Value_SDL_Keysym& src) = delete;
	Value_SDL_Keysym& operator=(const Value_SDL_Keysym& src) = delete;
	// Move constructor/operator
	Value_SDL_Keysym(Value_SDL_Keysym&& src) noexcept = delete;
	Value_SDL_Keysym& operator=(Value_SDL_Keysym&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Keysym() = default;
public:
	SDL_Keysym& GetEntity() { return _entity; }
	const SDL_Keysym& GetEntity() const { return _entity; }
	SDL_Keysym* GetEntityPtr() { return &_entity; }
	const SDL_Keysym* GetEntityPtr() const { return &_entity; }
public:
	static SDL_Keysym& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Keysym&>(value).GetEntity();
	}
	static const SDL_Keysym& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Keysym&>(value).GetEntity();
	}
	static SDL_Keysym* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Keysym&>(value).GetEntityPtr();
	}
	static const SDL_Keysym* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Keysym&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Keysym::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Keysym::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
