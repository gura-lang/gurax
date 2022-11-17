//==============================================================================
// Device.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Device
//------------------------------------------------------------------------------
Device* Device::OpenDevice(size_t iDevice)
{
	RefPtr<DeviceOwner> pDeviceOwner(Device::EnumDevice());
	if (!pDeviceOwner) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device");
		return nullptr;
	}
	if (iDevice >= pDeviceOwner->size()) {
		Error::Issue(ErrorType::IndexError, "device index is out of range");
		return nullptr;
	}
	return pDeviceOwner->at(iDevice)->Reference();
}

bool Device::Open(IPortableDeviceManager* pPortableDeviceManager)
{
	if (FAILED(::CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		return Value::nil();
	}
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceFTM, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pPortableDevice)))) return false;
	do {
		CComPtr<IPortableDeviceValues> pPortableDeviceValues;
		if (FAILED(::CoCreateInstance(CLSID_PortableDeviceValues, nullptr,
				CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceValues)))) return nullptr;
		if (FAILED(pPortableDeviceValues->SetStringValue(WPD_CLIENT_NAME, L"Gurax mtp Module"))) return nullptr;
		if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_MAJOR_VERSION, GURAX_VERSION_MAJOR))) return nullptr;
		if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_MINOR_VERSION, GURAX_VERSION_MINOR))) return nullptr;
		if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_REVISION, GURAX_VERSION_PATCH))) return false;
		if (FAILED(_pPortableDevice->Open(GetDeviceID(), pPortableDeviceValues.p))) return false;
	} while (0);
	if (FAILED(_pPortableDevice->Content(&_pPortableDeviceContent))) return false;
	if (FAILED(_pPortableDeviceContent->Properties(&_pPortableDeviceProperties))) return false;
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceFriendlyName(GetDeviceID(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceFriendlyName(GetDeviceID(), wstr.get(), &len))) return false;
		_friendlyName = WSTRToString(wstr.get());
	} while (0);
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceManufacturer(GetDeviceID(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceManufacturer(GetDeviceID(), wstr.get(), &len))) return false;
		_manufacturer = WSTRToString(wstr.get());
	} while (0);
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceDescription(GetDeviceID(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceDescription(GetDeviceID(), wstr.get(), &len))) return false;
		_description = WSTRToString(wstr.get());
	} while (0);
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceKeyCollection,
			nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pPortableDeviceKeyCollection)))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_DATE_CREATED))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_DATE_MODIFIED))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_ORIGINAL_FILE_NAME))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_LANGUAGE_LOCALE))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_CONTENT_TYPE))) return false;
	if (FAILED(_pPortableDeviceKeyCollection->Add(WPD_OBJECT_SIZE))) return false;
	return true;
}

DeviceOwner* Device::EnumDevice()
{
	RefPtr<DeviceOwner> pDeviceOwner(new DeviceOwner());
	CComPtr<IPortableDeviceManager> pPortableDeviceManager;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceManager, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceManager)))) return nullptr;
	DWORD nDeviceIDs = 0;
	if (FAILED(pPortableDeviceManager->GetDevices(nullptr, &nDeviceIDs))) return nullptr;
	std::unique_ptr<LPWSTR[]> deviceIDs(new LPWSTR[nDeviceIDs]);
	if (FAILED(pPortableDeviceManager->GetDevices(deviceIDs.get(), &nDeviceIDs))) return nullptr;
	for (DWORD i = 0; i < nDeviceIDs; i++) {
		RefPtr<Device> pDevice(new Device(deviceIDs[i]));
		::CoTaskMemFree(deviceIDs[i]);
		if (!pDevice->Open(pPortableDeviceManager.p)) return nullptr;
		pDeviceOwner->push_back(pDevice.release());
	}
	return pDeviceOwner.release();
}

