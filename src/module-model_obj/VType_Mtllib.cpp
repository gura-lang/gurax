//==============================================================================
// VType_Mtllib.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Mtllib, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Mtllib, `en)}

${help.ComposeMethodHelp(model.obj.Mtllib, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Mtllib() {block?}
Gurax_DeclareConstructor(Mtllib)
{
	Declare(VTYPE_Mtllib, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Mtllib` instance.
)""");
}

Gurax_ImplementConstructor(Mtllib)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Mtllib> pMtllib(new Mtllib());
	return argument.ReturnValue(processor, new Value_Mtllib(pMtllib.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Mtllib#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Mtllib, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Mtllib, MethodSkeleton)
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
// model.obj.Mtllib#propSkeleton
Gurax_DeclareProperty_R(Mtllib, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Mtllib, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Mtllib
//------------------------------------------------------------------------------
VType_Mtllib VTYPE_Mtllib("Mtllib");

void VType_Mtllib::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Mtllib));
	// Assignment of method
	Assign(Gurax_CreateMethod(Mtllib, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Mtllib, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Mtllib
//------------------------------------------------------------------------------
VType& Value_Mtllib::vtype = VTYPE_Mtllib;

String Value_Mtllib::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetMtllib().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
