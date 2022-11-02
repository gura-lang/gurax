//==============================================================================
// VType_Opt.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Opt)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Opt)}

${help.ComposeMethodHelp(Opt)}
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.Opt#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Opt, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Opt, MethodSkeleton)
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
// curl.Opt#propSkeleton
Gurax_DeclareProperty_R(Opt, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Opt, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Opt
//------------------------------------------------------------------------------
VType_Opt VTYPE_Opt("Opt");

void VType_Opt::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Opt, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Opt, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Opt
//------------------------------------------------------------------------------
VType& Value_Opt::vtype = VTYPE_Opt;

String Value_Opt::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOpt().ToString(ss));
}

bool Value_Opt::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	return GetOpt().SetProperty(pSymbol, *pValue);
}

Gurax_EndModuleScope(curl)
