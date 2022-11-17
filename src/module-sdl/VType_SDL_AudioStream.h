//==============================================================================
// VType_SDL_AudioStream.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_AUDIOSTREAM_H
#define GURAX_MODULE_SDL_VTYPE_SDL_AUDIOSTREAM_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_AudioStream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_AudioStream : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_AudioStream VTYPE_SDL_AudioStream;

//------------------------------------------------------------------------------
// Value_SDL_AudioStream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_AudioStream : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_AudioStream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_AudioStream");
protected:
	SDL_AudioStream* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_AudioStream(VType& vtype = VTYPE_SDL_AudioStream) : Value_Object(vtype) {}
	explicit Value_SDL_AudioStream(SDL_AudioStream* entity, VType& vtype = VTYPE_SDL_AudioStream) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_AudioStream(const Value_SDL_AudioStream& src) = delete;
	Value_SDL_AudioStream& operator=(const Value_SDL_AudioStream& src) = delete;
	// Move constructor/operator
	Value_SDL_AudioStream(Value_SDL_AudioStream&& src) noexcept = delete;
	Value_SDL_AudioStream& operator=(Value_SDL_AudioStream&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_AudioStream() = default;
public:
	SDL_AudioStream& GetEntity() { return *_entity; }
	const SDL_AudioStream& GetEntity() const { return *_entity; }
	SDL_AudioStream* GetEntityPtr() { return _entity; }
	const SDL_AudioStream* GetEntityPtr() const { return _entity; }
public:
	static SDL_AudioStream& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_AudioStream&>(value).GetEntity();
	}
	static const SDL_AudioStream& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioStream&>(value).GetEntity();
	}
	static SDL_AudioStream* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_AudioStream&>(value).GetEntityPtr();
	}
	static const SDL_AudioStream* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioStream&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_AudioStream::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_AudioStream::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
