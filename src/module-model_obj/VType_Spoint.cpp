//==============================================================================
// VType_Spoint.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Spoint, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Spoint, `en)}

${help.ComposeMethodHelp(model.obj.Spoint, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Spoint() {block?}
Gurax_DeclareConstructor(Spoint)
{
	Declare(VTYPE_Spoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Spoint` instance.
)""");
}

Gurax_ImplementConstructor(Spoint)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Spoint> pSpoint(new Spoint());
	return argument.ReturnValue(processor, new Value_Spoint(pSpoint.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Spoint#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Spoint, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Spoint, MethodSkeleton)
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
// model.obj.Spoint#propSkeleton
Gurax_DeclareProperty_R(Spoint, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Spoint, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Spoint
//------------------------------------------------------------------------------
VType_Spoint VTYPE_Spoint("Spoint");

void VType_Spoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Spoint));
	// Assignment of method
	Assign(Gurax_CreateMethod(Spoint, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Spoint, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Spoint
//------------------------------------------------------------------------------
VType& Value_Spoint::vtype = VTYPE_Spoint;


String Value_Spoint::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSpoint().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
