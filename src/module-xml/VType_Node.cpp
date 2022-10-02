//==============================================================================
// VType_Node.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Node#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Node, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
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
// xml.Node#type
Gurax_DeclareProperty_R(Node, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Node, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	Node::Type type = valueThis.GetNode().GetType();
	return new Value_Symbol(Node::TypeToSymbol(type));
}

//------------------------------------------------------------------------------
// VType_Node
//------------------------------------------------------------------------------
VType_Node VTYPE_Node("Node");

void VType_Node::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Node, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Node, type));
}

//------------------------------------------------------------------------------
// Value_Node
//------------------------------------------------------------------------------
VType& Value_Node::vtype = VTYPE_Node;

String Value_Node::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetNode().ToString(ss));
}

Gurax_EndModuleScope(xml)
