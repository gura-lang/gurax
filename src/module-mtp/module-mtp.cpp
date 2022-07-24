//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

using StringW = std::basic_string<WCHAR>;

//------------------------------------------------------------------------------
// Device
//------------------------------------------------------------------------------
class Device : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Device);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mtp::Device");
private:
	StringW _deviceID;
	CComPtr<IPortableDevice> _pPortableDevice;
	CComPtr<IPortableDeviceContent> _pPortableDeviceContent;
	CComPtr<IPortableDeviceProperties> _pPortableDeviceProperties;
public:
	Device(LPWSTR deviceID) : _deviceID(deviceID) {}
	bool Open();
};

bool Device::Open()
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
	//if (FAILED(_pPortableDevice->Open(_deviceID.c_str(), pClientInfo.Get()))) return false;
	if (FAILED(_pPortableDevice->Content(&_pPortableDeviceContent))) return false;
	if (FAILED(_pPortableDeviceContent->Properties(&_pPortableDeviceProperties))) return false;
	return true;
}

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mtp.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	if (FAILED(::CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
		return Value::nil();
	}

	CComPtr<IPortableDeviceManager> pPortableDeviceManager;
	if (FAILED(::CoCreateInstance(CLSID_PortableDeviceManager, nullptr,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pPortableDeviceManager)))) return Value::nil();
	DWORD nDeviceIDs = 0;
	if (FAILED(pPortableDeviceManager->GetDevices(nullptr, &nDeviceIDs))) return Value::nil();
	::printf("nDeviceIDs=%d\n", nDeviceIDs);
	std::unique_ptr<LPWSTR[]> deviceIDs(new LPWSTR[nDeviceIDs]);
	if (FAILED(pPortableDeviceManager->GetDevices(deviceIDs.get(), &nDeviceIDs))) return Value::nil();
	for (DWORD i = 0; i < nDeviceIDs; i++) {
		RefPtr<Device> pDevice(new Device(deviceIDs[i]));
		if (!pDevice->Open()) return Value::nil();
	}
	return Value::nil();
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(Gurax_CreateFunction(Test));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mtp)
