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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Iterator_Node
//------------------------------------------------------------------------------
Value* Iterator_Node::DoNextValue()
{
	const NodeOwner& nodeOwner = GetNodeOwner();
	if (_idx >= nodeOwner.size()) return nullptr;
	RefPtr<Value> pValue(new Value_Node(nodeOwner[_idx]->Reference()));
	_idx++;
	return pValue.release();
}

String Iterator_Node::ToString(const StringStyle& ss) const
{
	return String().Format("Node:n=%zu", GetNodeOwner().size());
}

Gurax_EndModuleScope(ml)
