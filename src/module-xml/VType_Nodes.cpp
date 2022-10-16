//==============================================================================
// VType_Nodes.cpp
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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.Nodes() {block?}
Gurax_DeclareConstructor(Nodes)
{
	Declare(VTYPE_Nodes, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Nodes` instance.");
}

Gurax_ImplementConstructor(Nodes)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<NodeOwner> pNodes(new NodeOwner());
	return argument.ReturnValue(processor, new Value_Nodes(pNodes.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Nodes#Each(tagName? as String):[cdata,comment,element,text] {block?}
Gurax_DeclareMethod(Nodes, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("tagName", VTYPE_String, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(cdata));
	DeclareAttrOpt(Gurax_Symbol(comment));
	DeclareAttrOpt(Gurax_Symbol(element));
	DeclareAttrOpt(Gurax_Symbol(text));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Nodes, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	ArgPicker args(argument);
	const char* tagName = args.IsValid()? args.PickString() : "";
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(valueThis.GetNodes().Reference(), Node::GetTypeMask(argument, tagName), tagName));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Nodes#len
Gurax_DeclareProperty_R(Nodes, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Nodes, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetNodes().size());
}

//------------------------------------------------------------------------------
// VType_Nodes
//------------------------------------------------------------------------------
VType_Nodes VTYPE_Nodes("Nodes");

void VType_Nodes::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Nodes));
	// Assignment of method
	Assign(Gurax_CreateMethod(Nodes, Each));
	// Assignment of property
	Assign(Gurax_CreateProperty(Nodes, len));
}

//------------------------------------------------------------------------------
// Value_Nodes
//------------------------------------------------------------------------------
VType& Value_Nodes::vtype = VTYPE_Nodes;

bool Value_Nodes::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const NodeOwner& nodes = GetNodes();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, nodes.size(), &idx)) return false;
	*ppValue = nodes[idx]->CreateValue();
	return true;
}

String Value_Nodes::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "xml.Nodes");
}

Gurax_EndModuleScope(xml)
