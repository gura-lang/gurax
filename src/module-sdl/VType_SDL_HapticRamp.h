//==============================================================================
// VType_SDL_HapticRamp.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICRAMP_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICRAMP_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticRamp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticRamp : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticRamp VTYPE_SDL_HapticRamp;

//------------------------------------------------------------------------------
// Value_SDL_HapticRamp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticRamp : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticRamp);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticRamp");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticRamp(VType& vtype = VTYPE_SDL_HapticRamp) : Value_Object(vtype) {}
	explicit Value_SDL_HapticRamp(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticRamp) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticRamp(const Value_SDL_HapticRamp& src) = delete;
	Value_SDL_HapticRamp& operator=(const Value_SDL_HapticRamp& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticRamp(Value_SDL_HapticRamp&& src) noexcept = delete;
	Value_SDL_HapticRamp& operator=(Value_SDL_HapticRamp&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticRamp() = default;
public:
	SDL_HapticRamp& GetEntity() { return _pValue_HapticEffect->GetEntity().ramp; }
	const SDL_HapticRamp& GetEntity() const { return _pValue_HapticEffect->GetEntity().ramp; }
	SDL_HapticRamp* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().ramp; }
	const SDL_HapticRamp* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().ramp; }
public:
	static SDL_HapticRamp& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticRamp&>(value).GetEntity();
	}
	static const SDL_HapticRamp& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticRamp&>(value).GetEntity();
	}
	static SDL_HapticRamp* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticRamp&>(value).GetEntityPtr();
	}
	static const SDL_HapticRamp* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticRamp&>(value).GetEntityPtr();
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
			GetEntityPtr() == Value_SDL_HapticRamp::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticRamp::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
