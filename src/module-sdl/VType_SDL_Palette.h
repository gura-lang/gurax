//==============================================================================
// VType_SDL_Palette.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_PALETTE_H
#define GURAX_MODULE_SDL_VTYPE_SDL_PALETTE_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Palette : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Palette VTYPE_SDL_Palette;

//------------------------------------------------------------------------------
// Value_SDL_Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Palette : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Palette);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Palette");
protected:
	SDL_Palette* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Palette(VType& vtype = VTYPE_SDL_Palette) : Value_Object(vtype) {}
	explicit Value_SDL_Palette(SDL_Palette* entity, VType& vtype = VTYPE_SDL_Palette) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Palette(const Value_SDL_Palette& src) = delete;
	Value_SDL_Palette& operator=(const Value_SDL_Palette& src) = delete;
	// Move constructor/operator
	Value_SDL_Palette(Value_SDL_Palette&& src) noexcept = delete;
	Value_SDL_Palette& operator=(Value_SDL_Palette&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Palette() = default;
public:
	SDL_Palette& GetEntity() { return *_entity; }
	const SDL_Palette& GetEntity() const { return *_entity; }
	SDL_Palette* GetEntityPtr() { return _entity; }
	const SDL_Palette* GetEntityPtr() const { return _entity; }
public:
	static SDL_Palette& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Palette&>(value).GetEntity();
	}
	static const SDL_Palette& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Palette&>(value).GetEntity();
	}
	static SDL_Palette* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Palette&>(value).GetEntityPtr();
	}
	static const SDL_Palette* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Palette&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Palette::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Palette::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
