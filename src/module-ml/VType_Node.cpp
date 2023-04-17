//==============================================================================
// VType_Node.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Node, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Node, `en)}

${help.ComposeMethodHelp(Node, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Node#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Node, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Node, MethodSkeleton)
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
// Node#propSkeleton
Gurax_DeclareProperty_R(Node, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Node, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Node
//------------------------------------------------------------------------------
VType_Node VTYPE_Node("Node");

void VType_Node::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Node, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Node, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Node
//------------------------------------------------------------------------------
VType& Value_Node::vtype = VTYPE_Node;

String Value_Node::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetNode().ToString(ss));
}

void Value_Node::GatherMemberSymbol(SymbolList& symbolList) const
{
	GetNode().GatherMemberSymbol(symbolList);
	Value::GatherMemberSymbol(symbolList);
}

Value* Value_Node::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	RefPtr<Value> pValueRtn(GetNode().DoGetProperty(pSymbol, attr));
	if (pValueRtn) return pValueRtn.release();
	return Value::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

Gurax_EndModuleScope(ml)
