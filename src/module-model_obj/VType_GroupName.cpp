//==============================================================================
// VType_GroupName.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.GroupName, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.GroupName, `en)}

${help.ComposeMethodHelp(model.obj.GroupName, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.GroupName() {block?}
Gurax_DeclareConstructor(GroupName)
{
	Declare(VTYPE_GroupName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.GroupName` instance.
)""");
}

Gurax_ImplementConstructor(GroupName)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<GroupName> pGroupName(new GroupName());
	return argument.ReturnValue(processor, new Value_GroupName(pGroupName.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.GroupName#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(GroupName, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(GroupName, MethodSkeleton)
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
// model.obj.GroupName#propSkeleton
Gurax_DeclareProperty_R(GroupName, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(GroupName, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GroupName
//------------------------------------------------------------------------------
VType_GroupName VTYPE_GroupName("GroupName");

void VType_GroupName::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(GroupName));
	// Assignment of method
	Assign(Gurax_CreateMethod(GroupName, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(GroupName, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GroupName
//------------------------------------------------------------------------------
VType& Value_GroupName::vtype = VTYPE_GroupName;

String Value_GroupName::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetGroupName().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
