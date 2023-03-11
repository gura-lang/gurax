//==============================================================================
// VType_SmoothingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.SmoothingGroup, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.SmoothingGroup, `en)}

${help.ComposeMethodHelp(model.obj.SmoothingGroup, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.SmoothingGroup() {block?}
Gurax_DeclareConstructor(SmoothingGroup)
{
	Declare(VTYPE_SmoothingGroup, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.SmoothingGroup` instance.
)""");
}

Gurax_ImplementConstructor(SmoothingGroup)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<SmoothingGroup> pSmoothingGroup(new SmoothingGroup());
	return argument.ReturnValue(processor, new Value_SmoothingGroup(pSmoothingGroup.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.SmoothingGroup#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(SmoothingGroup, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(SmoothingGroup, MethodSkeleton)
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
// model.obj.SmoothingGroup#propSkeleton
Gurax_DeclareProperty_R(SmoothingGroup, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(SmoothingGroup, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SmoothingGroup
//------------------------------------------------------------------------------
VType_SmoothingGroup VTYPE_SmoothingGroup("SmoothingGroup");

void VType_SmoothingGroup::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(SmoothingGroup));
	// Assignment of method
	Assign(Gurax_CreateMethod(SmoothingGroup, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SmoothingGroup, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SmoothingGroup
//------------------------------------------------------------------------------
VType& Value_SmoothingGroup::vtype = VTYPE_SmoothingGroup;

String Value_SmoothingGroup::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetSmoothingGroup().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
