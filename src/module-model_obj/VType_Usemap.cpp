//==============================================================================
// VType_Usemap.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Usemap, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Usemap, `en)}

${help.ComposeMethodHelp(model.obj.Usemap, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Usemap() {block?}
Gurax_DeclareConstructor(Usemap)
{
	Declare(VTYPE_Usemap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Usemap` instance.
)""");
}

Gurax_ImplementConstructor(Usemap)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Usemap> pUsemap(new Usemap());
	return argument.ReturnValue(processor, new Value_Usemap(pUsemap.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Usemap#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Usemap, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Usemap, MethodSkeleton)
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
// model.obj.Usemap#propSkeleton
Gurax_DeclareProperty_R(Usemap, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Usemap, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Usemap
//------------------------------------------------------------------------------
VType_Usemap VTYPE_Usemap("Usemap");

void VType_Usemap::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Usemap));
	// Assignment of method
	Assign(Gurax_CreateMethod(Usemap, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Usemap, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Usemap
//------------------------------------------------------------------------------
VType& Value_Usemap::vtype = VTYPE_Usemap;

String Value_Usemap::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetUsemap().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
