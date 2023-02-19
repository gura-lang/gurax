//==============================================================================
// VType_Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Face, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Face, `en)}

${help.ComposeMethodHelp(model.obj.Face, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Face() {block?}
Gurax_DeclareConstructor(Face)
{
	Declare(VTYPE_Face, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.obj.Face` instance.
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
// model.obj.Face#MethodSkeleton(num1 as Number, num2 as Number)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// model.obj.Face#propSkeleton
Gurax_DeclareProperty_R(Face, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Face, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateMethod(Face, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Face, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Face
//------------------------------------------------------------------------------
VType& Value_Face::vtype = VTYPE_Face;

String Value_Face::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetFace().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
