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
// Implementation of operator
//------------------------------------------------------------------------------
// -Rational
Gurax_ImplementOpUnary(Neg, Rational)
{
	const Rational& rat = Value_Rational::GetRational(value);
	Rational ratRtn = -rat;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// +Rational
Gurax_ImplementOpUnary(Pos, Rational)
{
	const Rational& rat = Value_Rational::GetRational(value);
	Rational ratRtn = +rat;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational + Rational
Gurax_ImplementOpBinary(Add, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL + ratR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational - Rational
Gurax_ImplementOpBinary(Sub, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL - ratR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational * Rational
Gurax_ImplementOpBinary(Mul, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL * ratR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational / Rational
Gurax_ImplementOpBinary(Div, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	if (ratR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = ratL / ratR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational / Number
Gurax_ImplementOpBinary(Div, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = ratL / numR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Number / Rational
Gurax_ImplementOpBinary(Div, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	if (ratR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = numL / ratR;
	if (ratRtn.IsInteger()) return new Value_Number(ratRtn.GetNumer());
	return new Value_Rational(ratRtn);
}

// Rational == Rational
Gurax_ImplementOpBinary(Eq, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL == ratR);
}

// Rational != Rational
Gurax_ImplementOpBinary(Ne, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL != ratR);
}

// Rational < Rational
Gurax_ImplementOpBinary(Lt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL < ratR);
}

// Rational > Rational
Gurax_ImplementOpBinary(Gt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL > ratR);
}

// Rational <= Rational
Gurax_ImplementOpBinary(Le, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL <= ratR);
}

// Rational >= Rational
Gurax_ImplementOpBinary(Ge, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Rational(ratL >= ratR);
}

//------------------------------------------------------------------------------
// Implementation of suffix manager
//------------------------------------------------------------------------------
Gurax_ImplementSuffixMgr_Compose(Number, r)
{
	bool successFlag = false;
	Int64 numer = strRef.GetStringSTL().ToInt64(&successFlag);
	if (!successFlag) {
		String::IssueError_InvalidFormatOfNumber();
		return;
	}
	composer.Add_Value(new Value_Rational(Rational(numer, 1)), pExpr);	// [Value]
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
	// Assignment of operator
	Gurax_AssignOpUnary(Neg,	Rational);
	Gurax_AssignOpUnary(Pos,	Rational);
	Gurax_AssignOpBinary(Add,	Rational, Rational);
	Gurax_AssignOpBinary(Sub,	Rational, Rational);
	Gurax_AssignOpBinary(Mul,	Rational, Rational);
	Gurax_AssignOpBinary(Div,	Rational, Rational);
	Gurax_AssignOpBinary(Div,	Rational, Number);
	Gurax_AssignOpBinary(Div,	Number, Rational);
	Gurax_AssignOpBinary(Eq,	Rational, Rational);
	Gurax_AssignOpBinary(Ne,	Rational, Rational);
	Gurax_AssignOpBinary(Lt,	Rational, Rational);
	Gurax_AssignOpBinary(Gt,	Rational, Rational);
	Gurax_AssignOpBinary(Le,	Rational, Rational);
	Gurax_AssignOpBinary(Ge,	Rational, Rational);
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Number, r);
}

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
VType& Value_Rational::vtype = VTYPE_Rational;

}
