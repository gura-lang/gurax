//==============================================================================
// VType_SDL_GameController.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_GAMECONTROLLER_H
#define GURAX_MODULE_SDL_VTYPE_SDL_GAMECONTROLLER_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_GameController
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_GameController : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_GameController VTYPE_SDL_GameController;

//------------------------------------------------------------------------------
// Value_SDL_GameController
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_GameController : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_GameController);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_GameController");
protected:
	SDL_GameController* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_GameController(VType& vtype = VTYPE_SDL_GameController) : Value_Object(vtype) {}
	explicit Value_SDL_GameController(SDL_GameController* entity, VType& vtype = VTYPE_SDL_GameController) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_GameController(const Value_SDL_GameController& src) = delete;
	Value_SDL_GameController& operator=(const Value_SDL_GameController& src) = delete;
	// Move constructor/operator
	Value_SDL_GameController(Value_SDL_GameController&& src) noexcept = delete;
	Value_SDL_GameController& operator=(Value_SDL_GameController&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_GameController() = default;
public:
	SDL_GameController& GetEntity() { return *_entity; }
	const SDL_GameController& GetEntity() const { return *_entity; }
	SDL_GameController* GetEntityPtr() { return _entity; }
	const SDL_GameController* GetEntityPtr() const { return _entity; }
public:
	static SDL_GameController& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_GameController&>(value).GetEntity();
	}
	static const SDL_GameController& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_GameController&>(value).GetEntity();
	}
	static SDL_GameController* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_GameController&>(value).GetEntityPtr();
	}
	static const SDL_GameController* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_GameController&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_GameController::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_GameController::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
