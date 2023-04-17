//==============================================================================
// VType_TrainNode.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

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
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(TrainNode, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(TrainNode, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_TrainNode
//------------------------------------------------------------------------------
VType& Value_TrainNode::vtype = VTYPE_TrainNode;

String Value_TrainNode::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrainNode().ToString(ss));
}

void Value_TrainNode::GatherMemberSymbol(SymbolList& symbolList) const
{
	GetTrainNode().GatherMemberSymbol(symbolList);
	Value::GatherMemberSymbol(symbolList);
}

Value* Value_TrainNode::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	RefPtr<Value> pValueRtn(GetTrainNode().DoGetProperty(pSymbol, attr));
	if (pValueRtn) return pValueRtn.release();
	return Value::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

Gurax_EndModuleScope(ml)
