//==============================================================================
// VType_Rational.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Rational, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Rational, `en)}

${help.ComposeMethodHelp(Rational, `en)}
)""";

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
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Rational` instance.
)""");
}

Gurax_ImplementConstructor(Rational)
{
	// Arguments
	ArgPicker args(argument);
	Int64 numer = args.IsValid()? args.PickNumber<Int64>() : 0;
	Int64 denom = args.IsValid()? args.PickNumber<Int64>() : 1;
	// Function body
	Rational rat = Rational::MakeCanonicalizedQuick(numer, denom);
	return argument.ReturnValue(processor, new Value_Rational(rat));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Rational#IsZero()
Gurax_DeclareMethod(Rational, IsZero)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the target rational equals to zero.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the target rational is greater than zero.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the target rational is less than zero.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the target rational is less than or equals to zero.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the target rational is greater than or equal to zero.
)""");
}

Gurax_ImplementMethod(Rational, IsNonNeg)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Bool(valueThis.GetRational().IsNonNeg());
}

// Rational#Canonicalize()
Gurax_DeclareMethod(Rational, Canonicalize)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a `Rational` instance that has been canonicalized from the target.
)""");
}

Gurax_ImplementMethod(Rational, Canonicalize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_Rational(valueThis.GetRational().Canonicalize());
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// Rational.format as String
Gurax_DeclareClassProperty_RW(Rational, format)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Format string used to convert a rational into a string.
)""");
}

Gurax_ImplementClassPropertyGetter(Rational, format)
{
	return new Value_String(Rational::formatterFormat);
}

Gurax_ImplementClassPropertySetter(Rational, format)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Int64, Formatter::VaType::Int64,
			Formatter::VaType::None)) return;
	Rational::formatterFormat = format;
}

// Rational.formatInt as String
Gurax_DeclareClassProperty_RW(Rational, formatInt)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Format string used to convert a rational which demoninator is one into a string.
)""");
}

Gurax_ImplementClassPropertyGetter(Rational, formatInt)
{
	return new Value_String(Rational::formatterFormat_Int);
}

Gurax_ImplementClassPropertySetter(Rational, formatInt)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Int64, Formatter::VaType::None)) return;
	Rational::formatterFormat_Int = format;
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Rational#denom as Number
Gurax_DeclareProperty_R(Rational, denom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The denomation part of the rational number.
)""");
}

Gurax_ImplementPropertyGetter(Rational, denom)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRational().GetDenom());
}

// Rational#numer as Number
Gurax_DeclareProperty_R(Rational, numer)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The numeration part of the rational number.
)""");
}

Gurax_ImplementPropertyGetter(Rational, numer)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRational().GetNumer());
}

// Rational#sign as Number
Gurax_DeclareProperty_R(Rational, sign)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The sign of the rational number. Returns 0 for a zero, -1 for a minus, and +1 for a plus.
)""");
}

Gurax_ImplementPropertyGetter(Rational, sign)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetRational().GetSign());
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
Gurax_ImplementOpBinary(Add, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL + ratR;
	return new Value_Rational(ratRtn);
}

// Rational + Number
Gurax_ImplementOpBinary(Add, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL + numR;
	return new Value_Rational(ratRtn);
}

// Number + Rational
Gurax_ImplementOpBinary(Add, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL + ratR;
	return new Value_Rational(ratRtn);
}

// Rational - Rational
Gurax_ImplementOpBinary(Sub, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL - ratR;
	return new Value_Rational(ratRtn);
}

// Rational - Number
Gurax_ImplementOpBinary(Sub, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL - numR;
	return new Value_Rational(ratRtn);
}

// Number - Rational
Gurax_ImplementOpBinary(Sub, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL - ratR;
	return new Value_Rational(ratRtn);
}

// Rational * Rational
Gurax_ImplementOpBinary(Mul, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = ratL * ratR;
	return new Value_Rational(ratRtn);
}

// Rational * Number
Gurax_ImplementOpBinary(Mul, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	Rational ratRtn = ratL * numR;
	return new Value_Rational(ratRtn);
}

// Number * Rational
Gurax_ImplementOpBinary(Mul, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	Rational ratRtn = numL * ratR;
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
	return new Value_Rational(ratRtn);
}

// Rational == Rational
Gurax_ImplementOpBinary(Eq, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL == ratR);
}

// Rational == Number
Gurax_ImplementOpBinary(Eq, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL == Rational::MakeFromDouble(numR));
}

// Number == Rational
Gurax_ImplementOpBinary(Eq, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) == ratR);
}

// Rational != Rational
Gurax_ImplementOpBinary(Ne, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL != ratR);
}

// Rational != Number
Gurax_ImplementOpBinary(Ne, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL != Rational::MakeFromDouble(numR));
}

