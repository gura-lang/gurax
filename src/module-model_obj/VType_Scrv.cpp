//==============================================================================
// VType_Scrv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Scrv, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Scrv, `en)}

${help.ComposeMethodHelp(model.obj.Scrv, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Scrv() {block?}
Gurax_DeclareConstructor(Scrv)
{
	Declare(VTYPE_Scrv, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Scrv` instance.
)""");
}

Gurax_ImplementConstructor(Scrv)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Scrv> pScrv(new Scrv());
	return argument.ReturnValue(processor, new Value_Scrv(pScrv.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Scrv#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Scrv, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Scrv, MethodSkeleton)
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
// model.obj.Scrv#propSkeleton
Gurax_DeclareProperty_R(Scrv, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Scrv, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Scrv
//------------------------------------------------------------------------------
VType_Scrv VTYPE_Scrv("Scrv");

void VType_Scrv::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Scrv));
	// Assignment of method
	Assign(Gurax_CreateMethod(Scrv, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Scrv, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Scrv
//------------------------------------------------------------------------------
VType& Value_Scrv::vtype = VTYPE_Scrv;


String Value_Scrv::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetScrv().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
