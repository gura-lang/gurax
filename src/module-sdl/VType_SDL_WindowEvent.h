//==============================================================================
// VType_SDL_WindowEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_WindowEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_WindowEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_WindowEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_WindowEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_WindowEvent VTYPE_SDL_WindowEvent;

//------------------------------------------------------------------------------
// Value_SDL_WindowEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_WindowEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_WindowEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_WindowEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_WindowEvent(VType& vtype = VTYPE_SDL_WindowEvent) : Value_Object(vtype) {}
	explicit Value_SDL_WindowEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_WindowEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_WindowEvent(const Value_SDL_WindowEvent& src) = delete;
	Value_SDL_WindowEvent& operator=(const Value_SDL_WindowEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_WindowEvent(Value_SDL_WindowEvent&& src) noexcept = delete;
	Value_SDL_WindowEvent& operator=(Value_SDL_WindowEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_WindowEvent() = default;
public:
	SDL_WindowEvent& GetEntity() { return _pValue->GetEntity().window; }
	const SDL_WindowEvent& GetEntity() const { return _pValue->GetEntity().window; }
	SDL_WindowEvent* GetEntityPtr() { return &_pValue->GetEntity().window; }
	const SDL_WindowEvent* GetEntityPtr() const { return &_pValue->GetEntity().window; }
public:
	static SDL_WindowEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_WindowEvent&>(value).GetEntity();
	}
	static const SDL_WindowEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_WindowEvent&>(value).GetEntity();
	}
	static SDL_WindowEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_WindowEvent&>(value).GetEntityPtr();
	}
	static const SDL_WindowEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_WindowEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_WindowEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_WindowEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
