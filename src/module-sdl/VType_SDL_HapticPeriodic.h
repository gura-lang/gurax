//==============================================================================
// VType_SDL_HapticPeriodic.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICPERIODIC_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICPERIODIC_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticPeriodic
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticPeriodic : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticPeriodic VTYPE_SDL_HapticPeriodic;

//------------------------------------------------------------------------------
// Value_SDL_HapticPeriodic
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticPeriodic : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticPeriodic);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticPeriodic");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticPeriodic(VType& vtype = VTYPE_SDL_HapticPeriodic) : Value_Object(vtype) {}
	explicit Value_SDL_HapticPeriodic(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticPeriodic) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticPeriodic(const Value_SDL_HapticPeriodic& src) = delete;
	Value_SDL_HapticPeriodic& operator=(const Value_SDL_HapticPeriodic& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticPeriodic(Value_SDL_HapticPeriodic&& src) noexcept = delete;
	Value_SDL_HapticPeriodic& operator=(Value_SDL_HapticPeriodic&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticPeriodic() = default;
public:
	SDL_HapticPeriodic& GetEntity() { return _pValue_HapticEffect->GetEntity().periodic; }
	const SDL_HapticPeriodic& GetEntity() const { return _pValue_HapticEffect->GetEntity().periodic; }
	SDL_HapticPeriodic* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().periodic; }
	const SDL_HapticPeriodic* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().periodic; }
public:
	static SDL_HapticPeriodic& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticPeriodic&>(value).GetEntity();
	}
	static const SDL_HapticPeriodic& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticPeriodic&>(value).GetEntity();
	}
	static SDL_HapticPeriodic* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticPeriodic&>(value).GetEntityPtr();
	}
	static const SDL_HapticPeriodic* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticPeriodic&>(value).GetEntityPtr();
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
			GetEntityPtr() == Value_SDL_HapticPeriodic::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticPeriodic::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
