//==============================================================================
// VType_Number.cpp
//==============================================================================
#include "stdafx.h"

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
// Implementation of property
//------------------------------------------------------------------------------
// Number#abs
Gurax_DeclareProperty_R(Number, abs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The absolute value of the number.");
}

Gurax_ImplementPropertyGetter(Number, abs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(std::abs(valueThis.GetNumber<Double>()));
}

// Number#arg
Gurax_DeclareProperty_R(Number, arg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The argument value of the number. Always returns zero.");
}

Gurax_ImplementPropertyGetter(Number, arg)
{
	return Value::Zero();
}

// Number#imag
Gurax_DeclareProperty_R(Number, imag)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The imaginary part of the number. Always returns zero.");
}

Gurax_ImplementPropertyGetter(Number, imag)
{
	return Value::Zero();
}

// Number#norm
Gurax_DeclareProperty_R(Number, norm)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The norm value of the number.");
}

Gurax_ImplementPropertyGetter(Number, norm)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(std::norm(valueThis.GetNumber<Double>()));
}

// Number#real
Gurax_DeclareProperty_R(Number, real)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The real part of the number. Always returns the number itself.");
}

Gurax_ImplementPropertyGetter(Number, real)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetNumber<Double>());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// ~Number
Gurax_ImplementOpUnary(Inv, Number)
{
	Int num = Value_Number::GetNumber<Int>(value);
	return new Value_Number(~num);
}

// -Number
Gurax_ImplementOpUnary(Neg, Number)
{
	Double num = Value_Number::GetNumber<Double>(value);
	return new Value_Number(-num);
}

// +Number
Gurax_ImplementOpUnary(Pos, Number)
{
	return value.Clone();
}

// Number ..
Gurax_ImplementOpUnary(PostSeq, Number)
{
	int num = Value_Number::GetNumber<Int>(value);
	return new Value_Iterator(new Iterator_Counter(num, 1));
}

// Number + Number
Gurax_ImplementOpBinary(Add, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number & Number
Gurax_ImplementOpBinary(And, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <=> Number
Gurax_ImplementOpBinary(Cmp, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	int rslt = (numL < numR)? -1 : (numL > numR)? +1 : 0;
	return new Value_Number(rslt);
}

// Number <+> Number
Gurax_ImplementOpBinary(Concat, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number in Number
Gurax_ImplementOpBinary(Contains, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL == numR);
}

// Number <^> Number
Gurax_ImplementOpBinary(Cross, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number <-> Number
Gurax_ImplementOpBinary(Difference, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number / Number
Gurax_ImplementOpBinary(Div, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(numL / numR);
}

// Number <.> Number
Gurax_ImplementOpBinary(Dot, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number == Number
Gurax_ImplementOpBinary(Eq, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL == numR);
}

// Number <*> Number
Gurax_ImplementOpBinary(Gear, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number >= Number
Gurax_ImplementOpBinary(Ge, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL >= numR);
}

// Number > Number
Gurax_ImplementOpBinary(Gt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL > numR);
}

// Number <&> Number
Gurax_ImplementOpBinary(Intersection, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <= Number
Gurax_ImplementOpBinary(Le, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL <= numR);
}

// Number < Number
Gurax_ImplementOpBinary(Lt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL < numR);
}

// Number % Number
Gurax_ImplementOpBinary(Mod, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Number(std::fmod(numL, numR));
}

// Number %% Number
Gurax_ImplementOpBinary(ModMod, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::fmod(numL, numR));
}

// Number * Number
Gurax_ImplementOpBinary(Mul, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number != Number
Gurax_ImplementOpBinary(Ne, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL != numR);
}

// Number | Number
Gurax_ImplementOpBinary(Or, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL | numR);
}

// Number => Number
Gurax_ImplementOpBinary(Pair, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number ** Number
Gurax_ImplementOpBinary(Pow, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::pow(numL, numR));
}

// Number .. Number
Gurax_ImplementOpBinary(Seq, Number, Number)
{
	int numL = Value_Number::GetNumber<Int>(valueL);
	int numR = Value_Number::GetNumber<Int>(valueR);
	int idxBegin = 0, idxEnd = 0, idxStep = 0;
	if (numL <= numR) {
		idxBegin = numL, idxEnd = numR + 1, idxStep = 1;
	} else {
		idxBegin = numL, idxEnd = numR - 1, idxStep = -1;
	}
	return new Value_Iterator(new Iterator_Range(idxBegin, idxEnd, idxStep));
}

