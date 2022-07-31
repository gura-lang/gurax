//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mtp.DetectDevices()
Gurax_DeclareFunction(DetectDevices)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Detects MTP devices and returns a list of `mtp.device` instances.\n");
}

Gurax_ImplementFunction(DetectDevices)
{
	// Arguments
	ArgPicker args(argument);
	// Function body
	RefPtr<DeviceOwner> pDeviceOwner(new DeviceOwner());
	if (!pDeviceOwner->Enumerate()) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device");
		return Value::nil();
	}
	return new Value_Iterator(new Iterator_Device(pDeviceOwner.release()));
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
	// Assignment of function
	Assign(Gurax_CreateFunction(DetectDevices));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mtp)
