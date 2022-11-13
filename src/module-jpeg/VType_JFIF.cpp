//==============================================================================
// VType_JFIF.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(jpeg.JFIF, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.JFIF, `en)}

${help.ComposeMethodHelp(jpeg.JFIF, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.JFIF#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(JFIF, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(JFIF, MethodSkeleton)
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
// jpeg.JFIF#propSkeleton
Gurax_DeclareProperty_R(JFIF, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(JFIF, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_JFIF
//------------------------------------------------------------------------------
VType_JFIF VTYPE_JFIF("JFIF");

void VType_JFIF::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(JFIF, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(JFIF, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_JFIF
//------------------------------------------------------------------------------
VType& Value_JFIF::vtype = VTYPE_JFIF;

String Value_JFIF::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetJFIF().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
