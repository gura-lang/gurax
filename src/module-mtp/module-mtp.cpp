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
		"Enumerates MTP devices and returns a list of `mtp.device` instances.\n");
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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mtp)
