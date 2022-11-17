//==============================================================================
// VType_SDL_CommonEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_CommonEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_CommonEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_CommonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_CommonEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_CommonEvent VTYPE_SDL_CommonEvent;

//------------------------------------------------------------------------------
// Value_SDL_CommonEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_CommonEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_CommonEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_CommonEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_CommonEvent(VType& vtype = VTYPE_SDL_CommonEvent) : Value_Object(vtype) {}
	explicit Value_SDL_CommonEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_CommonEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_CommonEvent(const Value_SDL_CommonEvent& src) = delete;
	Value_SDL_CommonEvent& operator=(const Value_SDL_CommonEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_CommonEvent(Value_SDL_CommonEvent&& src) noexcept = delete;
	Value_SDL_CommonEvent& operator=(Value_SDL_CommonEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_CommonEvent() = default;
public:
	SDL_CommonEvent& GetEntity() { return _pValue->GetEntity().common; }
	const SDL_CommonEvent& GetEntity() const { return _pValue->GetEntity().common; }
	SDL_CommonEvent* GetEntityPtr() { return &_pValue->GetEntity().common; }
	const SDL_CommonEvent* GetEntityPtr() const { return &_pValue->GetEntity().common; }
public:
	static SDL_CommonEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_CommonEvent&>(value).GetEntity();
	}
	static const SDL_CommonEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_CommonEvent&>(value).GetEntity();
	}
	static SDL_CommonEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_CommonEvent&>(value).GetEntityPtr();
	}
	static const SDL_CommonEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_CommonEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_CommonEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_CommonEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
