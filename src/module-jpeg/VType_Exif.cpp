//==============================================================================
// VType_Exif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

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
// jpeg.Exif() {block?}
Gurax_DeclareConstructor(Exif)
{
	Declare(VTYPE_Exif, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.Exif` instance.");
}

Gurax_ImplementConstructor(Exif)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Exif> pExif(new Exif());
	return argument.ReturnValue(processor, new Value_Exif(pExif.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Exif#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Exif, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Exif, MethodSkeleton)
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
// jpeg.Exif#propSkeleton
Gurax_DeclareProperty_R(Exif, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Exif, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Exif
//------------------------------------------------------------------------------
VType_Exif VTYPE_Exif("Exif");

void VType_Exif::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Exif));
	// Assignment of method
	Assign(Gurax_CreateMethod(Exif, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Exif, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Exif
//------------------------------------------------------------------------------
VType& Value_Exif::vtype = VTYPE_Exif;

Gurax_EndModuleScope(jpeg)
