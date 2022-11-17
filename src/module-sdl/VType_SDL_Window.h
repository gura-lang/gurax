//==============================================================================
// VType_SDL_Window.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_WINDOW_H
#define GURAX_MODULE_SDL_VTYPE_SDL_WINDOW_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Window : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Window VTYPE_SDL_Window;

//------------------------------------------------------------------------------
// Value_SDL_Window
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Window : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Window);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Window");
protected:
	SDL_Window* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Window(VType& vtype = VTYPE_SDL_Window) : Value_Object(vtype) {}
	explicit Value_SDL_Window(SDL_Window* entity, VType& vtype = VTYPE_SDL_Window) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Window(const Value_SDL_Window& src) = delete;
	Value_SDL_Window& operator=(const Value_SDL_Window& src) = delete;
	// Move constructor/operator
	Value_SDL_Window(Value_SDL_Window&& src) noexcept = delete;
	Value_SDL_Window& operator=(Value_SDL_Window&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Window() = default;
public:
	SDL_Window& GetEntity() { return *_entity; }
	const SDL_Window& GetEntity() const { return *_entity; }
	SDL_Window* GetEntityPtr() { return _entity; }
	const SDL_Window* GetEntityPtr() const { return _entity; }
public:
	static SDL_Window& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Window&>(value).GetEntity();
	}
	static const SDL_Window& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Window&>(value).GetEntity();
	}
	static SDL_Window* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Window&>(value).GetEntityPtr();
	}
	static const SDL_Window* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Window&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Window::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Window::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
