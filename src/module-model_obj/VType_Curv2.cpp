//==============================================================================
// VType_Curv2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Curv2, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Curv2, `en)}

${help.ComposeMethodHelp(model.obj.Curv2, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Curv2() {block?}
Gurax_DeclareConstructor(Curv2)
{
	Declare(VTYPE_Curv2, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Curv2` instance.
)""");
}

Gurax_ImplementConstructor(Curv2)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Curv2> pCurv2(new Curv2());
	return argument.ReturnValue(processor, new Value_Curv2(pCurv2.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Curv2#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Curv2, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Curv2, MethodSkeleton)
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
// model.obj.Curv2#propSkeleton
Gurax_DeclareProperty_R(Curv2, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Curv2, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Curv2
//------------------------------------------------------------------------------
VType_Curv2 VTYPE_Curv2("Curv2");

void VType_Curv2::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Curv2));
	// Assignment of method
	Assign(Gurax_CreateMethod(Curv2, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Curv2, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Curv2
//------------------------------------------------------------------------------
VType& Value_Curv2::vtype = VTYPE_Curv2;

String Value_Curv2::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCurv2().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
