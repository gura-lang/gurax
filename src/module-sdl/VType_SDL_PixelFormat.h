//==============================================================================
// VType_SDL_PixelFormat.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_PIXELFORMAT_H
#define GURAX_MODULE_SDL_VTYPE_SDL_PIXELFORMAT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_PixelFormat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_PixelFormat : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_PixelFormat VTYPE_SDL_PixelFormat;

//------------------------------------------------------------------------------
// Value_SDL_PixelFormat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_PixelFormat : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_PixelFormat);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_PixelFormat");
protected:
	SDL_PixelFormat* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_PixelFormat(VType& vtype = VTYPE_SDL_PixelFormat) : Value_Object(vtype) {}
	explicit Value_SDL_PixelFormat(SDL_PixelFormat* entity, VType& vtype = VTYPE_SDL_PixelFormat) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_PixelFormat(const Value_SDL_PixelFormat& src) = delete;
	Value_SDL_PixelFormat& operator=(const Value_SDL_PixelFormat& src) = delete;
	// Move constructor/operator
	Value_SDL_PixelFormat(Value_SDL_PixelFormat&& src) noexcept = delete;
	Value_SDL_PixelFormat& operator=(Value_SDL_PixelFormat&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_PixelFormat() = default;
public:
	SDL_PixelFormat& GetEntity() { return *_entity; }
	const SDL_PixelFormat& GetEntity() const { return *_entity; }
	SDL_PixelFormat* GetEntityPtr() { return _entity; }
	const SDL_PixelFormat* GetEntityPtr() const { return _entity; }
public:
	static SDL_PixelFormat& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_PixelFormat&>(value).GetEntity();
	}
	static const SDL_PixelFormat& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_PixelFormat&>(value).GetEntity();
	}
	static SDL_PixelFormat* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_PixelFormat&>(value).GetEntityPtr();
	}
	static const SDL_PixelFormat* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_PixelFormat&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_PixelFormat::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_PixelFormat::GetEntityPtr(value) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
