//==============================================================================
// VType_SDL_RendererInfo.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_RENDERERINFO_H
#define GURAX_MODULE_SDL_VTYPE_SDL_RENDERERINFO_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_RendererInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_RendererInfo : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_RendererInfo VTYPE_SDL_RendererInfo;

//------------------------------------------------------------------------------
// Value_SDL_RendererInfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_RendererInfo : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_RendererInfo);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_RendererInfo");
protected:
	SDL_RendererInfo _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_RendererInfo(VType& vtype = VTYPE_SDL_RendererInfo) : Value_Object(vtype) {}
	explicit Value_SDL_RendererInfo(const SDL_RendererInfo& entity, VType& vtype = VTYPE_SDL_RendererInfo) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_RendererInfo(const Value_SDL_RendererInfo& src) = delete;
	Value_SDL_RendererInfo& operator=(const Value_SDL_RendererInfo& src) = delete;
	// Move constructor/operator
	Value_SDL_RendererInfo(Value_SDL_RendererInfo&& src) noexcept = delete;
	Value_SDL_RendererInfo& operator=(Value_SDL_RendererInfo&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_RendererInfo() = default;
public:
	SDL_RendererInfo& GetEntity() { return _entity; }
	const SDL_RendererInfo& GetEntity() const { return _entity; }
	SDL_RendererInfo* GetEntityPtr() { return &_entity; }
	const SDL_RendererInfo* GetEntityPtr() const { return &_entity; }
public:
	static SDL_RendererInfo& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_RendererInfo&>(value).GetEntity();
	}
	static const SDL_RendererInfo& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_RendererInfo&>(value).GetEntity();
	}
	static SDL_RendererInfo* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_RendererInfo&>(value).GetEntityPtr();
	}
	static const SDL_RendererInfo* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_RendererInfo&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_RendererInfo::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_RendererInfo::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
