//==============================================================================
// Device.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_DEVICE_H
#define GURAX_MODULE_MTP_DEVICE_H
#include <gurax.h>
#include <PortableDeviceApi.h>	// Windows Portable Device API interfaces
#include <PortableDevice.h>		// Windows Portable Device definitions
#include <ATLComTime.h>			// COleDateTime
#include <propvarutil.h>		// InitPropVariantFromString
#include <atlbase.h>			// CComPtr
#include "Util.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Device
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Device : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Device);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mtp.Device");
private:
	StringW _deviceID;
	String _friendlyName;
	String _manufacturer;
	String _description;
	CComPtr<IPortableDevice> _pPortableDevice;
	CComPtr<IPortableDeviceContent> _pPortableDeviceContent;
	CComPtr<IPortableDeviceProperties> _pPortableDeviceProperties;
public:
	// Constructor
	Device(LPWSTR deviceID) : _deviceID(deviceID) {}
	// Copy constructor/operator
	Device(const Device& src) = delete;
	Device& operator=(const Device& src) = delete;
	// Move constructor/operator
	Device(Device&& src) noexcept = delete;
	Device& operator=(Device&& src) noexcept = delete;
protected:
	~Device() = default;
public:
	bool Open(IPortableDeviceManager* pPortableDeviceManager);
	const char* GetFriendlyName() const { return _friendlyName.c_str(); }
	const char* GetManufacturer() const { return _manufacturer.c_str(); }
	const char* GetDescription() const { return _description.c_str(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Device& other) const { return this == &other; }
	bool IsEqualTo(const Device& other) const { return IsIdentical(other); }
	bool IsLessThan(const Device& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DeviceList
//------------------------------------------------------------------------------
class DeviceList : public ListBase<Device*> {
};

//------------------------------------------------------------------------------
// DeviceOwner
//------------------------------------------------------------------------------
class DeviceOwner : public DeviceList {
public:
	~DeviceOwner() { Clear(); }
	void Clear() {
		for (auto pDevice : *this) Device::Delete(pDevice);
		clear();
	}
	bool Enumerate();
};

Gurax_EndModuleScope(mtp)

#endif
