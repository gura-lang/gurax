//==============================================================================
// VType_Trim.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(model.obj.Trim, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(model.obj.Trim, `en)}

${help.ComposeMethodHelp(model.obj.Trim, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// model.obj.Trim() {block?}
Gurax_DeclareConstructor(Trim)
{
	Declare(VTYPE_Trim, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `model.obj.Trim` instance.
)""");
}

Gurax_ImplementConstructor(Trim)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Trim> pTrim(new Trim());
	return argument.ReturnValue(processor, new Value_Trim(pTrim.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// model.obj.Trim#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Trim, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Trim, MethodSkeleton)
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
// model.obj.Trim#propSkeleton
Gurax_DeclareProperty_R(Trim, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Trim, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Trim
//------------------------------------------------------------------------------
VType_Trim VTYPE_Trim("Trim");

void VType_Trim::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Trim));
	// Assignment of method
	Assign(Gurax_CreateMethod(Trim, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Trim, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Trim
//------------------------------------------------------------------------------
VType& Value_Trim::vtype = VTYPE_Trim;

String Value_Trim::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTrim().ToString(ss));
}

Gurax_EndModuleScope(model_obj)
