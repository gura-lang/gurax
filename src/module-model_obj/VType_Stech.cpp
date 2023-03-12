//==============================================================================
// VType_Stech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Stech, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Stech, `en)}

${help.ComposeMethodHelp(model.obj.Stech, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Stech() {block?}
Gurax_DeclareConstructor(Stech)
{
	Declare(VTYPE_Stech, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Stech` instance.
)""");
}

Gurax_ImplementConstructor(Stech)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Stech> pStech(new Stech());
	return argument.ReturnValue(processor, new Value_Stech(pStech.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Stech#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Stech, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Stech, MethodSkeleton)
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
// model.obj.Stech#propSkeleton
Gurax_DeclareProperty_R(Stech, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Stech, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Stech
//------------------------------------------------------------------------------
VType_Stech VTYPE_Stech("Stech");

void VType_Stech::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Stech));
	// Assignment of method
	Assign(Gurax_CreateMethod(Stech, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Stech, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Stech
//------------------------------------------------------------------------------
VType& Value_Stech::vtype = VTYPE_Stech;


String Value_Stech::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetStech().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
