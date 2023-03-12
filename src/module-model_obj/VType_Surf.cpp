//==============================================================================
// VType_Surf.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Surf, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Surf, `en)}

${help.ComposeMethodHelp(model.obj.Surf, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Surf() {block?}
Gurax_DeclareConstructor(Surf)
{
	Declare(VTYPE_Surf, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Surf` instance.
)""");
}

Gurax_ImplementConstructor(Surf)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Surf> pSurf(new Surf());
	return argument.ReturnValue(processor, new Value_Surf(pSurf.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Surf#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Surf, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Surf, MethodSkeleton)
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
// model.obj.Surf#propSkeleton
Gurax_DeclareProperty_R(Surf, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Surf, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Surf
//------------------------------------------------------------------------------
VType_Surf VTYPE_Surf("Surf");

void VType_Surf::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Surf));
	// Assignment of method
	Assign(Gurax_CreateMethod(Surf, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Surf, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Surf
//------------------------------------------------------------------------------
VType& Value_Surf::vtype = VTYPE_Surf;


String Value_Surf::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSurf().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
