//==============================================================================
// VType_SDL_AudioDeviceEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_AudioDeviceEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_AudioDeviceEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_AudioDeviceEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_AudioDeviceEvent VTYPE_SDL_AudioDeviceEvent;

//------------------------------------------------------------------------------
// Value_SDL_AudioDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_AudioDeviceEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_AudioDeviceEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_AudioDeviceEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_AudioDeviceEvent(VType& vtype = VTYPE_SDL_AudioDeviceEvent) : Value_Object(vtype) {}
	explicit Value_SDL_AudioDeviceEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_AudioDeviceEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_AudioDeviceEvent(const Value_SDL_AudioDeviceEvent& src) = delete;
	Value_SDL_AudioDeviceEvent& operator=(const Value_SDL_AudioDeviceEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_AudioDeviceEvent(Value_SDL_AudioDeviceEvent&& src) noexcept = delete;
	Value_SDL_AudioDeviceEvent& operator=(Value_SDL_AudioDeviceEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_AudioDeviceEvent() = default;
public:
	SDL_AudioDeviceEvent& GetEntity() { return _pValue->GetEntity().adevice; }
	const SDL_AudioDeviceEvent& GetEntity() const { return _pValue->GetEntity().adevice; }
	SDL_AudioDeviceEvent* GetEntityPtr() { return &_pValue->GetEntity().adevice; }
	const SDL_AudioDeviceEvent* GetEntityPtr() const { return &_pValue->GetEntity().adevice; }
public:
	static SDL_AudioDeviceEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_AudioDeviceEvent&>(value).GetEntity();
	}
	static const SDL_AudioDeviceEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioDeviceEvent&>(value).GetEntity();
	}
	static SDL_AudioDeviceEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_AudioDeviceEvent&>(value).GetEntityPtr();
	}
	static const SDL_AudioDeviceEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioDeviceEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_AudioDeviceEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_AudioDeviceEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
