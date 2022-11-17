//==============================================================================
// VType_SDL_SysWMEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_SysWMEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_SysWMEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_SysWMEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_SysWMEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_SysWMEvent VTYPE_SDL_SysWMEvent;

//------------------------------------------------------------------------------
// Value_SDL_SysWMEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_SysWMEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_SysWMEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_SysWMEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_SysWMEvent(VType& vtype = VTYPE_SDL_SysWMEvent) : Value_Object(vtype) {}
	explicit Value_SDL_SysWMEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_SysWMEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_SysWMEvent(const Value_SDL_SysWMEvent& src) = delete;
	Value_SDL_SysWMEvent& operator=(const Value_SDL_SysWMEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_SysWMEvent(Value_SDL_SysWMEvent&& src) noexcept = delete;
	Value_SDL_SysWMEvent& operator=(Value_SDL_SysWMEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_SysWMEvent() = default;
public:
	SDL_SysWMEvent& GetEntity() { return _pValue->GetEntity().syswm; }
	const SDL_SysWMEvent& GetEntity() const { return _pValue->GetEntity().syswm; }
	SDL_SysWMEvent* GetEntityPtr() { return &_pValue->GetEntity().syswm; }
	const SDL_SysWMEvent* GetEntityPtr() const { return &_pValue->GetEntity().syswm; }
public:
	static SDL_SysWMEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_SysWMEvent&>(value).GetEntity();
	}
	static const SDL_SysWMEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_SysWMEvent&>(value).GetEntity();
	}
	static SDL_SysWMEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_SysWMEvent&>(value).GetEntityPtr();
	}
	static const SDL_SysWMEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_SysWMEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_SysWMEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_SysWMEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
