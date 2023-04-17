//==============================================================================
// VType_Gear.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Gear, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Gear, `en)}

${help.ComposeMethodHelp(Gear, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Gear#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Gear, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Gear, MethodSkeleton)
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
// Gear#propSkeleton
Gurax_DeclareProperty_R(Gear, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Gear, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Gear
//------------------------------------------------------------------------------
VType_Gear VTYPE_Gear("Gear");

void VType_Gear::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Gear, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Gear, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Gear
//------------------------------------------------------------------------------
VType& Value_Gear::vtype = VTYPE_Gear;

String Value_Gear::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetGear().ToString(ss));
}

}
