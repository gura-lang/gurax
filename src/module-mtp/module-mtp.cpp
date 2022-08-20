//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mtp.EnumDevice() {block?}
Gurax_DeclareFunction(EnumDevice)
{
	Declare(VTYPE_List, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Enumerates MTP devices and returns a list of `mtp.Device` instances.\n");
}

Gurax_ImplementFunction(EnumDevice)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	RefPtr<DeviceOwner> pDeviceOwner(Device::EnumDevice());
	if (!pDeviceOwner) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device");
		return Value::nil();
	}
	return argument.ReturnIterator(processor, new Iterator_Device(pDeviceOwner.release()));
}

// mtp.OpenDevice(iDevice? as Number) {block?}
Gurax_DeclareFunction(OpenDevice)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("iDevice", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Create an `mtp.Device` instance.\n");
}

Gurax_ImplementFunction(OpenDevice)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Device> pDevice(Device::OpenDevice(iDevice));
	if (!pDevice) return Value::nil();
	return argument.ReturnValue(processor, new Value_Device(pDevice.release()));
}

// mtp.OpenStorage(iDevice? as Number, iStorage? as Number) {block?}
Gurax_DeclareFunction(OpenStorage)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("iDevice", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareArg("iStorage", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Create an `mtp.Storage` instance.\n");
}

Gurax_ImplementFunction(OpenStorage)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	size_t iStorage = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Storage> pStorage(Storage::OpenStorage(iDevice, iStorage));
	if (!pStorage) return Value::nil();
	return argument.ReturnValue(processor, new Value_Storage(pStorage.release()));
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
	// Initialize COM
	if (FAILED(::CoInitializeEx(nullptr, COINIT_MULTITHREADED))) return false;
	// Assignment of VType
	Assign(VTYPE_Device);
	Assign(VTYPE_StatEx);
	Assign(VTYPE_Storage);
	// Assignment of function
	Assign(Gurax_CreateFunction(EnumDevice));
	Assign(Gurax_CreateFunction(OpenDevice));
	Assign(Gurax_CreateFunction(OpenStorage));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mtp)
