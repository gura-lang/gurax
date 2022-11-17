//==============================================================================
// VType_SDL_FPoint.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_FPOINT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_FPOINT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_FPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_FPoint : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_FPoint VTYPE_SDL_FPoint;

//------------------------------------------------------------------------------
// Value_SDL_FPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_FPoint : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_FPoint);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_FPoint");
protected:
	SDL_FPoint _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_FPoint(VType& vtype = VTYPE_SDL_FPoint) : Value_Object(vtype) {}
	explicit Value_SDL_FPoint(const SDL_FPoint& entity, VType& vtype = VTYPE_SDL_FPoint) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_FPoint(const Value_SDL_FPoint& src) = delete;
	Value_SDL_FPoint& operator=(const Value_SDL_FPoint& src) = delete;
	// Move constructor/operator
	Value_SDL_FPoint(Value_SDL_FPoint&& src) noexcept = delete;
	Value_SDL_FPoint& operator=(Value_SDL_FPoint&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_FPoint() = default;
public:
	SDL_FPoint& GetEntity() { return _entity; }
	const SDL_FPoint& GetEntity() const { return _entity; }
	SDL_FPoint* GetEntityPtr() { return &_entity; }
	const SDL_FPoint* GetEntityPtr() const { return &_entity; }
public:
	static SDL_FPoint ValueForVector(Value& value) { return GetEntity(value); }
	static SDL_FPoint& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_FPoint&>(value).GetEntity();
	}
	static const SDL_FPoint& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_FPoint&>(value).GetEntity();
	}
	static SDL_FPoint* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_FPoint&>(value).GetEntityPtr();
	}
	static const SDL_FPoint* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_FPoint&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_FPoint::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_FPoint::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
