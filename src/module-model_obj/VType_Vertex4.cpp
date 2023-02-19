//==============================================================================
// VType_Vertex4.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Vertex4, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Vertex4, `en)}

${help.ComposeMethodHelp(model.obj.Vertex4, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Vertex4() {block?}
Gurax_DeclareConstructor(Vertex4)
{
	Declare(VTYPE_Vertex4, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.obj.Vertex4` instance.
)**");
}

Gurax_ImplementConstructor(Vertex4)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Vertex4> pVertex4(new Vertex4());
	return argument.ReturnValue(processor, new Value_Vertex4(pVertex4.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Vertex4#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Vertex4, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Vertex4, MethodSkeleton)
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
// model.obj.Vertex4#propSkeleton
Gurax_DeclareProperty_R(Vertex4, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex4, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Vertex4
//------------------------------------------------------------------------------
VType_Vertex4 VTYPE_Vertex4("Vertex4");

void VType_Vertex4::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Vertex4));
	// Assignment of method
	Assign(Gurax_CreateMethod(Vertex4, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Vertex4, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Vertex4
//------------------------------------------------------------------------------
VType& Value_Vertex4::vtype = VTYPE_Vertex4;

String Value_Vertex4::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetVertex4().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
