//==============================================================================
// VType_Parm.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Parm, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Parm, `en)}

${help.ComposeMethodHelp(model.obj.Parm, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Parm() {block?}
Gurax_DeclareConstructor(Parm)
{
	Declare(VTYPE_Parm, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Parm` instance.
)""");
}

Gurax_ImplementConstructor(Parm)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Parm> pParm(new Parm());
	return argument.ReturnValue(processor, new Value_Parm(pParm.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Parm#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Parm, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Parm, MethodSkeleton)
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
// model.obj.Parm#propSkeleton
Gurax_DeclareProperty_R(Parm, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Parm, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Parm
//------------------------------------------------------------------------------
VType_Parm VTYPE_Parm("Parm");

void VType_Parm::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Parm));
	// Assignment of method
	Assign(Gurax_CreateMethod(Parm, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Parm, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Parm
//------------------------------------------------------------------------------
VType& Value_Parm::vtype = VTYPE_Parm;

String Value_Parm::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetParm().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
