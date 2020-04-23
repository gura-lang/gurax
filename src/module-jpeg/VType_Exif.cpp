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
// jpeg.Exif#ifd0
Gurax_DeclareProperty_R(Exif, ifd0)
{
	Declare(VTYPE_IFD, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"IFD0 field in the Exif. Returns `nil` if not exist.");
}

Gurax_ImplementPropertyGetter(Exif, ifd0)
{
	auto& valueThis = GetValueThis(valueTarget);
	const IFDOwner& ifdOwner = valueThis.GetExif().GetIFDOwner();
	if (ifdOwner.size() < 1) return Value::nil();
	return new Value_IFD(ifdOwner[0]->Reference());
}

// jpeg.Exif#ifd1
Gurax_DeclareProperty_R(Exif, ifd1)
{
	Declare(VTYPE_IFD, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"IFD1 field in the Exif. Returns `nil` if not exist.");
}

Gurax_ImplementPropertyGetter(Exif, ifd1)
{
	auto& valueThis = GetValueThis(valueTarget);
	const IFDOwner& ifdOwner = valueThis.GetExif().GetIFDOwner();
	if (ifdOwner.size() < 2) return Value::nil();
	return new Value_IFD(ifdOwner[1]->Reference());
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
	Declare(VTYPE_Segment, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Exif, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Exif, ifd0));
	Assign(Gurax_CreateProperty(Exif, ifd1));
}

//------------------------------------------------------------------------------
// Value_Exif
//------------------------------------------------------------------------------
VType& Value_Exif::vtype = VTYPE_Exif;

Gurax_EndModuleScope(jpeg)
