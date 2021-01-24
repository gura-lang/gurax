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
// gmp.mpq#den
Gurax_DeclareProperty_R(mpq, den)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, den)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_den());
}

// gmp.mpq#num
Gurax_DeclareProperty_R(mpq, num)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, num)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_mpz(valueThis.GetEntity().get_num());
}

// gmp.mpq#sgn
Gurax_DeclareProperty_R(mpq, sgn)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpq, sgn)
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
	Assign(Gurax_CreateProperty(mpq, den));
	Assign(Gurax_CreateProperty(mpq, num));
	Assign(Gurax_CreateProperty(mpq, sgn));
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
