//==============================================================================
// Device.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_DEVICE_H
#define GURAX_MODULE_MTP_DEVICE_H
#include <gurax.h>
#include <PortableDevice.h>			// Windows Portable Device definitions
#include <PortableDeviceApi.h>		// Windows Portable Device API interfaces
#include <PortableDeviceTypes.h>	// Windows Portable Device Key Collection
#include <ATLComTime.h>				// COleDateTime
#include <propvarutil.h>			// InitPropVariantFromString
#include <atlbase.h>				// CComPtr
#include "Util.h"

Gurax_BeginModuleScope(mtp)

class DeviceOwner;
class StorageOwner;

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
	CComPtr<IPortableDeviceKeyCollection> _pPortableDeviceKeyCollection;
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
	static Device* OpenDevice(size_t iDevice);
public:
	bool Open(IPortableDeviceManager* pPortableDeviceManager);
	LPCWSTR GetDeviceID() const { return _deviceID.c_str(); }
	const char* GetFriendlyName() const { return _friendlyName.c_str(); }
	const char* GetManufacturer() const { return _manufacturer.c_str(); }
	const char* GetDescription() const { return _description.c_str(); }
	static DeviceOwner* EnumDevice();
	StorageOwner* EnumStorage();
public:
	IPortableDevice* GetPortableDevice() { return _pPortableDevice.p; }
	IPortableDeviceContent* GetPortableDeviceContent() { return _pPortableDeviceContent.p; }
	IPortableDeviceProperties* GetPortableDeviceProperties() { return _pPortableDeviceProperties.p; }
	IPortableDeviceKeyCollection* GetPortableDeviceKeyCollection() { return _pPortableDeviceKeyCollection.p; }
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
class DeviceOwner : public DeviceList, Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeviceOwner);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mtp.DeviceOwner");
private:
	~DeviceOwner() { Clear(); }
public:
	void Clear() {
		for (auto pDevice : *this) Device::Delete(pDevice);
		clear();
	}
};

//------------------------------------------------------------------------------
// Iterator_Device
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Device : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Device");
private:
	RefPtr<DeviceOwner> _pDeviceOwner;
	size_t _idx;
	size_t _idxBegin;
	size_t _idxEnd;
public:
	Iterator_Device(DeviceOwner* pDeviceOwner) :
		_pDeviceOwner(pDeviceOwner), _idx(0), _idxBegin(0), _idxEnd(pDeviceOwner->size()) {}
	Iterator_Device(DeviceOwner* pDeviceOwner, size_t idxBegin) :
		_pDeviceOwner(pDeviceOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(pDeviceOwner->size()) {}
	Iterator_Device(DeviceOwner* pDeviceOwner, size_t idxBegin, size_t idxEnd) :
		_pDeviceOwner(pDeviceOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(idxEnd) {}
public:
	DeviceOwner& GetDeviceOwner() { return *_pDeviceOwner; }
	const DeviceOwner& GetDeviceOwner() const { return *_pDeviceOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetDeviceOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(mtp)

#endif
