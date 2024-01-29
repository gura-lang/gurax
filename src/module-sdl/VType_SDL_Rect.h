//==============================================================================
// VType_SDL_Rect.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_RECT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_RECT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Rect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Rect : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const;
};

extern GURAX_DLLDECLARE VType_SDL_Rect VTYPE_SDL_Rect;

//------------------------------------------------------------------------------
// Value_SDL_Rect
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Rect : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Rect);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Rect");
protected:
	SDL_Rect _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Rect(VType& vtype = VTYPE_SDL_Rect) : Value_Object(vtype) {}
	explicit Value_SDL_Rect(const SDL_Rect& entity, VType& vtype = VTYPE_SDL_Rect) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Rect(const Value_SDL_Rect& src) = delete;
	Value_SDL_Rect& operator=(const Value_SDL_Rect& src) = delete;
	// Move constructor/operator
	Value_SDL_Rect(Value_SDL_Rect&& src) noexcept = delete;
	Value_SDL_Rect& operator=(Value_SDL_Rect&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Rect() = default;
public:
	SDL_Rect& GetEntity() { return _entity; }
	const SDL_Rect& GetEntity() const { return _entity; }
	SDL_Rect* GetEntityPtr() { return &_entity; }
	const SDL_Rect* GetEntityPtr() const { return &_entity; }
public:
	static SDL_Rect ValueForVector(Value& value) { return GetEntity(value); }
	static SDL_Rect& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Rect&>(value).GetEntity();
	}
	static const SDL_Rect& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Rect&>(value).GetEntity();
	}
	static SDL_Rect* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Rect&>(value).GetEntityPtr();
	}
	static const SDL_Rect* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Rect&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Rect::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Rect::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
