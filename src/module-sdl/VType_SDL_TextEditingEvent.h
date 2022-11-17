//==============================================================================
// VType_SDL_TextEditingEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_TextEditingEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_TextEditingEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_TextEditingEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_TextEditingEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_TextEditingEvent VTYPE_SDL_TextEditingEvent;

//------------------------------------------------------------------------------
// Value_SDL_TextEditingEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_TextEditingEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_TextEditingEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_TextEditingEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_TextEditingEvent(VType& vtype = VTYPE_SDL_TextEditingEvent) : Value_Object(vtype) {}
	explicit Value_SDL_TextEditingEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_TextEditingEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_TextEditingEvent(const Value_SDL_TextEditingEvent& src) = delete;
	Value_SDL_TextEditingEvent& operator=(const Value_SDL_TextEditingEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_TextEditingEvent(Value_SDL_TextEditingEvent&& src) noexcept = delete;
	Value_SDL_TextEditingEvent& operator=(Value_SDL_TextEditingEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_TextEditingEvent() = default;
public:
	SDL_TextEditingEvent& GetEntity() { return _pValue->GetEntity().edit; }
	const SDL_TextEditingEvent& GetEntity() const { return _pValue->GetEntity().edit; }
	SDL_TextEditingEvent* GetEntityPtr() { return &_pValue->GetEntity().edit; }
	const SDL_TextEditingEvent* GetEntityPtr() const { return &_pValue->GetEntity().edit; }
public:
	static SDL_TextEditingEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_TextEditingEvent&>(value).GetEntity();
	}
	static const SDL_TextEditingEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_TextEditingEvent&>(value).GetEntity();
	}
	static SDL_TextEditingEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_TextEditingEvent&>(value).GetEntityPtr();
	}
	static const SDL_TextEditingEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_TextEditingEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_TextEditingEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_TextEditingEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
