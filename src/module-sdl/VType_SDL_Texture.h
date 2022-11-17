//==============================================================================
// VType_SDL_Texture.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_TEXTURE_H
#define GURAX_MODULE_SDL_VTYPE_SDL_TEXTURE_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Texture
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Texture : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Texture VTYPE_SDL_Texture;

//------------------------------------------------------------------------------
// Value_SDL_Texture
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Texture : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Texture);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Texture");
protected:
	SDL_Texture* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Texture(VType& vtype = VTYPE_SDL_Texture) : Value_Object(vtype) {}
	explicit Value_SDL_Texture(SDL_Texture* entity, VType& vtype = VTYPE_SDL_Texture) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Texture(const Value_SDL_Texture& src) = delete;
	Value_SDL_Texture& operator=(const Value_SDL_Texture& src) = delete;
	// Move constructor/operator
	Value_SDL_Texture(Value_SDL_Texture&& src) noexcept = delete;
	Value_SDL_Texture& operator=(Value_SDL_Texture&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Texture() = default;
public:
	SDL_Texture& GetEntity() { return *_entity; }
	const SDL_Texture& GetEntity() const { return *_entity; }
	SDL_Texture* GetEntityPtr() { return _entity; }
	const SDL_Texture* GetEntityPtr() const { return _entity; }
public:
	static SDL_Texture& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Texture&>(value).GetEntity();
	}
	static const SDL_Texture& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Texture&>(value).GetEntity();
	}
	static SDL_Texture* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Texture&>(value).GetEntityPtr();
	}
	static const SDL_Texture* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Texture&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Texture::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Texture::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
