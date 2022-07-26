//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

using StringW = std::basic_string<WCHAR>;

StringW STRToStringW(LPCSTR str);
String WSTRToString(LPCWSTR wstr);

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
	String _friendlyName;
	String _manufacturer;
	String _description;
	CComPtr<IPortableDevice> _pPortableDevice;
	CComPtr<IPortableDeviceContent> _pPortableDeviceContent;
	CComPtr<IPortableDeviceProperties> _pPortableDeviceProperties;
public:
	Device(LPWSTR deviceID) : _deviceID(deviceID) {}
	bool Open(IPortableDeviceManager* pPortableDeviceManager);
	const char* GetFriendlyName() const { return _friendlyName.c_str(); }
	const char* GetManufacturer() const { return _manufacturer.c_str(); }
	const char* GetDescription() const { return _description.c_str(); }
};

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

class DeviceList : public ListBase<Device*> {
};

class DeviceOwner : public DeviceList {
public:
	~DeviceOwner() { Clear(); }
	void Clear() {
		for (auto pDevice : *this) Device::Delete(pDevice);
		clear();
	}
	bool Enumerate();
};

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
	DeviceOwner deviceOwner;
	if (!deviceOwner.Enumerate()) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device");
		return Value::nil();
	}
	for (Device* pDevice : deviceOwner) {
		::printf("FriendlyName: %s\n", pDevice->GetFriendlyName());
		::printf("Manufacturer: %s\n", pDevice->GetManufacturer());
		::printf("Description: %s\n", pDevice->GetDescription());
	}
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------
StringW STRToStringW(LPCSTR str)
{
	// cnt includes null-terminater
	int cnt = ::MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	std::unique_ptr<WCHAR[]> wstr(new WCHAR [cnt + 1]);
	::MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr.get(), cnt);
	wstr[cnt] = '\0';
	return StringW(wstr.get());
}

String WSTRToString(LPCWSTR wstr)
{
	// cnt includes null-terminater
	int cnt = ::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
	std::unique_ptr<char []> str(new char [cnt + 1]);
	::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str.get(), cnt, nullptr, nullptr);
	str[cnt] = '\0';
	return String(str.get());
}

//********************
String HRESULTToString(HRESULT hr)
{
	String rtn;
	PVOID wstr;
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPTSTR>(&wstr), 0, nullptr);
	//::wprintf(L"[%S]\n", reinterpret_cast<LPWSTR>(wstr));
	if (wstr != nullptr) rtn = WSTRToString(reinterpret_cast<LPWSTR>(wstr));
	::LocalFree(wstr);
	return rtn;
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
