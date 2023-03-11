//==============================================================================
// VType_Lod.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Lod, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Lod, `en)}

${help.ComposeMethodHelp(model.obj.Lod, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Lod() {block?}
Gurax_DeclareConstructor(Lod)
{
	Declare(VTYPE_Lod, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Lod` instance.
)""");
}

Gurax_ImplementConstructor(Lod)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Lod> pLod(new Lod());
	return argument.ReturnValue(processor, new Value_Lod(pLod.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Lod#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Lod, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Lod, MethodSkeleton)
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
// model.obj.Lod#propSkeleton
Gurax_DeclareProperty_R(Lod, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Lod, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Lod
//------------------------------------------------------------------------------
VType_Lod VTYPE_Lod("Lod");

void VType_Lod::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Lod));
	// Assignment of method
	Assign(Gurax_CreateMethod(Lod, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Lod, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Lod
//------------------------------------------------------------------------------
VType& Value_Lod::vtype = VTYPE_Lod;

String Value_Lod::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLod().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
