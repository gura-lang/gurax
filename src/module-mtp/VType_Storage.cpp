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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// mtp.Storage() {block?}
Gurax_DeclareConstructor(Storage)
{
	Declare(VTYPE_Storage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `mtp.Storage` instance.");
}

Gurax_ImplementConstructor(Storage)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Storage> pStorage(new Storage());
	return argument.ReturnValue(processor, new Value_Storage(pStorage.release()));
}

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
// mtp.Storage#propSkeleton
Gurax_DeclareProperty_R(Storage, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Storage, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Storage));
	// Assignment of method
	Assign(Gurax_CreateMethod(Storage, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Storage, propSkeleton));
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
