//==============================================================================
// VType_MergingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.MergingGroup, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.MergingGroup, `en)}

${help.ComposeMethodHelp(model.obj.MergingGroup, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.MergingGroup() {block?}
Gurax_DeclareConstructor(MergingGroup)
{
	Declare(VTYPE_MergingGroup, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.MergingGroup` instance.
)""");
}

Gurax_ImplementConstructor(MergingGroup)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<MergingGroup> pMergingGroup(new MergingGroup());
	return argument.ReturnValue(processor, new Value_MergingGroup(pMergingGroup.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.MergingGroup#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(MergingGroup, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(MergingGroup, MethodSkeleton)
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
// model.obj.MergingGroup#propSkeleton
Gurax_DeclareProperty_R(MergingGroup, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(MergingGroup, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_MergingGroup
//------------------------------------------------------------------------------
VType_MergingGroup VTYPE_MergingGroup("MergingGroup");

void VType_MergingGroup::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(MergingGroup));
	// Assignment of method
	Assign(Gurax_CreateMethod(MergingGroup, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(MergingGroup, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MergingGroup
//------------------------------------------------------------------------------
VType& Value_MergingGroup::vtype = VTYPE_MergingGroup;

String Value_MergingGroup::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMergingGroup().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
