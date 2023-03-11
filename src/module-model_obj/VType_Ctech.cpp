//==============================================================================
// VType_Ctech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Ctech, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Ctech, `en)}

${help.ComposeMethodHelp(model.obj.Ctech, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Ctech() {block?}
Gurax_DeclareConstructor(Ctech)
{
	Declare(VTYPE_Ctech, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Ctech` instance.
)""");
}

Gurax_ImplementConstructor(Ctech)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Ctech> pCtech(new Ctech());
	return argument.ReturnValue(processor, new Value_Ctech(pCtech.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Ctech#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Ctech, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Ctech, MethodSkeleton)
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
// model.obj.Ctech#propSkeleton
Gurax_DeclareProperty_R(Ctech, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Ctech, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Ctech
//------------------------------------------------------------------------------
VType_Ctech VTYPE_Ctech("Ctech");

void VType_Ctech::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Ctech));
	// Assignment of method
	Assign(Gurax_CreateMethod(Ctech, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Ctech, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Ctech
//------------------------------------------------------------------------------
VType& Value_Ctech::vtype = VTYPE_Ctech;

String Value_Ctech::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCtech().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
