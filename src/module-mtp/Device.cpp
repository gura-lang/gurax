//==============================================================================
// Device.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Device
//------------------------------------------------------------------------------
bool Device::Open(IPortableDeviceManager* pPortableDeviceManager)
{
	CComPtr<IPortableDeviceValues> pPortableDeviceValues;
	if (FAILED(::CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		return Value::nil();
	}
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceValues, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceValues)))) return false;
	if (FAILED(pPortableDeviceValues->SetStringValue(WPD_CLIENT_NAME, L"Gurax mtp Module"))) return false;
	if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_MAJOR_VERSION, GURAX_VERSION_MAJOR))) return false;
	if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_MINOR_VERSION, GURAX_VERSION_MINOR))) return false;
	if (FAILED(pPortableDeviceValues->SetUnsignedIntegerValue(WPD_CLIENT_REVISION, GURAX_VERSION_PATCH))) return false;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceFTM, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pPortableDevice)))) return false;
	if (FAILED(_pPortableDevice->Open(_deviceID.c_str(), pPortableDeviceValues.p))) return false;
	if (FAILED(_pPortableDevice->Content(&_pPortableDeviceContent))) return false;
	if (FAILED(_pPortableDeviceContent->Properties(&_pPortableDeviceProperties))) return false;
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceFriendlyName(_deviceID.c_str(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceFriendlyName(_deviceID.c_str(), wstr.get(), &len))) return false;
		_friendlyName = WSTRToString(wstr.get());
	} while (0);
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceManufacturer(_deviceID.c_str(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceManufacturer(_deviceID.c_str(), wstr.get(), &len))) return false;
		_manufacturer = WSTRToString(wstr.get());
	} while (0);
	do {
		DWORD len = 0;
		if (FAILED(pPortableDeviceManager->GetDeviceDescription(_deviceID.c_str(), nullptr, &len))) return false;
		std::unique_ptr<WCHAR[]> wstr(new WCHAR[len]);	// len contains terminal null.
		if (FAILED(pPortableDeviceManager->GetDeviceDescription(_deviceID.c_str(), wstr.get(), &len))) return false;
		_description = WSTRToString(wstr.get());
	} while (0);
	return true;
}

String Device::ToString(const StringStyle& ss) const
{
	return String().Format("mtp.Device");
}

//------------------------------------------------------------------------------
// DeviceList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DeviceOwner
//------------------------------------------------------------------------------
bool DeviceOwner::Enumerate()
{
	CComPtr<IPortableDeviceManager> pPortableDeviceManager;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceManager, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceManager)))) return false;
	DWORD nDeviceIDs = 0;
	if (FAILED(pPortableDeviceManager->GetDevices(nullptr, &nDeviceIDs))) return false;
	std::unique_ptr<LPWSTR[]> deviceIDs(new LPWSTR[nDeviceIDs]);
	if (FAILED(pPortableDeviceManager->GetDevices(deviceIDs.get(), &nDeviceIDs))) return false;
	for (DWORD i = 0; i < nDeviceIDs; i++) {
		RefPtr<Device> pDevice(new Device(deviceIDs[i]));
		::CoTaskMemFree(deviceIDs[i]);
		if (!pDevice->Open(pPortableDeviceManager.p)) return false;
		push_back(pDevice.release());
	}
	return true;
}

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
	str.Format("Device:begin=%zu:end=%zu", _idxBegin, _idxEnd);
	return str;
}

Gurax_EndModuleScope(mtp)
