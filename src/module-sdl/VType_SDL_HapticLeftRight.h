//==============================================================================
// VType_SDL_HapticLeftRight.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICLEFTRIGHT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICLEFTRIGHT_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticLeftRight
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticLeftRight : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticLeftRight VTYPE_SDL_HapticLeftRight;

//------------------------------------------------------------------------------
// Value_SDL_HapticLeftRight
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticLeftRight : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticLeftRight);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticLeftRight");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticLeftRight(VType& vtype = VTYPE_SDL_HapticLeftRight) : Value_Object(vtype) {}
	explicit Value_SDL_HapticLeftRight(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticLeftRight) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticLeftRight(const Value_SDL_HapticLeftRight& src) = delete;
	Value_SDL_HapticLeftRight& operator=(const Value_SDL_HapticLeftRight& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticLeftRight(Value_SDL_HapticLeftRight&& src) noexcept = delete;
	Value_SDL_HapticLeftRight& operator=(Value_SDL_HapticLeftRight&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticLeftRight() = default;
public:
	SDL_HapticLeftRight& GetEntity() { return _pValue_HapticEffect->GetEntity().leftright; }
	const SDL_HapticLeftRight& GetEntity() const { return _pValue_HapticEffect->GetEntity().leftright; }
	SDL_HapticLeftRight* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().leftright; }
	const SDL_HapticLeftRight* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().leftright; }
public:
	static SDL_HapticLeftRight& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticLeftRight&>(value).GetEntity();
	}
	static const SDL_HapticLeftRight& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticLeftRight&>(value).GetEntity();
	}
	static SDL_HapticLeftRight* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticLeftRight&>(value).GetEntityPtr();
	}
	static const SDL_HapticLeftRight* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticLeftRight&>(value).GetEntityPtr();
	}
public:
	const Value_SDL_HapticEffect& GetValue_HapticEffect() const { return *_pValue_HapticEffect; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_HapticLeftRight::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticLeftRight::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
