//==============================================================================
// VType_NodeMap.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.NodeMap, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.NodeMap, `en)}

${help.ComposeMethodHelp(ml.NodeMap, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.NodeMap() {block?}
Gurax_DeclareConstructor(NodeMap)
{
	Declare(VTYPE_NodeMap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.NodeMap` instance.
)""");
}

Gurax_ImplementConstructor(NodeMap)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<NodeMap> pNodeMap(new NodeMap());
	return argument.ReturnValue(processor, new Value_NodeMap(pNodeMap.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// ml.NodeMap#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(NodeMap, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(NodeMap, MethodSkeleton)
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
// ml.NodeMap#propSkeleton
Gurax_DeclareProperty_R(NodeMap, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(NodeMap, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_NodeMap
//------------------------------------------------------------------------------
VType_NodeMap VTYPE_NodeMap("NodeMap");

void VType_NodeMap::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(NodeMap));
	// Assignment of method
	Assign(Gurax_CreateMethod(NodeMap, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(NodeMap, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_NodeMap
//------------------------------------------------------------------------------
VType& Value_NodeMap::vtype = VTYPE_NodeMap;

String Value_NodeMap::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetNodeMap().ToString(ss));
}

Value* Value_NodeMap::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	Node* pNode = _pNodeMap->FindNode(pSymbol);
	if (pNode) return new Value_Node(pNode->Reference());
	return Value::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

Gurax_EndModuleScope(ml)
