//==============================================================================
// VType_SDL_version.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_VERSION_H
#define GURAX_MODULE_SDL_VTYPE_SDL_VERSION_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_version
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_version : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_version VTYPE_SDL_version;

//------------------------------------------------------------------------------
// Value_SDL_version
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_version : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_version);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_version");
protected:
	SDL_version _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_version(VType& vtype = VTYPE_SDL_version) : Value_Object(vtype) {}
	explicit Value_SDL_version(const SDL_version& entity, VType& vtype = VTYPE_SDL_version) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_version(const Value_SDL_version& src) = delete;
	Value_SDL_version& operator=(const Value_SDL_version& src) = delete;
	// Move constructor/operator
	Value_SDL_version(Value_SDL_version&& src) noexcept = delete;
	Value_SDL_version& operator=(Value_SDL_version&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_version() = default;
public:
	SDL_version& GetEntity() { return _entity; }
	const SDL_version& GetEntity() const { return _entity; }
	SDL_version* GetEntityPtr() { return &_entity; }
	const SDL_version* GetEntityPtr() const { return &_entity; }
public:
	static SDL_version& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_version&>(value).GetEntity();
	}
	static const SDL_version& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_version&>(value).GetEntity();
	}
	static SDL_version* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_version&>(value).GetEntityPtr();
	}
	static const SDL_version* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_version&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_version::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_version::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
