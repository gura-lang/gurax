//==============================================================================
// VType_mpf.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gmp.mpf#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(mpf, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(mpf, MethodSkeleton)
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
// gmp.mpf#propSkeleton
Gurax_DeclareProperty_R(mpf, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpf, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_mpf
//------------------------------------------------------------------------------
VType_mpf VTYPE_mpf("mpf");

void VType_mpf::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(mpf, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpf, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_mpf
//------------------------------------------------------------------------------
VType& Value_mpf::vtype = VTYPE_mpf;

String Value_mpf::ToString(const StringStyle& ss) const
{
	mp_exp_t exp = 0;
	String strEntity = GetEntity().get_str(exp);
	strEntity += "L";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

Gurax_EndModuleScope(gmp)
