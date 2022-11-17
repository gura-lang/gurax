//==============================================================================
// VType_SDL_Renderer.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_RENDERER_H
#define GURAX_MODULE_SDL_VTYPE_SDL_RENDERER_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Renderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Renderer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Renderer VTYPE_SDL_Renderer;

//------------------------------------------------------------------------------
// Value_SDL_Renderer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Renderer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Renderer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Renderer");
protected:
	SDL_Renderer* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Renderer(VType& vtype = VTYPE_SDL_Renderer) : Value_Object(vtype) {}
	explicit Value_SDL_Renderer(SDL_Renderer* entity, VType& vtype = VTYPE_SDL_Renderer) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Renderer(const Value_SDL_Renderer& src) = delete;
	Value_SDL_Renderer& operator=(const Value_SDL_Renderer& src) = delete;
	// Move constructor/operator
	Value_SDL_Renderer(Value_SDL_Renderer&& src) noexcept = delete;
	Value_SDL_Renderer& operator=(Value_SDL_Renderer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Renderer() = default;
public:
	SDL_Renderer& GetEntity() { return *_entity; }
	const SDL_Renderer& GetEntity() const { return *_entity; }
	SDL_Renderer* GetEntityPtr() { return _entity; }
	const SDL_Renderer* GetEntityPtr() const { return _entity; }
public:
	static SDL_Renderer& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Renderer&>(value).GetEntity();
	}
	static const SDL_Renderer& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Renderer&>(value).GetEntity();
	}
	static SDL_Renderer* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Renderer&>(value).GetEntityPtr();
	}
	static const SDL_Renderer* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Renderer&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Renderer::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Renderer::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
