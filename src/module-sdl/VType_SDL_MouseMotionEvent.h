//==============================================================================
// VType_SDL_MouseMotionEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_MouseMotionEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_MouseMotionEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_MouseMotionEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_MouseMotionEvent VTYPE_SDL_MouseMotionEvent;

//------------------------------------------------------------------------------
// Value_SDL_MouseMotionEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_MouseMotionEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_MouseMotionEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_MouseMotionEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_MouseMotionEvent(VType& vtype = VTYPE_SDL_MouseMotionEvent) : Value_Object(vtype) {}
	explicit Value_SDL_MouseMotionEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_MouseMotionEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_MouseMotionEvent(const Value_SDL_MouseMotionEvent& src) = delete;
	Value_SDL_MouseMotionEvent& operator=(const Value_SDL_MouseMotionEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_MouseMotionEvent(Value_SDL_MouseMotionEvent&& src) noexcept = delete;
	Value_SDL_MouseMotionEvent& operator=(Value_SDL_MouseMotionEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_MouseMotionEvent() = default;
public:
	SDL_MouseMotionEvent& GetEntity() { return _pValue->GetEntity().motion; }
	const SDL_MouseMotionEvent& GetEntity() const { return _pValue->GetEntity().motion; }
	SDL_MouseMotionEvent* GetEntityPtr() { return &_pValue->GetEntity().motion; }
	const SDL_MouseMotionEvent* GetEntityPtr() const { return &_pValue->GetEntity().motion; }
public:
	static SDL_MouseMotionEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_MouseMotionEvent&>(value).GetEntity();
	}
	static const SDL_MouseMotionEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseMotionEvent&>(value).GetEntity();
	}
	static SDL_MouseMotionEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_MouseMotionEvent&>(value).GetEntityPtr();
	}
	static const SDL_MouseMotionEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_MouseMotionEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_MouseMotionEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_MouseMotionEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
