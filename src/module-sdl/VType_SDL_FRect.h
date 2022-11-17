//==============================================================================
// VType_SDL_FRect.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_FRECT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_FRECT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_FRect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_FRect : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_FRect VTYPE_SDL_FRect;

//------------------------------------------------------------------------------
// Value_SDL_FRect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_FRect : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_FRect);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_FRect");
protected:
	SDL_FRect _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_FRect(VType& vtype = VTYPE_SDL_FRect) : Value_Object(vtype) {}
	explicit Value_SDL_FRect(const SDL_FRect& entity, VType& vtype = VTYPE_SDL_FRect) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_FRect(const Value_SDL_FRect& src) = delete;
	Value_SDL_FRect& operator=(const Value_SDL_FRect& src) = delete;
	// Move constructor/operator
	Value_SDL_FRect(Value_SDL_FRect&& src) noexcept = delete;
	Value_SDL_FRect& operator=(Value_SDL_FRect&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_FRect() = default;
public:
	SDL_FRect& GetEntity() { return _entity; }
	const SDL_FRect& GetEntity() const { return _entity; }
	SDL_FRect* GetEntityPtr() { return &_entity; }
	const SDL_FRect* GetEntityPtr() const { return &_entity; }
public:
	static SDL_FRect ValueForVector(Value& value) { return GetEntity(value); }
	static SDL_FRect& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_FRect&>(value).GetEntity();
	}
	static const SDL_FRect& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_FRect&>(value).GetEntity();
	}
	static SDL_FRect* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_FRect&>(value).GetEntityPtr();
	}
	static const SDL_FRect* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_FRect&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_FRect::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_FRect::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
