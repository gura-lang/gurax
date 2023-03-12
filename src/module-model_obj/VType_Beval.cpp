//==============================================================================
// VType_Beval.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Beval, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Beval, `en)}

${help.ComposeMethodHelp(model.obj.Beval, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Beval() {block?}
Gurax_DeclareConstructor(Beval)
{
	Declare(VTYPE_Beval, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Beval` instance.
)""");
}

Gurax_ImplementConstructor(Beval)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Beval> pBeval(new Beval());
	return argument.ReturnValue(processor, new Value_Beval(pBeval.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Beval#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Beval, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Beval, MethodSkeleton)
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
// model.obj.Beval#propSkeleton
Gurax_DeclareProperty_R(Beval, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Beval, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Beval
//------------------------------------------------------------------------------
VType_Beval VTYPE_Beval("Beval");

void VType_Beval::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Beval));
	// Assignment of method
	Assign(Gurax_CreateMethod(Beval, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Beval, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Beval
//------------------------------------------------------------------------------
VType& Value_Beval::vtype = VTYPE_Beval;

String Value_Beval::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetBeval().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
