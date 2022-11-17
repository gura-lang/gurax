//==============================================================================
// VType_Mix_Music.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_MIX_MUSIC_H
#define GURAX_MODULE_SDL_VTYPE_MIX_MUSIC_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_Mix_Music
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Mix_Music : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Mix_Music VTYPE_Mix_Music;

//------------------------------------------------------------------------------
// Value_Mix_Music
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Mix_Music : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Mix_Music);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Mix_Music");
protected:
	Mix_Music* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Mix_Music(VType& vtype = VTYPE_Mix_Music) : Value_Object(vtype) {}
	explicit Value_Mix_Music(Mix_Music* entity, VType& vtype = VTYPE_Mix_Music) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Mix_Music(const Value_Mix_Music& src) = delete;
	Value_Mix_Music& operator=(const Value_Mix_Music& src) = delete;
	// Move constructor/operator
	Value_Mix_Music(Value_Mix_Music&& src) noexcept = delete;
	Value_Mix_Music& operator=(Value_Mix_Music&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Mix_Music() = default;
public:
	Mix_Music& GetEntity() { return *_entity; }
	const Mix_Music& GetEntity() const { return *_entity; }
	Mix_Music* GetEntityPtr() { return _entity; }
	const Mix_Music* GetEntityPtr() const { return _entity; }
public:
	static Mix_Music& GetEntity(Value& value) {
		return dynamic_cast<Value_Mix_Music&>(value).GetEntity();
	}
	static const Mix_Music& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Mix_Music&>(value).GetEntity();
	}
	static Mix_Music* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Mix_Music&>(value).GetEntityPtr();
	}
	static const Mix_Music* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Mix_Music&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Mix_Music::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Mix_Music::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
