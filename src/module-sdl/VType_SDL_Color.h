//==============================================================================
// VType_SDL_Color.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_COLOR_H
#define GURAX_MODULE_SDL_VTYPE_SDL_COLOR_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Color : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Color VTYPE_SDL_Color;

//------------------------------------------------------------------------------
// Value_SDL_Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Color : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Color);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Color");
protected:
	SDL_Color _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Color(VType& vtype = VTYPE_SDL_Color) : Value_Object(vtype) {}
	explicit Value_SDL_Color(const SDL_Color& entity, VType& vtype = VTYPE_SDL_Color) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Color(const Value_SDL_Color& src) = delete;
	Value_SDL_Color& operator=(const Value_SDL_Color& src) = delete;
	// Move constructor/operator
	Value_SDL_Color(Value_SDL_Color&& src) noexcept = delete;
	Value_SDL_Color& operator=(Value_SDL_Color&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Color() = default;
public:
	SDL_Color& GetEntity() { return _entity; }
	const SDL_Color& GetEntity() const { return _entity; }
	SDL_Color* GetEntityPtr() { return &_entity; }
	const SDL_Color* GetEntityPtr() const { return &_entity; }
public:
	static SDL_Color ValueForVector(Value& value) { return GetEntity(value); }
	static SDL_Color& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Color&>(value).GetEntity();
	}
	static const SDL_Color& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Color&>(value).GetEntity();
	}
	static SDL_Color* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Color&>(value).GetEntityPtr();
	}
	static const SDL_Color* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Color&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Color::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Color::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
