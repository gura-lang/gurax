//==============================================================================
// VType_SDL_TextInputEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_TextInputEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_TextInputEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_TextInputEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_TextInputEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_TextInputEvent VTYPE_SDL_TextInputEvent;

//------------------------------------------------------------------------------
// Value_SDL_TextInputEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_TextInputEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_TextInputEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_TextInputEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_TextInputEvent(VType& vtype = VTYPE_SDL_TextInputEvent) : Value_Object(vtype) {}
	explicit Value_SDL_TextInputEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_TextInputEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_TextInputEvent(const Value_SDL_TextInputEvent& src) = delete;
	Value_SDL_TextInputEvent& operator=(const Value_SDL_TextInputEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_TextInputEvent(Value_SDL_TextInputEvent&& src) noexcept = delete;
	Value_SDL_TextInputEvent& operator=(Value_SDL_TextInputEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_TextInputEvent() = default;
public:
	SDL_TextInputEvent& GetEntity() { return _pValue->GetEntity().text; }
	const SDL_TextInputEvent& GetEntity() const { return _pValue->GetEntity().text; }
	SDL_TextInputEvent* GetEntityPtr() { return &_pValue->GetEntity().text; }
	const SDL_TextInputEvent* GetEntityPtr() const { return &_pValue->GetEntity().text; }
public:
	static SDL_TextInputEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_TextInputEvent&>(value).GetEntity();
	}
	static const SDL_TextInputEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_TextInputEvent&>(value).GetEntity();
	}
	static SDL_TextInputEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_TextInputEvent&>(value).GetEntityPtr();
	}
	static const SDL_TextInputEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_TextInputEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_TextInputEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_TextInputEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
