//==============================================================================
// VType_SDL_Cursor.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_CURSOR_H
#define GURAX_MODULE_SDL_VTYPE_SDL_CURSOR_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Cursor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Cursor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Cursor VTYPE_SDL_Cursor;

//------------------------------------------------------------------------------
// Value_SDL_Cursor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Cursor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Cursor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Cursor");
protected:
	SDL_Cursor* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Cursor(VType& vtype = VTYPE_SDL_Cursor) : Value_Object(vtype) {}
	explicit Value_SDL_Cursor(SDL_Cursor* entity, VType& vtype = VTYPE_SDL_Cursor) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Cursor(const Value_SDL_Cursor& src) = delete;
	Value_SDL_Cursor& operator=(const Value_SDL_Cursor& src) = delete;
	// Move constructor/operator
	Value_SDL_Cursor(Value_SDL_Cursor&& src) noexcept = delete;
	Value_SDL_Cursor& operator=(Value_SDL_Cursor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Cursor() = default;
public:
	SDL_Cursor& GetEntity() { return *_entity; }
	const SDL_Cursor& GetEntity() const { return *_entity; }
	SDL_Cursor* GetEntityPtr() { return _entity; }
	const SDL_Cursor* GetEntityPtr() const { return _entity; }
public:
	static SDL_Cursor& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Cursor&>(value).GetEntity();
	}
	static const SDL_Cursor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Cursor&>(value).GetEntity();
	}
	static SDL_Cursor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Cursor&>(value).GetEntityPtr();
	}
	static const SDL_Cursor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Cursor&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Cursor::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Cursor::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
