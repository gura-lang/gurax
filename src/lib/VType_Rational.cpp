//==============================================================================
// VType_Rational.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Rational() {block?}
Gurax_DeclareConstructor(Rational)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Rational` instance.");
}

Gurax_ImplementConstructor(Rational)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	Rational rational;
	return argument.ReturnValue(processor, new Value_Rational(rational));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Rational#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Rational, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Rational, MethodSkeleton)
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
// Rational#denom
Gurax_DeclareProperty_R(Rational, denom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The denomation part of the rational number.");
}

Gurax_ImplementPropertyGetter(Rational, denom)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRational().GetDenom());
}

// Rational#numer
Gurax_DeclareProperty_R(Rational, numer)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The numeration part of the rational number.");
}

Gurax_ImplementPropertyGetter(Rational, numer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRational().GetNumer());
}

//------------------------------------------------------------------------------
// VType_Rational
//------------------------------------------------------------------------------
VType_Rational VTYPE_Rational("Rational");

void VType_Rational::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Rational));
	// Assignment of method
	Assign(Gurax_CreateMethod(Rational, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Rational, denom));
	Assign(Gurax_CreateProperty(Rational, numer));
}

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
VType& Value_Rational::vtype = VTYPE_Rational;

}
