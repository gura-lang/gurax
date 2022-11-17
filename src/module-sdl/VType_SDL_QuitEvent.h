//==============================================================================
// VType_SDL_QuitEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_QuitEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_QuitEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_QuitEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_QuitEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_QuitEvent VTYPE_SDL_QuitEvent;

//------------------------------------------------------------------------------
// Value_SDL_QuitEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_QuitEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_QuitEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_QuitEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_QuitEvent(VType& vtype = VTYPE_SDL_QuitEvent) : Value_Object(vtype) {}
	explicit Value_SDL_QuitEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_QuitEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_QuitEvent(const Value_SDL_QuitEvent& src) = delete;
	Value_SDL_QuitEvent& operator=(const Value_SDL_QuitEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_QuitEvent(Value_SDL_QuitEvent&& src) noexcept = delete;
	Value_SDL_QuitEvent& operator=(Value_SDL_QuitEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_QuitEvent() = default;
public:
	SDL_QuitEvent& GetEntity() { return _pValue->GetEntity().quit; }
	const SDL_QuitEvent& GetEntity() const { return _pValue->GetEntity().quit; }
	SDL_QuitEvent* GetEntityPtr() { return &_pValue->GetEntity().quit; }
	const SDL_QuitEvent* GetEntityPtr() const { return &_pValue->GetEntity().quit; }
public:
	static SDL_QuitEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_QuitEvent&>(value).GetEntity();
	}
	static const SDL_QuitEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_QuitEvent&>(value).GetEntity();
	}
	static SDL_QuitEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_QuitEvent&>(value).GetEntityPtr();
	}
	static const SDL_QuitEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_QuitEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_QuitEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_QuitEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
