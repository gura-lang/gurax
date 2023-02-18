//==============================================================================
// VType_Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.stl.Face, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.stl.Face, `en)}

${help.ComposeMethodHelp(model.stl.Face, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.stl.Face() {block?}
Gurax_DeclareConstructor(Face)
{
	Declare(VTYPE_Face, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.stl.Face` instance.
)**");
}

Gurax_ImplementConstructor(Face)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Face> pFace(new Face());
	return argument.ReturnValue(processor, new Value_Face(pFace.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
#if 0
// model.stl.Face#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Face, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Face, MethodSkeleton)
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
#endif

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.stl.Face#normal
Gurax_DeclareProperty_R(Face, normal)
{
	Declare(VTYPE_Vertex, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, normal)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Vertex(valueThis.GetFace().GetNormalRef().Reference());
}

// model.stl.Face#vertex1
Gurax_DeclareProperty_R(Face, vertex1)
{
	Declare(VTYPE_Vertex, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, vertex1)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Vertex(valueThis.GetFace().GetVertex1Ref().Reference());
}

// model.stl.Face#vertex2
Gurax_DeclareProperty_R(Face, vertex2)
{
	Declare(VTYPE_Vertex, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, vertex2)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Vertex(valueThis.GetFace().GetVertex2Ref().Reference());
}

// model.stl.Face#vertex3
Gurax_DeclareProperty_R(Face, vertex3)
{
	Declare(VTYPE_Vertex, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, vertex3)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Vertex(valueThis.GetFace().GetVertex3Ref().Reference());
}

// model.stl.Face#attr
Gurax_DeclareProperty_R(Face, attr)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, attr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetFace().GetAttr());
}

//------------------------------------------------------------------------------
// VType_Face
//------------------------------------------------------------------------------
VType_Face VTYPE_Face("Face");

void VType_Face::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Face));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Face, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Face, normal));
	Assign(Gurax_CreateProperty(Face, vertex1));
	Assign(Gurax_CreateProperty(Face, vertex2));
	Assign(Gurax_CreateProperty(Face, vertex3));
	Assign(Gurax_CreateProperty(Face, attr));
}

//------------------------------------------------------------------------------
// Value_Face
//------------------------------------------------------------------------------
VType& Value_Face::vtype = VTYPE_Face;

String Value_Face::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFace().ToString(ss));
}

Gurax_EndModuleScope(model_stl)
