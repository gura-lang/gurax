//==============================================================================
// VType_Vertex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Vertex, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Vertex, `en)}

${help.ComposeMethodHelp(Vertex, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Vertex() {block?}
Gurax_DeclareConstructor(Vertex)
{
	Declare(VTYPE_Vertex, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Vertex` instance.
)**");
}

Gurax_ImplementConstructor(Vertex)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Vertex> pVertex(new Vertex());
	return argument.ReturnValue(processor, new Value_Vertex(pVertex.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Vertex#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Vertex, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Vertex, MethodSkeleton)
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
// Vertex#propSkeleton
Gurax_DeclareProperty_R(Vertex, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Vertex
//------------------------------------------------------------------------------
VType_Vertex VTYPE_Vertex("Vertex");

void VType_Vertex::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Vertex));
	// Assignment of method
	Assign(Gurax_CreateMethod(Vertex, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Vertex, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Vertex
//------------------------------------------------------------------------------
VType& Value_Vertex::vtype = VTYPE_Vertex;

String Value_Vertex::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetVertex().ToString(ss));
}

}
