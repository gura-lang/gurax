//==============================================================================
// VType_Device.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_VTYPE_DEVICE_H
#define GURAX_MODULE_MTP_VTYPE_DEVICE_H
#include <gurax.h>
#include "Device.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// VType_Device
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Device : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Device VTYPE_Device;

//------------------------------------------------------------------------------
// Value_Device
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Device : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Device);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Device");
protected:
	RefPtr<Device> _pDevice;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Device() = delete;
	explicit Value_Device(Device* pDevice, VType& vtype = VTYPE_Device) :
		Value_Object(vtype), _pDevice(pDevice) {}
	// Copy constructor/operator
	Value_Device(const Value_Device& src) :
		Value_Object(src), _pDevice(src._pDevice->Reference()) {}
	Value_Device& operator=(const Value_Device& src) = delete;
	// Move constructor/operator
	Value_Device(Value_Device&& src) noexcept = delete;
	Value_Device& operator=(Value_Device&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Device() = default;
public:
	Device& GetDevice() { return *_pDevice; }
	const Device& GetDevice() const { return *_pDevice; }
public:
	static Device& GetDevice(Value& value) {
		return dynamic_cast<Value_Device&>(value).GetDevice();
	}
	static const Device& GetDevice(const Value& value) {
		return dynamic_cast<const Value_Device&>(value).GetDevice();
	}
	static Device* GetEntityPtr(Value& value) { return &GetDevice(value); }
	static const Device* GetEntityPtr(const Value& value) { return &GetDevice(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDevice().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDevice().IsEqualTo(Value_Device::GetDevice(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDevice().IsLessThan(Value_Device::GetDevice(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mtp)

#endif
