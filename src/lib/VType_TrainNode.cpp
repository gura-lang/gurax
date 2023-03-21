//==============================================================================
// VType_TrainNode.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(TrainNode, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(TrainNode, `en)}

${help.ComposeMethodHelp(TrainNode, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// TrainNode() {block?}
Gurax_DeclareConstructor(TrainNode)
{
	Declare(VTYPE_TrainNode, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `TrainNode` instance.
)""");
}

Gurax_ImplementConstructor(TrainNode)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<TrainNode> pTrainNode(new TrainNode());
	return argument.ReturnValue(processor, new Value_TrainNode(pTrainNode.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// TrainNode#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(TrainNode, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(TrainNode, MethodSkeleton)
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
// TrainNode#propSkeleton
Gurax_DeclareProperty_R(TrainNode, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(TrainNode, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_TrainNode
//------------------------------------------------------------------------------
VType_TrainNode VTYPE_TrainNode("TrainNode");

void VType_TrainNode::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(TrainNode));
	// Assignment of method
	Assign(Gurax_CreateMethod(TrainNode, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(TrainNode, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_TrainNode
//------------------------------------------------------------------------------
VType& Value_TrainNode::vtype = VTYPE_TrainNode;

String Value_TrainNode::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrainNode().ToString(ss));
}

}
