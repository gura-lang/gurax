//==============================================================================
// VType_Conv2d.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.Conv2d, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.Conv2d, `en)}

${help.ComposeMethodHelp(ml.Conv2d, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.Conv2d() {block?}
Gurax_DeclareConstructor(Conv2d)
{
	Declare(VTYPE_Conv2d, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.Conv2d` instance.
)""");
}

Gurax_ImplementConstructor(Conv2d)
{
	// Function body
	RefPtr<Conv2d> pConv2d(new Conv2d());
	return argument.ReturnValue(processor, new Value_Conv2d(pConv2d.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.Conv2d#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Conv2d, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Conv2d, MethodSkeleton)
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
// ml.Conv2d#propSkeleton
Gurax_DeclareProperty_R(Conv2d, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Conv2d, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Conv2d
//------------------------------------------------------------------------------
VType_Conv2d VTYPE_Conv2d("Conv2d");

void VType_Conv2d::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Gear, Flag::Immutable, Gurax_CreateConstructor(Conv2d));
	// Assignment of method
	Assign(Gurax_CreateMethod(Conv2d, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Conv2d, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Conv2d
//------------------------------------------------------------------------------
VType& Value_Conv2d::vtype = VTYPE_Conv2d;

String Value_Conv2d::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetConv2d().ToString(ss));
}

Gurax_EndModuleScope(ml)
