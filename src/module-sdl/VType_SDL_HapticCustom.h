//==============================================================================
// VType_SDL_HapticCustom.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCUSTOM_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCUSTOM_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticCustom : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticCustom VTYPE_SDL_HapticCustom;

//------------------------------------------------------------------------------
// Value_SDL_HapticCustom
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticCustom : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticCustom);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticCustom");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticCustom(VType& vtype = VTYPE_SDL_HapticCustom) : Value_Object(vtype) {}
	explicit Value_SDL_HapticCustom(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticCustom) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticCustom(const Value_SDL_HapticCustom& src) = delete;
	Value_SDL_HapticCustom& operator=(const Value_SDL_HapticCustom& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticCustom(Value_SDL_HapticCustom&& src) noexcept = delete;
	Value_SDL_HapticCustom& operator=(Value_SDL_HapticCustom&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticCustom() = default;
public:
	SDL_HapticCustom& GetEntity() { return _pValue_HapticEffect->GetEntity().custom; }
	const SDL_HapticCustom& GetEntity() const { return _pValue_HapticEffect->GetEntity().custom; }
	SDL_HapticCustom* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().custom; }
	const SDL_HapticCustom* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().custom; }
public:
	static SDL_HapticCustom& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticCustom&>(value).GetEntity();
	}
	static const SDL_HapticCustom& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticCustom&>(value).GetEntity();
	}
	static SDL_HapticCustom* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticCustom&>(value).GetEntityPtr();
	}
	static const SDL_HapticCustom* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticCustom&>(value).GetEntityPtr();
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
			GetEntityPtr() == Value_SDL_HapticCustom::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticCustom::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
