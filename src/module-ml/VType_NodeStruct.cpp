//==============================================================================
// VType_NodeStruct.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.NodeStruct, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.NodeStruct, `en)}

${help.ComposeMethodHelp(ml.NodeStruct, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.NodeStruct() {block?}
Gurax_DeclareConstructor(NodeStruct)
{
	Declare(VTYPE_NodeStruct, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.NodeStruct` instance.
)""");
}

Gurax_ImplementConstructor(NodeStruct)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<NodeStruct> pNodeStruct(new NodeStruct());
	return argument.ReturnValue(processor, new Value_NodeStruct(pNodeStruct.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.NodeStruct#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(NodeStruct, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(NodeStruct, MethodSkeleton)
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
// ml.NodeStruct#propSkeleton
Gurax_DeclareProperty_R(NodeStruct, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(NodeStruct, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_NodeStruct
//------------------------------------------------------------------------------
VType_NodeStruct VTYPE_NodeStruct("NodeStruct");

void VType_NodeStruct::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(NodeStruct));
	// Assignment of method
	Assign(Gurax_CreateMethod(NodeStruct, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(NodeStruct, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_NodeStruct
//------------------------------------------------------------------------------
VType& Value_NodeStruct::vtype = VTYPE_NodeStruct;

String Value_NodeStruct::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetNodeStruct().ToString(ss));
}

Gurax_EndModuleScope(ml)
