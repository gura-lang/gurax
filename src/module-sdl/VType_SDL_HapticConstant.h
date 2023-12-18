//==============================================================================
// VType_SDL_HapticConstant.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCONSTANT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_HAPTICCONSTANT_H
#include "module-sdl.h"
#include "VType_SDL_HapticEffect.h"
#include "VType_SDL_HapticDirection.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_HapticConstant
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_HapticConstant : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_HapticConstant VTYPE_SDL_HapticConstant;

//------------------------------------------------------------------------------
// Value_SDL_HapticConstant
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_HapticConstant : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_HapticConstant);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_HapticConstant");
protected:
	RefPtr<Value_SDL_HapticEffect> _pValue_HapticEffect;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_HapticConstant(VType& vtype = VTYPE_SDL_HapticConstant) : Value_Object(vtype) {}
	explicit Value_SDL_HapticConstant(Value_SDL_HapticEffect* pValue_HapticEffect, VType& vtype = VTYPE_SDL_HapticConstant) :
		Value_Object(vtype), _pValue_HapticEffect(pValue_HapticEffect) {}
	// Copy constructor/operator
	Value_SDL_HapticConstant(const Value_SDL_HapticConstant& src) = delete;
	Value_SDL_HapticConstant& operator=(const Value_SDL_HapticConstant& src) = delete;
	// Move constructor/operator
	Value_SDL_HapticConstant(Value_SDL_HapticConstant&& src) noexcept = delete;
	Value_SDL_HapticConstant& operator=(Value_SDL_HapticConstant&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_HapticConstant() = default;
public:
	SDL_HapticConstant& GetEntity() { return _pValue_HapticEffect->GetEntity().constant; }
	const SDL_HapticConstant& GetEntity() const { return _pValue_HapticEffect->GetEntity().constant; }
	SDL_HapticConstant* GetEntityPtr() { return &_pValue_HapticEffect->GetEntity().constant; }
	const SDL_HapticConstant* GetEntityPtr() const { return &_pValue_HapticEffect->GetEntity().constant; }
public:
	static SDL_HapticConstant& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_HapticConstant&>(value).GetEntity();
	}
	static const SDL_HapticConstant& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticConstant&>(value).GetEntity();
	}
	static SDL_HapticConstant* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_HapticConstant&>(value).GetEntityPtr();
	}
	static const SDL_HapticConstant* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_HapticConstant&>(value).GetEntityPtr();
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
			GetEntityPtr() == Value_SDL_HapticConstant::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_HapticConstant::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
