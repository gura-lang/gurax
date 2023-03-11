//==============================================================================
// VType_Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.Info, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.Info, `en)}

${help.ComposeMethodHelp(curl.Info, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.Info#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Info, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Info, MethodSkeleton)
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
// curl.Info#propSkeleton
Gurax_DeclareProperty_R(Info, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Info, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Info
//------------------------------------------------------------------------------
VType_Info VTYPE_Info("Info");

void VType_Info::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Info, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Info, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Info
//------------------------------------------------------------------------------
VType& Value_Info::vtype = VTYPE_Info;

String Value_Info::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetInfo().ToString(ss));
}

Value* Value_Info::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return GetInfo().GetProperty(pSymbol);
}

Gurax_EndModuleScope(curl)
