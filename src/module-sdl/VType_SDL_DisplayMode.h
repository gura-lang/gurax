//==============================================================================
// VType_SDL_DisplayMode.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_DISPLAYMODE_H
#define GURAX_MODULE_SDL_VTYPE_SDL_DISPLAYMODE_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_DisplayMode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_DisplayMode : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_DisplayMode VTYPE_SDL_DisplayMode;

//------------------------------------------------------------------------------
// Value_SDL_DisplayMode
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_DisplayMode : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_DisplayMode);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_DisplayMode");
protected:
	SDL_DisplayMode _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_DisplayMode(VType& vtype = VTYPE_SDL_DisplayMode) : Value_Object(vtype) {}
	explicit Value_SDL_DisplayMode(const SDL_DisplayMode& entity, VType& vtype = VTYPE_SDL_DisplayMode) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_DisplayMode(const Value_SDL_DisplayMode& src) = delete;
	Value_SDL_DisplayMode& operator=(const Value_SDL_DisplayMode& src) = delete;
	// Move constructor/operator
	Value_SDL_DisplayMode(Value_SDL_DisplayMode&& src) noexcept = delete;
	Value_SDL_DisplayMode& operator=(Value_SDL_DisplayMode&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_DisplayMode() = default;
public:
	SDL_DisplayMode& GetEntity() { return _entity; }
	const SDL_DisplayMode& GetEntity() const { return _entity; }
	SDL_DisplayMode* GetEntityPtr() { return &_entity; }
	const SDL_DisplayMode* GetEntityPtr() const { return &_entity; }
public:
	static SDL_DisplayMode& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_DisplayMode&>(value).GetEntity();
	}
	static const SDL_DisplayMode& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_DisplayMode&>(value).GetEntity();
	}
	static SDL_DisplayMode* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_DisplayMode&>(value).GetEntityPtr();
	}
	static const SDL_DisplayMode* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_DisplayMode&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_DisplayMode::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_DisplayMode::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
