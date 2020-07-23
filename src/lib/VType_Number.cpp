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

Number.format

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
// Implementation of property
//------------------------------------------------------------------------------
// Number.formatFloat:String
Gurax_DeclareClassProperty_RW(Number, formatFloat)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert a floating number into a string.");
}

Gurax_ImplementClassPropertyGetter(Number, formatFloat)
{
	return new Value_String(NumberBase::GetFormatterFormat_Float());
}

Gurax_ImplementClassPropertySetter(Number, formatFloat)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::None)) return;
	NumberBase::SetFormatterFormat_Float(format);
}

// Number.formatInt:String
Gurax_DeclareClassProperty_RW(Number, formatInt)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert an integer number into a string.");
}

Gurax_ImplementClassPropertyGetter(Number, formatInt)
{
	return new Value_String(NumberBase::GetFormatterFormat_Int());
}

Gurax_ImplementClassPropertySetter(Number, formatInt)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Int64, Formatter::VaType::None)) return;
	NumberBase::SetFormatterFormat_Int(format);
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
Gurax_ImplementBinary(Add, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number & Number
Gurax_ImplementBinary(And, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <=> Number
Gurax_ImplementBinary(Cmp, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	int rslt = (numL < numR)? -1 : (numL > numR)? +1 : 0;
	return new Value_Number(rslt);
}

// Number <+> Number
Gurax_ImplementBinary(Concat, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number in Number
Gurax_ImplementBinary(Contains, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL == numR);
}

// Number <^> Number
Gurax_ImplementBinary(Cross, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number <-> Number
Gurax_ImplementBinary(Difference, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number / Number
Gurax_ImplementBinary(Div, Number, Number)
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
Gurax_ImplementBinary(Dot, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number == Number
Gurax_ImplementBinary(Eq, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL == numR);
}

// Number <*> Number
Gurax_ImplementBinary(Gear, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number >= Number
Gurax_ImplementBinary(Ge, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL >= numR);
}

// Number > Number
Gurax_ImplementBinary(Gt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL > numR);
}

// Number <&> Number
Gurax_ImplementBinary(Intersection, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL & numR);
}

// Number <= Number
Gurax_ImplementBinary(Le, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL <= numR);
}

// Number < Number
Gurax_ImplementBinary(Lt, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL < numR);
}

// Number % Number
Gurax_ImplementBinary(Mod, Number, Number)
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
Gurax_ImplementBinary(ModMod, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::fmod(numL, numR));
}

// Number * Number
Gurax_ImplementBinary(Mul, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL * numR);
}

// Number != Number
Gurax_ImplementBinary(Ne, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL != numR);
}

// Number | Number
Gurax_ImplementBinary(Or, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL | numR);
}

// Number ** Number
Gurax_ImplementBinary(Pow, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(std::pow(numL, numR));
}

// Number .. Number
Gurax_ImplementBinary(Seq, Number, Number)
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
Gurax_ImplementBinary(Shl, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL << numR);
}

// Number >> Number
Gurax_ImplementBinary(Shr, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL >> numR);
}

// Number - Number
Gurax_ImplementBinary(Sub, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL - numR);
}

// Number ||| Number
Gurax_ImplementBinary(Union, Number, Number)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Number(numL + numR);
}

// Number ^ Number
Gurax_ImplementBinary(Xor, Number, Number)
{
	Int numL = Value_Number::GetNumber<Int>(valueL);
	Int numR = Value_Number::GetNumber<Int>(valueR);
	return new Value_Number(numL ^ numR);
}

//------------------------------------------------------------------------------
// Implementation of suffix manager
//------------------------------------------------------------------------------
Gurax_ImplementSuffixMgr_Compose(Number, f)
{
	bool successFlag = false;
	Double num = strRef.GetStringSTL().ToDouble(&successFlag);
	if (!successFlag) {
		String::IssueError_InvalidFormatOfNumber();
		return;
	}
	composer.Add_Value(new Value_Number(num), *pExpr);							// [Value]
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
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(Number, formatFloat));
	Assign(Gurax_CreateClassProperty(Number, formatInt));
	// Assignment of operator
	Gurax_AssignOpUnary(Inv,		Number);
	Gurax_AssignOpUnary(Neg,		Number);
	Gurax_AssignOpUnary(Pos,		Number);
	Gurax_AssignOpUnary(PostSeq,	Number);
	Gurax_AssignBinary(Add,			Number, Number);
	Gurax_AssignBinary(And,			Number, Number);
	Gurax_AssignBinary(Cmp,			Number, Number);
	Gurax_AssignBinary(Concat,		Number, Number);
	Gurax_AssignBinary(Contains,	Number, Number);
	Gurax_AssignBinary(Cross,		Number, Number);
	Gurax_AssignBinary(Difference,	Number, Number);
	Gurax_AssignBinary(Div,			Number, Number);
	Gurax_AssignBinary(Dot,			Number, Number);
	Gurax_AssignBinary(Eq,			Number, Number);
	Gurax_AssignBinary(Gear,		Number, Number);
	Gurax_AssignBinary(Ge,			Number, Number);
	Gurax_AssignBinary(Gt,			Number, Number);
	Gurax_AssignBinary(Intersection,Number, Number);
	Gurax_AssignBinary(Le,			Number, Number);
	Gurax_AssignBinary(Lt,			Number, Number);
	Gurax_AssignBinary(Mod,			Number, Number);
	Gurax_AssignBinary(ModMod,		Number, Number);
	Gurax_AssignBinary(Mul,			Number, Number);
	Gurax_AssignBinary(Ne,			Number, Number);
	Gurax_AssignBinary(Or,			Number, Number);
	Gurax_AssignBinary(Pow,			Number, Number);
	Gurax_AssignBinary(Seq,			Number, Number);
	Gurax_AssignBinary(Shl,			Number, Number);
	Gurax_AssignBinary(Shr,			Number, Number);
	Gurax_AssignBinary(Sub,			Number, Number);
	Gurax_AssignBinary(Union,		Number, Number);
	Gurax_AssignBinary(Xor,			Number, Number);
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Number, f);
}

Value* VType_Number::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Rational)) {
		return new Value_Number(Value_Rational::GetRational(value).ToDouble());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Number
//------------------------------------------------------------------------------
VType& Value_Number::vtype = VTYPE_Number;

String Value_Number::ToString(const StringStyle& ss) const
{
	String strEntity = Number<Double>::ToString(GetNumber<Double>());
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
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
