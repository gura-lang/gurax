//==============================================================================
// VType_mpz.cpp
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
// gmp.mpz#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(mpz, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(mpz, MethodSkeleton)
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
// gmp.mpz#propSkeleton
Gurax_DeclareProperty_R(mpz, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(mpz, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_mpz
//------------------------------------------------------------------------------
VType_mpz VTYPE_mpz("mpz");

void VType_mpz::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(mpz, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(mpz, propSkeleton));
}

Value* VType_mpz::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	mpz_t num;
	if (value.IsInstanceOf(VTYPE_Number)) {
		::mpz_set_d(num, Value_Number::GetNumber<Double>(value));
		return new Value_mpz(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpq)) {
		::mpz_set_q(num, Value_mpq::GetEntity(value).get_mpq_t());
		return new Value_mpz(mpz_class(num));
	} else if (value.IsInstanceOf(VTYPE_mpf)) {
		::mpz_set_f(num, Value_mpf::GetEntity(value).get_mpf_t());
		return new Value_mpz(mpz_class(num));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_mpz
//------------------------------------------------------------------------------
VType& Value_mpz::vtype = VTYPE_mpz;

String Value_mpz::ToString(const StringStyle& ss) const
{
	String strEntity = GetEntity().get_str();
	strEntity += "L";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

Gurax_EndModuleScope(gmp)
