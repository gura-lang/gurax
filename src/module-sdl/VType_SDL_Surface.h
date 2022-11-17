//==============================================================================
// VType_SDL_Surface.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_SURFACE_H
#define GURAX_MODULE_SDL_VTYPE_SDL_SURFACE_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Surface
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Surface : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_SDL_Surface VTYPE_SDL_Surface;

//------------------------------------------------------------------------------
// Value_SDL_Surface
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Surface : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Surface);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Surface");
protected:
	SDL_Surface* _entity;
	RefPtr<Image> _pImage;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Surface(VType& vtype = VTYPE_SDL_Surface) : Value_Object(vtype) {}
	explicit Value_SDL_Surface(SDL_Surface* entity, VType& vtype = VTYPE_SDL_Surface) :
		Value_Object(vtype), _entity(entity) {}
	explicit Value_SDL_Surface(SDL_Surface* entity, Image* pImage, VType& vtype = VTYPE_SDL_Surface) :
		Value_Object(vtype), _entity(entity), _pImage(pImage) {}
	// Copy constructor/operator
	Value_SDL_Surface(const Value_SDL_Surface& src) = delete;
	Value_SDL_Surface& operator=(const Value_SDL_Surface& src) = delete;
	// Move constructor/operator
	Value_SDL_Surface(Value_SDL_Surface&& src) noexcept = delete;
	Value_SDL_Surface& operator=(Value_SDL_Surface&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Surface() = default;
public:
	static Value_SDL_Surface* Create(Image* pImage);
public:
	SDL_Surface& GetEntity() { return *_entity; }
	const SDL_Surface& GetEntity() const { return *_entity; }
	SDL_Surface* GetEntityPtr() { return _entity; }
	const SDL_Surface* GetEntityPtr() const { return _entity; }
	Image* GetImage() { return _pImage.get(); }
	const Image* GetImage() const { return _pImage.get(); }
public:
	static SDL_Surface& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Surface&>(value).GetEntity();
	}
	static const SDL_Surface& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Surface&>(value).GetEntity();
	}
	static SDL_Surface* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Surface&>(value).GetEntityPtr();
	}
	static const SDL_Surface* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Surface&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Surface::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Surface::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
