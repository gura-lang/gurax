//==============================================================================
// VType_SDL_GLContext.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_GLCONTEXT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_GLCONTEXT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_GLContext
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_GLContext : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_GLContext VTYPE_SDL_GLContext;

//------------------------------------------------------------------------------
// Value_SDL_GLContext
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_GLContext : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_GLContext);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_GLContext");
protected:
	SDL_GLContext _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_GLContext(VType& vtype = VTYPE_SDL_GLContext) : Value_Object(vtype) {}
	explicit Value_SDL_GLContext(const SDL_GLContext& entity, VType& vtype = VTYPE_SDL_GLContext) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_GLContext(const Value_SDL_GLContext& src) = delete;
	Value_SDL_GLContext& operator=(const Value_SDL_GLContext& src) = delete;
	// Move constructor/operator
	Value_SDL_GLContext(Value_SDL_GLContext&& src) noexcept = delete;
	Value_SDL_GLContext& operator=(Value_SDL_GLContext&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_GLContext() = default;
public:
	SDL_GLContext GetEntityPtr() { return _entity; }
	const SDL_GLContext GetEntityPtr() const { return _entity; }
public:
	static SDL_GLContext GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_GLContext&>(value).GetEntityPtr();
	}
	static const SDL_GLContext GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_GLContext&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_GLContext::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_GLContext::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
