//==============================================================================
// VType_Bevel.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Bevel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Bevel, `en)}

${help.ComposeMethodHelp(model.obj.Bevel, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Bevel() {block?}
Gurax_DeclareConstructor(Bevel)
{
	Declare(VTYPE_Bevel, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Bevel` instance.
)""");
}

Gurax_ImplementConstructor(Bevel)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Bevel> pBevel(new Bevel());
	return argument.ReturnValue(processor, new Value_Bevel(pBevel.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Bevel#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Bevel, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Bevel, MethodSkeleton)
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
// model.obj.Bevel#propSkeleton
Gurax_DeclareProperty_R(Bevel, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Bevel, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Bevel
//------------------------------------------------------------------------------
VType_Bevel VTYPE_Bevel("Bevel");

void VType_Bevel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Bevel));
	// Assignment of method
	Assign(Gurax_CreateMethod(Bevel, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Bevel, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Bevel
//------------------------------------------------------------------------------
VType& Value_Bevel::vtype = VTYPE_Bevel;

String Value_Bevel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetBevel().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
