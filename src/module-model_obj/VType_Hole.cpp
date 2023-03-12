//==============================================================================
// VType_Hole.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Hole, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Hole, `en)}

${help.ComposeMethodHelp(model.obj.Hole, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Hole() {block?}
Gurax_DeclareConstructor(Hole)
{
	Declare(VTYPE_Hole, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Hole` instance.
)""");
}

Gurax_ImplementConstructor(Hole)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Hole> pHole(new Hole());
	return argument.ReturnValue(processor, new Value_Hole(pHole.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Hole#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Hole, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Hole, MethodSkeleton)
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
// model.obj.Hole#propSkeleton
Gurax_DeclareProperty_R(Hole, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Hole, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Hole
//------------------------------------------------------------------------------
VType_Hole VTYPE_Hole("Hole");

void VType_Hole::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Hole));
	// Assignment of method
	Assign(Gurax_CreateMethod(Hole, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Hole, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Hole
//------------------------------------------------------------------------------
VType& Value_Hole::vtype = VTYPE_Hole;


String Value_Hole::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetHole().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
