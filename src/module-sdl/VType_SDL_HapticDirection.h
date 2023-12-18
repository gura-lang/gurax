//==============================================================================
// VType_SDL_HapticDirection.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICDIRECTION_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICDIRECTION_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticDirection
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticDirection : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticDirection VTYPE_SDL_HapticDirection;

//------------------------------------------------------------------------------
// Value_SDL_HapticDirection
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticDirection : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticDirection);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticDirection");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticDirection(VType& vtype = VTYPE_SDL_HapticDirection) : Value_Object(vtype) {}
	explicit Value_SDL_HapticDirection(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticDirection) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticDirection(const Value_SDL_HapticDirection& src) = delete;
	Value_SDL_HapticDirection& operator=(const Value_SDL_HapticDirection& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticDirection(Value_SDL_HapticDirection&& src) noexcept = delete;
	Value_SDL_HapticDirection& operator=(Value_SDL_HapticDirection&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticDirection() = default;
public:
	SDL_HapticDirection& GetEntity() { return _pValue_HapticEffect->GetEntity().constant.direction; }
	const SDL_HapticDirection& GetEntity() const { return _pValue_HapticEffect->GetEntity().constant.direction; }
	SDL_HapticDirection* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().constant.direction; }
	const SDL_HapticDirection* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().constant.direction; }
public:
	static SDL_HapticDirection& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticDirection&>(value).GetEntity();
	}
	static const SDL_HapticDirection& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticDirection&>(value).GetEntity();
	}
	static SDL_HapticDirection* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticDirection&>(value).GetEntityPtr();
	}
	static const SDL_HapticDirection* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticDirection&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_HapticDirection::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticDirection::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
