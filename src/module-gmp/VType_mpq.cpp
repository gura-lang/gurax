//==============================================================================
// VType_mpq.cpp
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
// gmp.mpq#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(mpq, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(mpq, MethodSkeleton)
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
// gmp.mpq#denom
Gurax_DeclareProperty_R(mpq, denom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, denom)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_den());
}

// gmp.mpq#numer
Gurax_DeclareProperty_R(mpq, numer)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, numer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_num());
}

// gmp.mpq#sign
Gurax_DeclareProperty_R(mpq, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(mpq_sgn(valueThis.GetEntity().get_mpq_t()));
}

//------------------------------------------------------------------------------
// VType_mpq
//------------------------------------------------------------------------------
VType_mpq VTYPE_mpq("mpq");

void VType_mpq::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(mpq, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpq, denom));
	Assign(Gurax_CreateProperty(mpq, numer));
	Assign(Gurax_CreateProperty(mpq, sign));
}

//------------------------------------------------------------------------------
// Value_mpq
//------------------------------------------------------------------------------
VType& Value_mpq::vtype = VTYPE_mpq;

String Value_mpq::ToString(const StringStyle& ss) const
{
	String strEntity = GetEntity().get_str();
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

Gurax_EndModuleScope(gmp)
