//==============================================================================
// VType_Shadow_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Shadow_obj, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Shadow_obj, `en)}

${help.ComposeMethodHelp(model.obj.Shadow_obj, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Shadow_obj() {block?}
Gurax_DeclareConstructor(Shadow_obj)
{
	Declare(VTYPE_Shadow_obj, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Shadow_obj` instance.
)""");
}

Gurax_ImplementConstructor(Shadow_obj)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Shadow_obj> pShadow_obj(new Shadow_obj());
	return argument.ReturnValue(processor, new Value_Shadow_obj(pShadow_obj.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Shadow_obj#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Shadow_obj, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Shadow_obj, MethodSkeleton)
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
// model.obj.Shadow_obj#propSkeleton
Gurax_DeclareProperty_R(Shadow_obj, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Shadow_obj, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Shadow_obj
//------------------------------------------------------------------------------
VType_Shadow_obj VTYPE_Shadow_obj("Shadow_obj");

void VType_Shadow_obj::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Shadow_obj));
	// Assignment of method
	Assign(Gurax_CreateMethod(Shadow_obj, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Shadow_obj, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Shadow_obj
//------------------------------------------------------------------------------
VType& Value_Shadow_obj::vtype = VTYPE_Shadow_obj;

String Value_Shadow_obj::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetShadow_obj().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
