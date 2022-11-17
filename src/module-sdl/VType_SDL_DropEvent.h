//==============================================================================
// VType_SDL_DropEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_DropEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_DropEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_DropEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_DropEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_DropEvent VTYPE_SDL_DropEvent;

//------------------------------------------------------------------------------
// Value_SDL_DropEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_DropEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_DropEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_DropEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_DropEvent(VType& vtype = VTYPE_SDL_DropEvent) : Value_Object(vtype) {}
	explicit Value_SDL_DropEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_DropEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_DropEvent(const Value_SDL_DropEvent& src) = delete;
	Value_SDL_DropEvent& operator=(const Value_SDL_DropEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_DropEvent(Value_SDL_DropEvent&& src) noexcept = delete;
	Value_SDL_DropEvent& operator=(Value_SDL_DropEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_DropEvent() = default;
public:
	SDL_DropEvent& GetEntity() { return _pValue->GetEntity().drop; }
	const SDL_DropEvent& GetEntity() const { return _pValue->GetEntity().drop; }
	SDL_DropEvent* GetEntityPtr() { return &_pValue->GetEntity().drop; }
	const SDL_DropEvent* GetEntityPtr() const { return &_pValue->GetEntity().drop; }
public:
	static SDL_DropEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_DropEvent&>(value).GetEntity();
	}
	static const SDL_DropEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_DropEvent&>(value).GetEntity();
	}
	static SDL_DropEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_DropEvent&>(value).GetEntityPtr();
	}
	static const SDL_DropEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_DropEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_DropEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_DropEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
