//==============================================================================
// VType_Step.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Step, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Step, `en)}

${help.ComposeMethodHelp(model.obj.Step, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Step() {block?}
Gurax_DeclareConstructor(Step)
{
	Declare(VTYPE_Step, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Step` instance.
)""");
}

Gurax_ImplementConstructor(Step)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Step> pStep(new Step());
	return argument.ReturnValue(processor, new Value_Step(pStep.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Step#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Step, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Step, MethodSkeleton)
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
// model.obj.Step#propSkeleton
Gurax_DeclareProperty_R(Step, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Step, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Step
//------------------------------------------------------------------------------
VType_Step VTYPE_Step("Step");

void VType_Step::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Step));
	// Assignment of method
	Assign(Gurax_CreateMethod(Step, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Step, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Step
//------------------------------------------------------------------------------
VType& Value_Step::vtype = VTYPE_Step;

String Value_Step::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetStep().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
