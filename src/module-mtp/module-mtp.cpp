//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mtp.Glob(pattern:string):map:flat:[stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Glob)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(stat));
	DeclareAttrOpt(Gurax_Symbol(file));
	DeclareAttrOpt(Gurax_Symbol(dir));
	DeclareAttrOpt(Gurax_Symbol(case_));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator for item names that match with a pattern supporting\n"
		"UNIX shell-style wild cards. In default, case of characters is distinguished.\n"
		"\n"
		"Though the default sensitiveness of character cases during pattern matching depends on the current platform,\n"
		"it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.\n");
}

Gurax_ImplementFunction(Glob)
{
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	if (Error::IsIssued()) return Value::nil();
	bool addSepFlag = true;
	bool statFlag = argument.IsSet(Gurax_Symbol(stat));
	bool fileFlag = argument.IsSet(Gurax_Symbol(file)) || !argument.IsSet(Gurax_Symbol(dir));
	bool dirFlag = argument.IsSet(Gurax_Symbol(dir)) || !argument.IsSet(Gurax_Symbol(file));
	bool caseFlag = PathName::CaseFlagPlatform;
	if (argument.IsSet(Gurax_Symbol(case_))) caseFlag = true;
	if (argument.IsSet(Gurax_Symbol(icase))) caseFlag = false;
	// Function body
	RefPtr<Iterator_DirectoryGlob> pIterator(
		new Iterator_DirectoryGlob(addSepFlag, statFlag, caseFlag, fileFlag, dirFlag));
	if (!pIterator->Init(pattern)) return Value::nil();
	return argument.ReturnIterator(processor, pIterator.release());
}

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
