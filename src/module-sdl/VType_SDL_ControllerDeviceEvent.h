//==============================================================================
// VType_SDL_ControllerDeviceEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_ControllerDeviceEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_ControllerDeviceEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_ControllerDeviceEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_ControllerDeviceEvent VTYPE_SDL_ControllerDeviceEvent;

//------------------------------------------------------------------------------
// Value_SDL_ControllerDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_ControllerDeviceEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_ControllerDeviceEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_ControllerDeviceEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_ControllerDeviceEvent(VType& vtype = VTYPE_SDL_ControllerDeviceEvent) : Value_Object(vtype) {}
	explicit Value_SDL_ControllerDeviceEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_ControllerDeviceEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_ControllerDeviceEvent(const Value_SDL_ControllerDeviceEvent& src) = delete;
	Value_SDL_ControllerDeviceEvent& operator=(const Value_SDL_ControllerDeviceEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_ControllerDeviceEvent(Value_SDL_ControllerDeviceEvent&& src) noexcept = delete;
	Value_SDL_ControllerDeviceEvent& operator=(Value_SDL_ControllerDeviceEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_ControllerDeviceEvent() = default;
public:
	SDL_ControllerDeviceEvent& GetEntity() { return _pValue->GetEntity().cdevice; }
	const SDL_ControllerDeviceEvent& GetEntity() const { return _pValue->GetEntity().cdevice; }
	SDL_ControllerDeviceEvent* GetEntityPtr() { return &_pValue->GetEntity().cdevice; }
	const SDL_ControllerDeviceEvent* GetEntityPtr() const { return &_pValue->GetEntity().cdevice; }
public:
	static SDL_ControllerDeviceEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_ControllerDeviceEvent&>(value).GetEntity();
	}
	static const SDL_ControllerDeviceEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerDeviceEvent&>(value).GetEntity();
	}
	static SDL_ControllerDeviceEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_ControllerDeviceEvent&>(value).GetEntityPtr();
	}
	static const SDL_ControllerDeviceEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_ControllerDeviceEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_ControllerDeviceEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_ControllerDeviceEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
