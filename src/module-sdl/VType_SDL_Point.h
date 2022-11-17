//==============================================================================
// VType_SDL_Point.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_POINT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_POINT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Point : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Point VTYPE_SDL_Point;

//------------------------------------------------------------------------------
// Value_SDL_Point
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Point : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Point);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Point");
protected:
	SDL_Point _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Point(VType& vtype = VTYPE_SDL_Point) : Value_Object(vtype) {}
	explicit Value_SDL_Point(const SDL_Point& entity, VType& vtype = VTYPE_SDL_Point) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Point(const Value_SDL_Point& src) = delete;
	Value_SDL_Point& operator=(const Value_SDL_Point& src) = delete;
	// Move constructor/operator
	Value_SDL_Point(Value_SDL_Point&& src) noexcept = delete;
	Value_SDL_Point& operator=(Value_SDL_Point&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Point() = default;
public:
	SDL_Point& GetEntity() { return _entity; }
	const SDL_Point& GetEntity() const { return _entity; }
	SDL_Point* GetEntityPtr() { return &_entity; }
	const SDL_Point* GetEntityPtr() const { return &_entity; }
public:
	static SDL_Point ValueForVector(Value& value) { return GetEntity(value); }
	static SDL_Point& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Point&>(value).GetEntity();
	}
	static const SDL_Point& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Point&>(value).GetEntity();
	}
	static SDL_Point* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Point&>(value).GetEntityPtr();
	}
	static const SDL_Point* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Point&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Point::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Point::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
