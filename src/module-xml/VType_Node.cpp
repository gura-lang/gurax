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

${help.ComposePropertyHelp(xml.Node, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Node, `en)}

${help.ComposeMethodHelp(xml.Node, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Node#Compose(stream? as Stream)
Gurax_DeclareMethod(Node, Compose)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Node, Compose)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : Stream::COut.get();
	// Function body
	valueThis.GetNode().Compose(*pStream);
	return Value::nil();
}

// xml.Node#IsCData()
Gurax_DeclareMethod(Node, IsCData)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Node, IsCData)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetNode().GetType() == Node::Type::CData);
}

// xml.Node#IsComment()
Gurax_DeclareMethod(Node, IsComment)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Node, IsComment)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetNode().GetType() == Node::Type::Comment);
}

// xml.Node#IsElement()
Gurax_DeclareMethod(Node, IsElement)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Node, IsElement)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetNode().GetType() == Node::Type::Element);
}

// xml.Node#IsText()
Gurax_DeclareMethod(Node, IsText)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Node, IsText)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetNode().GetType() == Node::Type::Text);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Node#depth
Gurax_DeclareProperty_R(Node, depth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Node, depth)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetNode().GetDepth());
}

// xml.Node#parent
Gurax_DeclareProperty_R(Node, parent)
{
	Declare(VTYPE_Node, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Node, parent)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Node> pNodeParent(valueThis.GetNode().LockNodeParent());
	return pNodeParent? pNodeParent->CreateValue() : Value::nil();
}

// xml.Node#type
Gurax_DeclareProperty_R(Node, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Node, Compose));
	Assign(Gurax_CreateMethod(Node, IsCData));
	Assign(Gurax_CreateMethod(Node, IsComment));
	Assign(Gurax_CreateMethod(Node, IsElement));
	Assign(Gurax_CreateMethod(Node, IsText));
	// Assignment of property
	Assign(Gurax_CreateProperty(Node, depth));
	Assign(Gurax_CreateProperty(Node, parent));
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