StorageOwner* Device::EnumStorage()
{
	CComPtr<IEnumPortableDeviceObjectIDs> pEnumPortableDeviceObjectIDs;
	CComPtr<IPortableDeviceKeyCollection> pPortableDeviceKeyCollection;
	if (FAILED(_pPortableDeviceContent->EnumObjects(
			0, WPD_DEVICE_OBJECT_ID, nullptr, &pEnumPortableDeviceObjectIDs))) return nullptr;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceKeyCollection,
			nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceKeyCollection)))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_TYPE))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_FILE_SYSTEM_TYPE))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_CAPACITY))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_FREE_SPACE_IN_BYTES))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_FREE_SPACE_IN_OBJECTS))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_DESCRIPTION))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_SERIAL_NUMBER))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_MAX_OBJECT_SIZE))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_CAPACITY_IN_OBJECTS))) return nullptr;
	if (FAILED(pPortableDeviceKeyCollection->Add(WPD_STORAGE_ACCESS_CAPABILITY))) return nullptr;
	LPWSTR objectIDs[32];
	HRESULT hr;
	RefPtr<StorageOwner> pStorageOwner(new StorageOwner());
	do {
		DWORD nObjectIDs = 0;
		hr = pEnumPortableDeviceObjectIDs->Next(Gurax_ArraySizeOf(objectIDs), objectIDs, &nObjectIDs);
		if (FAILED(hr)) return nullptr;
		for (DWORD i = 0; i < nObjectIDs; i++) {
			RefPtr<Storage> pStorage(new Storage(Reference(), objectIDs[i]));
			::CoTaskMemFree(objectIDs[i]);
			LPCWSTR objectID = pStorage->GetObjectID();
			CComPtr<IPortableDeviceValues> pPortableDeviceValues;
			if (FAILED(_pPortableDeviceProperties->GetValues(
				objectID, pPortableDeviceKeyCollection.p, &pPortableDeviceValues))) return nullptr;
			do { // WPD_STORAGE_TYPE: VT_UI4
				ULONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedIntegerValue(WPD_STORAGE_TYPE, &value))) return nullptr;
				pStorage->SetStorageType(
					(value == WPD_STORAGE_TYPE_FIXED_ROM)? Gurax_Symbol(FixedROM) :
					(value == WPD_STORAGE_TYPE_REMOVABLE_ROM)? Gurax_Symbol(RemovableROM) :
					(value == WPD_STORAGE_TYPE_FIXED_RAM)? Gurax_Symbol(FixedRAM) :
					(value ==  WPD_STORAGE_TYPE_REMOVABLE_RAM)? Gurax_Symbol(RemovableRAM) :
					Gurax_Symbol(Undefined));
			} while (0);
			do { // WPD_STORAGE_FILE_SYSTEM_TYPE: VT_LPWSTR
				LPWSTR value = nullptr;
				if (FAILED(pPortableDeviceValues->GetStringValue(WPD_STORAGE_FILE_SYSTEM_TYPE, &value))) return nullptr;
				::CoTaskMemFree(value);
			} while (0);
			do { // WPD_STORAGE_CAPACITY: VT_UI8
				ULONGLONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedLargeIntegerValue(WPD_STORAGE_CAPACITY, &value))) return nullptr;
				pStorage->SetMaxCapacity(value);
			} while (0);
			do { // WPD_STORAGE_FREE_SPACE_IN_BYTES: VT_UI8
				ULONGLONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedLargeIntegerValue(WPD_STORAGE_FREE_SPACE_IN_BYTES, &value))) return nullptr;
				pStorage->SetFreeSpaceInBytes(value);
			} while (0);
			do { // WPD_STORAGE_FREE_SPACE_IN_OBJECTS: VT_UI8
				ULONGLONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedLargeIntegerValue(WPD_STORAGE_FREE_SPACE_IN_OBJECTS, &value))) return nullptr;
				pStorage->SetFreeSpaceInObjects(value);
			} while (0);
			do { // WPD_STORAGE_DESCRIPTION: VT_LPWSTR
				LPWSTR value = nullptr;
				if (FAILED(pPortableDeviceValues->GetStringValue(WPD_STORAGE_DESCRIPTION, &value))) return nullptr;
				pStorage->SetStorageDescription(WSTRToString(value).c_str());
				::CoTaskMemFree(value);
			} while (0);
			do { // WPD_STORAGE_SERIAL_NUMBER: VT_LPWSTR
				LPWSTR value = nullptr;
				if (FAILED(pPortableDeviceValues->GetStringValue(WPD_STORAGE_SERIAL_NUMBER, &value))) return nullptr;
				pStorage->SetVolumeIdentifier(WSTRToString(value).c_str());
				::CoTaskMemFree(value);
			} while (0);
#if 0
			do { // WPD_STORAGE_MAX_OBJECT_SIZE: VT_UI8
				ULONGLONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedLargeIntegerValue(WPD_STORAGE_MAX_OBJECT_SIZE, &value))) return nullptr;
				::printf("max object size: %lld\n", value);
			} while (0);
#endif
#if 0
			do { // WPD_STORAGE_CAPACITY_IN_OBJECTS: VT_UI8
				ULONGLONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedLargeIntegerValue(WPD_STORAGE_CAPACITY_IN_OBJECTS, &value))) return nullptr;
				::printf("capacity in obj: %lld\n", value);
			} while (0);
#endif
			do { // WPD_STORAGE_ACCESS_CAPABILITY: VT_UI4
				ULONG value = 0;
				if (FAILED(pPortableDeviceValues->GetUnsignedIntegerValue(WPD_STORAGE_ACCESS_CAPABILITY, &value))) return nullptr;
				pStorage->SetAccessCapability(
					(value == WPD_STORAGE_ACCESS_CAPABILITY_READWRITE)? Gurax_Symbol(ReadWrite) :
					(value == WPD_STORAGE_ACCESS_CAPABILITY_READ_ONLY_WITHOUT_OBJECT_DELETION)? Gurax_Symbol(ReadOnly) :
					(value == WPD_STORAGE_ACCESS_CAPABILITY_READ_ONLY_WITH_OBJECT_DELETION)? Gurax_Symbol(ReadOnlyWithObjectDeletion) :
					Gurax_Symbol(Undefined));
			} while (0);
			pStorageOwner->push_back(pStorage.release());
		}
	} while (hr == S_OK);
	return pStorageOwner.release();
}

String Device::ToString(const StringStyle& ss) const
{
	return String().Format("mtp.Device:%s", GetFriendlyName());
}

//------------------------------------------------------------------------------
// DeviceList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DeviceOwner
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Iterator_Device
//------------------------------------------------------------------------------
Value* Iterator_Device::DoNextValue()
{
	const DeviceOwner& deviceOwner = GetDeviceOwner();
	if (_idx >= _idxEnd) return nullptr;
	return new Value_Device(deviceOwner[_idx++]->Reference());
}

String Iterator_Device::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("mtp.Device:begin=%zu:end=%zu:current=%zu", _idxBegin, _idxEnd, _idx);
	return str;
}

Gurax_EndModuleScope(mtp)
