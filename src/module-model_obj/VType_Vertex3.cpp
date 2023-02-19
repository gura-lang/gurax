//==============================================================================
// VType_Vertex3.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Vertex3, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Vertex3, `en)}

${help.ComposeMethodHelp(model.obj.Vertex3, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Vertex3() {block?}
Gurax_DeclareConstructor(Vertex3)
{
	Declare(VTYPE_Vertex3, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `model.obj.Vertex3` instance.
)**");
}

Gurax_ImplementConstructor(Vertex3)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Vertex3> pVertex3(new Vertex3());
	return argument.ReturnValue(processor, new Value_Vertex3(pVertex3.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Vertex3#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Vertex3, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Vertex3, MethodSkeleton)
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
// model.obj.Vertex3#propSkeleton
Gurax_DeclareProperty_R(Vertex3, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(Vertex3, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Vertex3
//------------------------------------------------------------------------------
VType_Vertex3 VTYPE_Vertex3("Vertex3");

void VType_Vertex3::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Vertex3));
	// Assignment of method
	Assign(Gurax_CreateMethod(Vertex3, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Vertex3, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Vertex3
//------------------------------------------------------------------------------
VType& Value_Vertex3::vtype = VTYPE_Vertex3;

String Value_Vertex3::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetVertex3().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
