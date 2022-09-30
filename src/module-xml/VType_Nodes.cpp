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
// xml.Nodes#Each() {block?}
Gurax_DeclareMethod(Nodes, Each)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Nodes, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Node(valueThis.GetNodes().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Nodes#propSkeleton
Gurax_DeclareProperty_R(Nodes, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Nodes, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateProperty(Nodes, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Nodes
//------------------------------------------------------------------------------
VType& Value_Nodes::vtype = VTYPE_Nodes;

String Value_Nodes::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "xml.Nodes");
}

Gurax_EndModuleScope(xml)
