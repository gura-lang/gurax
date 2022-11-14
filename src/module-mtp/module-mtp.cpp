//==============================================================================
// module-mtp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(mtp)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// mtp.Dir(iDevice as Number, iStorage as Number, dirName? as String, pattern* as String):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Dir)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("iDevice", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("iStorage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dirName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that lists item names in the specified directory.
If pathname is omitted, the current directory shall be listed.

Though the default sensitiveness of character cases during pattern matching depends on the target directory,
it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.
)**");
}

Gurax_ImplementFunction(Dir)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.PickNumberNonNeg<size_t>();
	size_t iStorage = args.PickNumberNonNeg<size_t>();
	const char* dirName = args.IsValid()? args.PickString() : "";
	int depthMax = 0;
	StringList patterns = args.PickStringList();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Storage> pStorage(Storage::OpenStorage(iDevice, iStorage));
	if (!pStorage) return Value::nil();
	RefPtr<Directory> pDirectory(pStorage->OpenDirectory(dirName, true));
	if (!pDirectory) return Value::nil();
	Directory::WalkFlags walkFlags = Directory::WalkFlag::CheckArgument(argument, true, pDirectory->GetCaseFlag());
	RefPtr<Iterator> pIterator(new Iterator_DirectoryWalk(pDirectory.release(), depthMax, patterns, walkFlags));
	return argument.ReturnIterator(processor, pIterator.release());
}

// mtp.Glob(iDevice as Number, iStorage as Number, pattern as String):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Glob)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("iDevice", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("iStorage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator for item names that match with a pattern supporting
UNIX shell-style wild cards. In default, case of characters is distinguished.

Though the default sensitiveness of character cases during pattern matching depends on the current platform,
it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.
)**");
}

Gurax_ImplementFunction(Glob)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.PickNumberNonNeg<size_t>();
	size_t iStorage = args.PickNumberNonNeg<size_t>();
	const char* pattern = args.PickString();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Storage> pStorage(Storage::OpenStorage(iDevice, iStorage));
	if (!pStorage) return Value::nil();
	RefPtr<Iterator_DirectoryGlob> pIterator(new Iterator_DirectoryGlobEx(pStorage.release()));
	if (!pIterator->Initialize(pattern)) return Value::nil();
	pIterator->SetWalkFlags(Directory::WalkFlag::CheckArgument(argument, true, pIterator->GetDirectoryCur().GetCaseFlag()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// mtp.EnumDevice() {block?}
Gurax_DeclareFunction(EnumDevice)
{
	Declare(VTYPE_List, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Enumerates MTP devices and returns a list of `mtp.Device` instances.
)**");
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

// mtp.Walk(iDevice as Number, iStorage as Number, dirName? as String, depthMax? as Number, pattern* as String):map:flat:[addSep,elimSep,stat,file,dir,case,icase] {block?}
Gurax_DeclareFunction(Walk)
{
	Declare(VTYPE_Any, Flag::Map | Flag::Flat);
	DeclareArg("iDevice", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("iStorage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dirName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("depthMax", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pattern", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	Directory::WalkFlag::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that recursively lists item names under the specified directory.
If `directory` is omitted, search starts at the current directory.

Though the default sensitiveness of character cases during pattern matching depends on the target directory,
it can be changed by attributes `:case` for case-sensitive and `:icase` for case-insensitive.
)**");
}

Gurax_ImplementFunction(Walk)
{
	// Arguments
	ArgPicker args(argument);
	size_t iDevice = args.PickNumberNonNeg<size_t>();
	size_t iStorage = args.PickNumberNonNeg<size_t>();
	const char* dirName = args.IsValid()? args.PickString() : "";
	int depthMax = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	StringList patterns = args.PickStringList();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Storage> pStorage(Storage::OpenStorage(iDevice, iStorage));
	if (!pStorage) return Value::nil();
	RefPtr<Directory> pDirectory(pStorage->OpenDirectory(dirName, true));
	if (!pDirectory) return Value::nil();
	Directory::WalkFlags walkFlags = Directory::WalkFlag::CheckArgument(argument, true, pDirectory->GetCaseFlag());
	RefPtr<Iterator> pIterator(new Iterator_DirectoryWalk(pDirectory.release(), depthMax, patterns, walkFlags));
	return argument.ReturnIterator(processor, pIterator.release());
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
	Assign(Gurax_CreateFunction(Dir));
	Assign(Gurax_CreateFunction(EnumDevice));
	Assign(Gurax_CreateFunction(Glob));
	Assign(Gurax_CreateFunction(Walk));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(mtp)
