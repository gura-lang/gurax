//==============================================================================
// VType_SDL_JoyDeviceEvent.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_JoyDeviceEvent_H
#define GURAX_MODULE_SDL_VTYPE_SDL_JoyDeviceEvent_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_JoyDeviceEvent : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_JoyDeviceEvent VTYPE_SDL_JoyDeviceEvent;

//------------------------------------------------------------------------------
// Value_SDL_JoyDeviceEvent
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_JoyDeviceEvent : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_JoyDeviceEvent);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_JoyDeviceEvent");
protected:
	RefPtr<Value_SDL_Event> _pValue;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_JoyDeviceEvent(VType& vtype = VTYPE_SDL_JoyDeviceEvent) : Value_Object(vtype) {}
	explicit Value_SDL_JoyDeviceEvent(Value_SDL_Event* pValue, VType& vtype = VTYPE_SDL_JoyDeviceEvent) :
		Value_Object(vtype), _pValue(pValue) {}
	// Copy constructor/operator
	Value_SDL_JoyDeviceEvent(const Value_SDL_JoyDeviceEvent& src) = delete;
	Value_SDL_JoyDeviceEvent& operator=(const Value_SDL_JoyDeviceEvent& src) = delete;
	// Move constructor/operator
	Value_SDL_JoyDeviceEvent(Value_SDL_JoyDeviceEvent&& src) noexcept = delete;
	Value_SDL_JoyDeviceEvent& operator=(Value_SDL_JoyDeviceEvent&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_JoyDeviceEvent() = default;
public:
	SDL_JoyDeviceEvent& GetEntity() { return _pValue->GetEntity().jdevice; }
	const SDL_JoyDeviceEvent& GetEntity() const { return _pValue->GetEntity().jdevice; }
	SDL_JoyDeviceEvent* GetEntityPtr() { return &_pValue->GetEntity().jdevice; }
	const SDL_JoyDeviceEvent* GetEntityPtr() const { return &_pValue->GetEntity().jdevice; }
public:
	static SDL_JoyDeviceEvent& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_JoyDeviceEvent&>(value).GetEntity();
	}
	static const SDL_JoyDeviceEvent& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyDeviceEvent&>(value).GetEntity();
	}
	static SDL_JoyDeviceEvent* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_JoyDeviceEvent&>(value).GetEntityPtr();
	}
	static const SDL_JoyDeviceEvent* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_JoyDeviceEvent&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_JoyDeviceEvent::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_JoyDeviceEvent::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
