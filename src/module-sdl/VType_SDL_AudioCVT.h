//==============================================================================
// VType_SDL_AudioCVT.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_AUDIOCVT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_AUDIOCVT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_AudioCVT
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_AudioCVT : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_AudioCVT VTYPE_SDL_AudioCVT;

//------------------------------------------------------------------------------
// Value_SDL_AudioCVT
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_AudioCVT : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_AudioCVT);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_AudioCVT");
protected:
	SDL_AudioCVT _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_AudioCVT(VType& vtype = VTYPE_SDL_AudioCVT) : Value_Object(vtype) {}
	explicit Value_SDL_AudioCVT(const SDL_AudioCVT& entity, VType& vtype = VTYPE_SDL_AudioCVT) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_AudioCVT(const Value_SDL_AudioCVT& src) = delete;
	Value_SDL_AudioCVT& operator=(const Value_SDL_AudioCVT& src) = delete;
	// Move constructor/operator
	Value_SDL_AudioCVT(Value_SDL_AudioCVT&& src) noexcept = delete;
	Value_SDL_AudioCVT& operator=(Value_SDL_AudioCVT&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_AudioCVT() = default;
public:
	SDL_AudioCVT& GetEntity() { return _entity; }
	const SDL_AudioCVT& GetEntity() const { return _entity; }
	SDL_AudioCVT* GetEntityPtr() { return &_entity; }
	const SDL_AudioCVT* GetEntityPtr() const { return &_entity; }
public:
	static SDL_AudioCVT& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_AudioCVT&>(value).GetEntity();
	}
	static const SDL_AudioCVT& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioCVT&>(value).GetEntity();
	}
	static SDL_AudioCVT* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_AudioCVT&>(value).GetEntityPtr();
	}
	static const SDL_AudioCVT* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioCVT&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_AudioCVT::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_AudioCVT::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
