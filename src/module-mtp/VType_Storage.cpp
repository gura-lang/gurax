//==============================================================================
// VType_Storage.cpp
//==============================================================================
#include "stdafx.h"

#undef DeletFile

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(mtp.Storage, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(mtp.Storage, `en)}

${help.ComposeMethodHelp(mtp.Storage, `en)}
)**";

// mtp.Storage(iDevice? as Number, iStorage? as Number) {block?}
Gurax_DeclareConstructor(Storage)
{
	Declare(VTYPE_Device, Flag::None);
	DeclareArg("iDevice", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareArg("iStorage", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Create an `mtp.Storage` instance.
)**");
}

Gurax_ImplementConstructor(Storage)
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.Storage#OpenDirectory(pathName as String) {block?}
Gurax_DeclareMethod(Storage, OpenDirectory)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Storage, OpenDirectory)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	RefPtr<Directory> pDirectory(valueThis.GetStorage().OpenDirectory(pathName, true));
	if (!pDirectory) {
		Error::Issue(ErrorType::PathError, "can't open directory %s", pathName);
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_Directory(pDirectory.release()));
}

// mtp.Storage#RecvFile(pathName as String, stream:w as Stream) {block?}
Gurax_DeclareMethod(Storage, RecvFile)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Storage, RecvFile)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Function> pFuncBlock(argument.CreateBlockFunction(processor.GetFrameCur(), Gurax_Symbol(block), false));
	valueThis.GetStorage().RecvFile(processor, pathName, stream, pFuncBlock.get());
	return Value::nil();
}

// mtp.Storage#DeleteFile(pathName as String)
Gurax_DeclareMethodAlias(Storage, DeleteFile_, "DeleteFile")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Storage, DeleteFile_)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	// Function body
	valueThis.GetStorage().DeleteFile(pathName);
	return Value::nil();
}

// mtp.Storage#SendFile(pathName as String, stream:r as Stream) {block?}
Gurax_DeclareMethod(Storage, SendFile)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Storage, SendFile)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Function> pFuncBlock(argument.CreateBlockFunction(processor.GetFrameCur(), Gurax_Symbol(block), false));
	valueThis.GetStorage().SendFile(processor, pathName, stream, pFuncBlock.get());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.Storage#storageType
Gurax_DeclareProperty_R(Storage, storageType)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Indicates the type of the storage by following symbols:

- `` `Undefined`` .. Undefined type.
- `` `FixedROM`` .. Non-removable and read-only.
- `` `RemovableROM`` .. Removable and read-only.
- `` `FixedRAM`` .. Non-removable and read/write capable.
- `` `RemovableRAM`` .. Removable and read/write capable.
)**");
}

Gurax_ImplementPropertyGetter(Storage, storageType)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetStorage().GetStorageType());
}

// mtp.Storage#filesystemType
Gurax_DeclareProperty_R(Storage, filesystemType)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Indicates the type of the file system by following symbols:

- `` `Undefined`` .. 
- `` `GenericFlat`` .. 
- `` `GenericHierarchical`` .. 
- `` `DCF`` .. 
)**");
}

Gurax_ImplementPropertyGetter(Storage, filesystemType)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetStorage().GetFilesystemType());
}

// mtp.Storage#accessCapability
Gurax_DeclareProperty_R(Storage, accessCapability)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Indicates what access is permitted to the storage by following symbols:

- `` `ReadWrite`` .. Read/write capable.
- `` `ReadOnly`` .. Read-only.
- `` `ReadOnlyWithObjectDeletion`` .. Read-only but deleting operation is permitted.
)**");
}

Gurax_ImplementPropertyGetter(Storage, accessCapability)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetStorage().GetAccessCapability());
}

// mtp.Storage#maxCapacity
Gurax_DeclareProperty_R(Storage, maxCapacity)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the maximum capacity of the storage in bytes.
)**");
}

Gurax_ImplementPropertyGetter(Storage, maxCapacity)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetStorage().GetMaxCapacity());
}

// mtp.Storage#freeSpaceInBytes
Gurax_DeclareProperty_R(Storage, freeSpaceInBytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the free space in the storage in bytes.
)**");
}

Gurax_ImplementPropertyGetter(Storage, freeSpaceInBytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetStorage().GetFreeSpaceInBytes());
}

// mtp.Storage#freeSpaceInObjects
Gurax_DeclareProperty_R(Storage, freeSpaceInObjects)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the free space in the storage in number of objects.
)**");
}

Gurax_ImplementPropertyGetter(Storage, freeSpaceInObjects)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetStorage().GetFreeSpaceInObjects());
}

// mtp.Storage#storageDescription
Gurax_DeclareProperty_R(Storage, storageDescription)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the storage description.
)**");
}

Gurax_ImplementPropertyGetter(Storage, storageDescription)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetStorage().GetStorageDescription());
}

// mtp.Storage#volumeIdentifier
Gurax_DeclareProperty_R(Storage, volumeIdentifier)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the volume identifier.
)**");
}

Gurax_ImplementPropertyGetter(Storage, volumeIdentifier)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetStorage().GetVolumeIdentifier());
}

//------------------------------------------------------------------------------
// VType_Storage
//------------------------------------------------------------------------------
VType_Storage VTYPE_Storage("Storage");

void VType_Storage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Storage));
	// Assignment of method
	Assign(Gurax_CreateMethod(Storage, OpenDirectory));
	Assign(Gurax_CreateMethod(Storage, RecvFile));
	Assign(Gurax_CreateMethod(Storage, DeleteFile_));
	Assign(Gurax_CreateMethod(Storage, SendFile));
	// Assignment of property
	Assign(Gurax_CreateProperty(Storage, storageType));
	Assign(Gurax_CreateProperty(Storage, filesystemType));
	Assign(Gurax_CreateProperty(Storage, accessCapability));
	Assign(Gurax_CreateProperty(Storage, maxCapacity));
	Assign(Gurax_CreateProperty(Storage, freeSpaceInBytes));
	Assign(Gurax_CreateProperty(Storage, freeSpaceInObjects));
	Assign(Gurax_CreateProperty(Storage, storageDescription));
	Assign(Gurax_CreateProperty(Storage, volumeIdentifier));
}

//------------------------------------------------------------------------------
// Value_Storage
//------------------------------------------------------------------------------
VType& Value_Storage::vtype = VTYPE_Storage;

String Value_Storage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetStorage().ToString(ss));
}

Gurax_EndModuleScope(mtp)
