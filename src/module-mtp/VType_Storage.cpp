//==============================================================================
// VType_Storage.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mtp.Storage#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Storage, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Storage, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// mtp.Storage#storageType
Gurax_DeclareProperty_R(Storage, storageType)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Indicates the type of the storage by following symbols:\n"
		"\n"
		"- `` `Undefined`` .. Undefined type.\n"
		"- `` `FixedROM`` .. Non-removable and read-only.\n"
		"- `` `RemovableROM`` .. Removable and read-only.\n"
		"- `` `FixedRAM`` .. Non-removable and read/write capable.\n"
		"- `` `RemovableRAM`` .. Removable and read/write capable.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Indicates the type of the file system by following symbols:\n"
		"\n"
		"- `` `Undefined`` .. \n"
		"- `` `GenericFlat`` .. \n"
		"- `` `GenericHierarchical`` .. \n"
		"- `` `DCF`` .. \n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Indicates what access is permitted to the storage by following symbols:\n"
		"\n"
		"- `` `ReadWrite`` .. Read/write capable.\n"
		"- `` `ReadOnly`` .. Read-only.\n"
		"- `` `ReadOnlyWithObjectDeletion`` .. Read-only but deleting operation is permitted.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns the maximum capacity of the storage in bytes.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns the free space in the storage in bytes.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns the free space in the storage in number of objects.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns the storage description.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Returns the volume identifier.");
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Storage, MethodSkeleton));
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
