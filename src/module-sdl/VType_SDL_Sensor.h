//==============================================================================
// VType_SDL_Sensor.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_SENSOR_H
#define GURAX_MODULE_SDL_VTYPE_SDL_SENSOR_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_Sensor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_Sensor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_Sensor VTYPE_SDL_Sensor;

//------------------------------------------------------------------------------
// Value_SDL_Sensor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_Sensor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_Sensor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_Sensor");
protected:
	SDL_Sensor* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_Sensor(VType& vtype = VTYPE_SDL_Sensor) : Value_Object(vtype) {}
	explicit Value_SDL_Sensor(SDL_Sensor* entity, VType& vtype = VTYPE_SDL_Sensor) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_SDL_Sensor(const Value_SDL_Sensor& src) = delete;
	Value_SDL_Sensor& operator=(const Value_SDL_Sensor& src) = delete;
	// Move constructor/operator
	Value_SDL_Sensor(Value_SDL_Sensor&& src) noexcept = delete;
	Value_SDL_Sensor& operator=(Value_SDL_Sensor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_Sensor() = default;
public:
	SDL_Sensor& GetEntity() { return *_entity; }
	const SDL_Sensor& GetEntity() const { return *_entity; }
	SDL_Sensor* GetEntityPtr() { return _entity; }
	const SDL_Sensor* GetEntityPtr() const { return _entity; }
public:
	static SDL_Sensor& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_Sensor&>(value).GetEntity();
	}
	static const SDL_Sensor& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_Sensor&>(value).GetEntity();
	}
	static SDL_Sensor* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_Sensor&>(value).GetEntityPtr();
	}
	static const SDL_Sensor* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_Sensor&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_Sensor::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_Sensor::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
