//==============================================================================
// VType_SDL_SysWMinfo.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_SYSWMINFO_H
#define GURAX_MODULE_SDL_VTYPE_SDL_SYSWMINFO_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_SysWMinfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_SysWMinfo : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_SysWMinfo VTYPE_SDL_SysWMinfo;

//------------------------------------------------------------------------------
// Value_SDL_SysWMinfo
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_SysWMinfo : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_SysWMinfo);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_SysWMinfo");
protected:
	SDL_SysWMinfo _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_SysWMinfo(VType& vtype = VTYPE_SDL_SysWMinfo) : Value_Object(vtype) {}
	explicit Value_SDL_SysWMinfo(const SDL_SysWMinfo& entity, VType& vtype = VTYPE_SDL_SysWMinfo) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_SysWMinfo(const Value_SDL_SysWMinfo& src) = delete;
	Value_SDL_SysWMinfo& operator=(const Value_SDL_SysWMinfo& src) = delete;
	// Move constructor/operator
	Value_SDL_SysWMinfo(Value_SDL_SysWMinfo&& src) noexcept = delete;
	Value_SDL_SysWMinfo& operator=(Value_SDL_SysWMinfo&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_SysWMinfo() = default;
public:
	SDL_SysWMinfo& GetEntity() { return _entity; }
	const SDL_SysWMinfo& GetEntity() const { return _entity; }
	SDL_SysWMinfo* GetEntityPtr() { return &_entity; }
	const SDL_SysWMinfo* GetEntityPtr() const { return &_entity; }
public:
	static SDL_SysWMinfo& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_SysWMinfo&>(value).GetEntity();
	}
	static const SDL_SysWMinfo& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_SysWMinfo&>(value).GetEntity();
	}
	static SDL_SysWMinfo* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_SysWMinfo&>(value).GetEntityPtr();
	}
	static const SDL_SysWMinfo* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_SysWMinfo&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_SysWMinfo::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_SysWMinfo::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
