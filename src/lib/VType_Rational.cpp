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
// Rational(numer?:Number, denom?:Number) {block?}
Gurax_DeclareConstructor(Rational)
{
	Declare(VTYPE_Rational, Flag::None);
	DeclareArg("numer", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("denom", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Rational` instance.");
}

Gurax_ImplementConstructor(Rational)
{
	// Arguments
	ArgPicker args(argument);
	Int64 numer = args.IsValid()? args.PickNumber<Int64>() : 0;
	Int64 denom = args.IsValid()? args.PickNumber<Int64>() : 1;
	// Function body
	Rational rat = Rational::MakeRegulatedQuick(numer, denom);
	return argument.ReturnValue(processor, new Value_Rational(rat));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Rational#IsZero()
Gurax_DeclareMethod(Rational, IsZero)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the target rational equals to zero.\n");
}

Gurax_ImplementMethod(Rational, IsZero)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsZero());
}

// Rational#IsPos()
Gurax_DeclareMethod(Rational, IsPos)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the target rational is greater than zero.\n");
}

Gurax_ImplementMethod(Rational, IsPos)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsPos());
}

// Rational#IsNeg()
Gurax_DeclareMethod(Rational, IsNeg)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the target rational is less than zero.\n");
}

Gurax_ImplementMethod(Rational, IsNeg)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsNeg());
}

// Rational#IsNonPos()
Gurax_DeclareMethod(Rational, IsNonPos)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the target rational is less than or equals to zero.\n");
}

Gurax_ImplementMethod(Rational, IsNonPos)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsNonPos());
}

// Rational#IsNonNeg()
Gurax_DeclareMethod(Rational, IsNonNeg)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the target rational is greater than or equal to zero.\n");
}

Gurax_ImplementMethod(Rational, IsNonNeg)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsNonNeg());
}

// Rational#Regulate()
Gurax_DeclareMethod(Rational, Regulate)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `Rational` instance that has been regulated from the target.\n");
}

Gurax_ImplementMethod(Rational, Regulate)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Rational(valueThis.GetRational().Regulate());
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// Rational.format:String
Gurax_DeclareClassProperty_RW(Rational, format)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert a rational into a string.");
}

Gurax_ImplementClassPropertyGetter(Rational, format)
{
	return new Value_String(Rational::GetFormatterFormat());
}

Gurax_ImplementClassPropertySetter(Rational, format)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Int64, Formatter::VaType::Int64,
			Formatter::VaType::None)) return;
	Rational::SetFormatterFormat(format);
}

// Rational.formatInt:String
Gurax_DeclareClassProperty_RW(Rational, formatInt)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert a rational which demoninator is one into a string.");
}

Gurax_ImplementClassPropertyGetter(Rational, formatInt)
{
	return new Value_String(Rational::GetFormatterFormat_Int());
}

Gurax_ImplementClassPropertySetter(Rational, formatInt)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Int64, Formatter::VaType::None)) return;
	Rational::SetFormatterFormat_Int(format);
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
	return new Value_Rational(ratRtn);
}

// +Rational
Gurax_ImplementOpUnary(Pos, Rational)
{
	const Rational& rat = Value_Rational::GetRational(value);
	Rational ratRtn = +rat;
	return new Value_Rational(ratRtn);
}

// Rational + Rational
Gurax_ImplementBinary(Add, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL + ratR;
	return new Value_Rational(ratRtn);
}

// Rational + Number
Gurax_ImplementBinary(Add, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL + numR;
	return new Value_Rational(ratRtn);
}

// Number + Rational
Gurax_ImplementBinary(Add, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL + ratR;
	return new Value_Rational(ratRtn);
}

// Rational - Rational
Gurax_ImplementBinary(Sub, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL - ratR;
	return new Value_Rational(ratRtn);
}

// Rational - Number
Gurax_ImplementBinary(Sub, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL - numR;
	return new Value_Rational(ratRtn);
}

// Number - Rational
Gurax_ImplementBinary(Sub, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL - ratR;
	return new Value_Rational(ratRtn);
}

// Rational * Rational
Gurax_ImplementBinary(Mul, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL * ratR;
	return new Value_Rational(ratRtn);
}

// Rational * Number
Gurax_ImplementBinary(Mul, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL * numR;
	return new Value_Rational(ratRtn);
}

// Number * Rational
Gurax_ImplementBinary(Mul, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL * ratR;
	return new Value_Rational(ratRtn);
}

// Rational / Rational
Gurax_ImplementBinary(Div, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	if (ratR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = ratL / ratR;
	return new Value_Rational(ratRtn);
}

// Rational / Number
Gurax_ImplementBinary(Div, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = ratL / numR;
	return new Value_Rational(ratRtn);
}

// Number / Rational
Gurax_ImplementBinary(Div, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	if (ratR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::nil();
	}
	Rational ratRtn = numL / ratR;
	return new Value_Rational(ratRtn);
}

// Rational == Rational
Gurax_ImplementBinary(Eq, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL == ratR);
}

// Rational == Number
Gurax_ImplementBinary(Eq, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL == Rational::MakeFromDouble(numR));
}

// Number == Rational
Gurax_ImplementBinary(Eq, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) == ratR);
}

// Rational != Rational
Gurax_ImplementBinary(Ne, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL != ratR);
}

// Rational != Number
Gurax_ImplementBinary(Ne, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL != Rational::MakeFromDouble(numR));
}

// Number != Rational
Gurax_ImplementBinary(Ne, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) != ratR);
}

// Rational < Rational
Gurax_ImplementBinary(Lt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL < ratR);
}

// Rational < Number
Gurax_ImplementBinary(Lt, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL < Rational::MakeFromDouble(numR));
}

// Number < Rational
Gurax_ImplementBinary(Lt, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) < ratR);
}

// Rational > Rational
Gurax_ImplementBinary(Gt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL > ratR);
}

// Rational > Number
Gurax_ImplementBinary(Gt, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL > Rational::MakeFromDouble(numR));
}

// Number > Rational
Gurax_ImplementBinary(Gt, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) > ratR);
}

// Rational <= Rational
Gurax_ImplementBinary(Le, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL <= ratR);
}

// Rational <= Number
Gurax_ImplementBinary(Le, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL <= Rational::MakeFromDouble(numR));
}

// Number <= Rational
Gurax_ImplementBinary(Le, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) <= ratR);
}

// Rational >= Rational
Gurax_ImplementBinary(Ge, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL >= ratR);
}

// Rational >= Number
Gurax_ImplementBinary(Ge, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL >= Rational::MakeFromDouble(numR));
}

// Number >= Rational
Gurax_ImplementBinary(Ge, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) >= ratR);
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
	composer.Add_Value(new Value_Rational(Rational(numer, 1)), *pExpr);			// [Value]
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
	Assign(Gurax_CreateMethod(Rational, IsZero));
	Assign(Gurax_CreateMethod(Rational, IsPos));
	Assign(Gurax_CreateMethod(Rational, IsNeg));
	Assign(Gurax_CreateMethod(Rational, IsNonPos));
	Assign(Gurax_CreateMethod(Rational, IsNonNeg));
	Assign(Gurax_CreateMethod(Rational, Regulate));
	// Assignment of class property
	Assign(Gurax_CreateProperty(Rational, format));
	Assign(Gurax_CreateProperty(Rational, formatInt));
	// Assignment of property
	Assign(Gurax_CreateProperty(Rational, denom));
	Assign(Gurax_CreateProperty(Rational, numer));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg,	Rational);
	Gurax_AssignOpUnary(Pos,	Rational);
	Gurax_AssignBinary(Add,	Rational, Rational);
	Gurax_AssignBinary(Add,	Rational, Number);
	Gurax_AssignBinary(Add,	Number, Rational);
	Gurax_AssignBinary(Sub,	Rational, Rational);
	Gurax_AssignBinary(Sub,	Rational, Number);
	Gurax_AssignBinary(Sub,	Number, Rational);
	Gurax_AssignBinary(Mul,	Rational, Rational);
	Gurax_AssignBinary(Mul,	Rational, Number);
	Gurax_AssignBinary(Mul,	Number, Rational);
	Gurax_AssignBinary(Div,	Rational, Rational);
	Gurax_AssignBinary(Div,	Rational, Number);
	Gurax_AssignBinary(Div,	Number, Rational);
	Gurax_AssignBinary(Eq,	Rational, Rational);
	Gurax_AssignBinary(Eq,	Rational, Number);
	Gurax_AssignBinary(Eq,	Number, Rational);
	Gurax_AssignBinary(Ne,	Rational, Rational);
	Gurax_AssignBinary(Ne,	Rational, Number);
	Gurax_AssignBinary(Ne,	Number, Rational);
	Gurax_AssignBinary(Lt,	Rational, Rational);
	Gurax_AssignBinary(Lt,	Rational, Number);
	Gurax_AssignBinary(Lt,	Number, Rational);
	Gurax_AssignBinary(Gt,	Rational, Rational);
	Gurax_AssignBinary(Gt,	Rational, Number);
	Gurax_AssignBinary(Gt,	Number, Rational);
	Gurax_AssignBinary(Le,	Rational, Rational);
	Gurax_AssignBinary(Le,	Rational, Number);
	Gurax_AssignBinary(Le,	Number, Rational);
	Gurax_AssignBinary(Ge,	Rational, Rational);
	Gurax_AssignBinary(Ge,	Rational, Number);
	Gurax_AssignBinary(Ge,	Number, Rational);
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Number, r);
}

Value* VType_Rational::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Number)) {
		return new Value_Rational(Rational::MakeFromDouble(Value_Number::GetNumber<Double>(value)));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Rational
//------------------------------------------------------------------------------
VType& Value_Rational::vtype = VTYPE_Rational;

String Value_Rational::ToString(const StringStyle& ss) const
{
	return GetRational().ToString(ss);
}

}
