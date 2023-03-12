//==============================================================================
// VType_Deg.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Deg, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Deg, `en)}

${help.ComposeMethodHelp(model.obj.Deg, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Deg() {block?}
Gurax_DeclareConstructor(Deg)
{
	Declare(VTYPE_Deg, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Deg` instance.
)""");
}

Gurax_ImplementConstructor(Deg)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Deg> pDeg(new Deg());
	return argument.ReturnValue(processor, new Value_Deg(pDeg.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Deg#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Deg, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Deg, MethodSkeleton)
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
// model.obj.Deg#propSkeleton
Gurax_DeclareProperty_R(Deg, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Deg, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Deg
//------------------------------------------------------------------------------
VType_Deg VTYPE_Deg("Deg");

void VType_Deg::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Deg));
	// Assignment of method
	Assign(Gurax_CreateMethod(Deg, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Deg, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Deg
//------------------------------------------------------------------------------
VType& Value_Deg::vtype = VTYPE_Deg;

String Value_Deg::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDeg().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