// Number != Rational
Gurax_ImplementOpBinary(Ne, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) != ratR);
}

// Rational < Rational
Gurax_ImplementOpBinary(Lt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL < ratR);
}

// Rational < Number
Gurax_ImplementOpBinary(Lt, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL < Rational::MakeFromDouble(numR));
}

// Number < Rational
Gurax_ImplementOpBinary(Lt, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) < ratR);
}

// Rational > Rational
Gurax_ImplementOpBinary(Gt, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL > ratR);
}

// Rational > Number
Gurax_ImplementOpBinary(Gt, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL > Rational::MakeFromDouble(numR));
}

// Number > Rational
Gurax_ImplementOpBinary(Gt, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) > ratR);
}

// Rational <= Rational
Gurax_ImplementOpBinary(Le, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL <= ratR);
}

// Rational <= Number
Gurax_ImplementOpBinary(Le, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL <= Rational::MakeFromDouble(numR));
}

// Number <= Rational
Gurax_ImplementOpBinary(Le, Number, Rational)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(Rational::MakeFromDouble(numL) <= ratR);
}

// Rational >= Rational
Gurax_ImplementOpBinary(Ge, Rational, Rational)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	const Rational& ratR = Value_Rational::GetRational(valueR);
	return new Value_Bool(ratL >= ratR);
}

// Rational >= Number
Gurax_ImplementOpBinary(Ge, Rational, Number)
{
	const Rational& ratL = Value_Rational::GetRational(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(ratL >= Rational::MakeFromDouble(numR));
}

// Number >= Rational
Gurax_ImplementOpBinary(Ge, Number, Rational)
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Rational));
	// Assignment of method
	Assign(Gurax_CreateMethod(Rational, IsZero));
	Assign(Gurax_CreateMethod(Rational, IsPos));
	Assign(Gurax_CreateMethod(Rational, IsNeg));
	Assign(Gurax_CreateMethod(Rational, IsNonPos));
	Assign(Gurax_CreateMethod(Rational, IsNonNeg));
	Assign(Gurax_CreateMethod(Rational, Canonicalize));
	// Assignment of class property
	Assign(Gurax_CreateProperty(Rational, format));
	Assign(Gurax_CreateProperty(Rational, formatInt));
	// Assignment of property
	Assign(Gurax_CreateProperty(Rational, denom));
	Assign(Gurax_CreateProperty(Rational, numer));
	Assign(Gurax_CreateProperty(Rational, sign));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg,	Rational);
	Gurax_AssignOpUnary(Pos,	Rational);
	Gurax_AssignOpBinary(Add,	Rational, Rational);
	Gurax_AssignOpBinary(Add,	Rational, Number);
	Gurax_AssignOpBinary(Add,	Number, Rational);
	Gurax_AssignOpBinary(Sub,	Rational, Rational);
	Gurax_AssignOpBinary(Sub,	Rational, Number);
	Gurax_AssignOpBinary(Sub,	Number, Rational);
	Gurax_AssignOpBinary(Mul,	Rational, Rational);
	Gurax_AssignOpBinary(Mul,	Rational, Number);
	Gurax_AssignOpBinary(Mul,	Number, Rational);
	Gurax_AssignOpBinary(Div,	Rational, Rational);
	Gurax_AssignOpBinary(Div,	Rational, Number);
	Gurax_AssignOpBinary(Div,	Number, Rational);
	Gurax_AssignOpBinary(Eq,	Rational, Rational);
	Gurax_AssignOpBinary(Eq,	Rational, Number);
	Gurax_AssignOpBinary(Eq,	Number, Rational);
	Gurax_AssignOpBinary(Ne,	Rational, Rational);
	Gurax_AssignOpBinary(Ne,	Rational, Number);
	Gurax_AssignOpBinary(Ne,	Number, Rational);
	Gurax_AssignOpBinary(Lt,	Rational, Rational);
	Gurax_AssignOpBinary(Lt,	Rational, Number);
	Gurax_AssignOpBinary(Lt,	Number, Rational);
	Gurax_AssignOpBinary(Gt,	Rational, Rational);
	Gurax_AssignOpBinary(Gt,	Rational, Number);
	Gurax_AssignOpBinary(Gt,	Number, Rational);
	Gurax_AssignOpBinary(Le,	Rational, Rational);
	Gurax_AssignOpBinary(Le,	Rational, Number);
	Gurax_AssignOpBinary(Le,	Number, Rational);
	Gurax_AssignOpBinary(Ge,	Rational, Rational);
	Gurax_AssignOpBinary(Ge,	Rational, Number);
	Gurax_AssignOpBinary(Ge,	Number, Rational);
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
	String strEntity = GetRational().ToString(ss);
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

}
