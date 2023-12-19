//==============================================================================
// VType_SDL_HapticCondition.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCONDITION_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCONDITION_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticCondition
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticCondition : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticCondition VTYPE_SDL_HapticCondition;

//------------------------------------------------------------------------------
// Value_SDL_HapticCondition
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticCondition : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticCondition);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticCondition");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticCondition(VType& vtype = VTYPE_SDL_HapticCondition) : Value_Object(vtype) {}
	explicit Value_SDL_HapticCondition(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticCondition) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticCondition(const Value_SDL_HapticCondition& src) = delete;
	Value_SDL_HapticCondition& operator=(const Value_SDL_HapticCondition& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticCondition(Value_SDL_HapticCondition&& src) noexcept = delete;
	Value_SDL_HapticCondition& operator=(Value_SDL_HapticCondition&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticCondition() = default;
public:
	SDL_HapticCondition& GetEntity() { return _pValue_HapticEffect->GetEntity().condition; }
	const SDL_HapticCondition& GetEntity() const { return _pValue_HapticEffect->GetEntity().condition; }
	SDL_HapticCondition* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().condition; }
	const SDL_HapticCondition* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().condition; }
public:
	static SDL_HapticCondition& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticCondition&>(value).GetEntity();
	}
	static const SDL_HapticCondition& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticCondition&>(value).GetEntity();
	}
	static SDL_HapticCondition* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticCondition&>(value).GetEntityPtr();
	}
	static const SDL_HapticCondition* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticCondition&>(value).GetEntityPtr();
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
			GetEntityPtr() == Value_SDL_HapticCondition::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticCondition::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
