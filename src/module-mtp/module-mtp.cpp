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
	DeviceOwner deviceOwner;
	if (!deviceOwner.Enumerate()) {
		Error::Issue(ErrorType::GuestError, "failed to open portable device");
		return Value::nil();
	}
	RefPtr<ValueOwner> pValues(new ValueOwner());
	for (Device* pDevice : deviceOwner) {
		pValues->push_back(new Value_Device(pDevice->Reference()));
	}
	return new Value_List(pValues.release(), VTYPE_Device);
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
