//==============================================================================
// VType_SDL_UserEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_UserEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_UserEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_UserEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_UserEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_UserEvent VTYPE_SDL_UserEvent;

//------------------------------------------------------------------------------
// Value_SDL_UserEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_UserEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_UserEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_UserEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_UserEvent(VType& vtype = VTYPE_SDL_UserEvent) : Value_Object(vtype) {}
	explicit Value_SDL_UserEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_UserEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_UserEvent(const Value_SDL_UserEvent& src) = delete;
	Value_SDL_UserEvent& operator=(const Value_SDL_UserEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_UserEvent(Value_SDL_UserEvent&& src) noexcept = delete;
	Value_SDL_UserEvent& operator=(Value_SDL_UserEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_UserEvent() = default;
public:
	SDL_UserEvent& GetEntity() { return _pValue->GetEntity().user; }
	const SDL_UserEvent& GetEntity() const { return _pValue->GetEntity().user; }
	SDL_UserEvent* GetEntityPtr() { return &_pValue->GetEntity().user; }
	const SDL_UserEvent* GetEntityPtr() const { return &_pValue->GetEntity().user; }
public:
	static SDL_UserEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_UserEvent&>(value).GetEntity();
	}
	static const SDL_UserEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_UserEvent&>(value).GetEntity();
	}
	static SDL_UserEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_UserEvent&>(value).GetEntityPtr();
	}
	static const SDL_UserEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_UserEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_UserEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_UserEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