// Number << Number
Gurax_ImplementOpBinary(Shl, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL << numR);
}

// Number >> Number
Gurax_ImplementOpBinary(Shr, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL >> numR);
}

// Number - Number
Gurax_ImplementOpBinary(Sub, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number ||| Number
Gurax_ImplementOpBinary(Union, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number ^ Number
Gurax_ImplementOpBinary(Xor, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL ^ numR);
}

//------------------------------------------------------------------------------
// VType_Number
//------------------------------------------------------------------------------
VType_Number VTYPE_Number("Number");

void VType_Number::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Number, abs));
	Assign(Gurax_CreateProperty(Number, arg));
	Assign(Gurax_CreateProperty(Number, imag));
	Assign(Gurax_CreateProperty(Number, norm));
	Assign(Gurax_CreateProperty(Number, real));
	// Assignment of operator
	Gurax_AssignOpUnary(Inv,			Number);
	Gurax_AssignOpUnary(Neg,			Number);
	Gurax_AssignOpUnary(Pos,			Number);
	Gurax_AssignOpUnary(PostSeq,		Number);
	Gurax_AssignOpBinary(Add,			Number, Number);
	Gurax_AssignOpBinary(And,			Number, Number);
	Gurax_AssignOpBinary(Cmp,			Number, Number);
	Gurax_AssignOpBinary(Concat,		Number, Number);
	Gurax_AssignOpBinary(Contains,		Number, Number);
	Gurax_AssignOpBinary(Cross,			Number, Number);
	Gurax_AssignOpBinary(Difference,	Number, Number);
	Gurax_AssignOpBinary(Div,			Number, Number);
	Gurax_AssignOpBinary(Dot,			Number, Number);
	Gurax_AssignOpBinary(Eq,			Number, Number);
	Gurax_AssignOpBinary(Gear,			Number, Number);
	Gurax_AssignOpBinary(Ge,			Number, Number);
	Gurax_AssignOpBinary(Gt,			Number, Number);
	Gurax_AssignOpBinary(Intersection,	Number, Number);
	Gurax_AssignOpBinary(Le,			Number, Number);
	Gurax_AssignOpBinary(Lt,			Number, Number);
	Gurax_AssignOpBinary(Mod,			Number, Number);
	Gurax_AssignOpBinary(ModMod,		Number, Number);
	Gurax_AssignOpBinary(Mul,			Number, Number);
	Gurax_AssignOpBinary(Ne,			Number, Number);
	Gurax_AssignOpBinary(Or,			Number, Number);
	Gurax_AssignOpBinary(Pair,			Number, Number);
	Gurax_AssignOpBinary(Pow,			Number, Number);
	Gurax_AssignOpBinary(Seq,			Number, Number);
	Gurax_AssignOpBinary(Shl,			Number, Number);
	Gurax_AssignOpBinary(Shr,			Number, Number);
	Gurax_AssignOpBinary(Sub,			Number, Number);
	Gurax_AssignOpBinary(Union,			Number, Number);
	Gurax_AssignOpBinary(Xor,			Number, Number);
}

//------------------------------------------------------------------------------
// Value_Number
//------------------------------------------------------------------------------
VType& Value_Number::vtype = VTYPE_Number;

String Value_Number::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%g>", GetNumber<Double>());
	return str;
}

String Value_Number::ToStringDetail(const StringStyle& ss) const
{
	String str;
	str.Printf("%g", GetNumber<Double>());
	return str;
}

bool Value_Number::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_d(GetNumber<Int64>(), buff, sizeof(buff)));
}

bool Value_Number::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_u(GetNumber<UInt64>(), buff, sizeof(buff)));
}

bool Value_Number::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_b(GetNumber<UInt64>(), buff, sizeof(buff)));
}

bool Value_Number::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_o(GetNumber<UInt64>(), buff, sizeof(buff)));
}

bool Value_Number::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_x(GetNumber<UInt64>(), buff, sizeof(buff)));
}

bool Value_Number::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_e(GetNumber<Double>(), buff, sizeof(buff)));
}

bool Value_Number::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_f(GetNumber<Double>(), buff, sizeof(buff)));
}

bool Value_Number::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_g(GetNumber<Double>(), buff, sizeof(buff)));
}

bool Value_Number::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutChar(GetNumber<Char>());
}

}
