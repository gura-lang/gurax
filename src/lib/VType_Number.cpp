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
// Implementation of class property
//------------------------------------------------------------------------------
// Number.int8
Gurax_DeclareClassProperty_R(Number, int8)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for int8.");
}

Gurax_ImplementClassPropertyGetter(Number, int8)
{
	return VTYPE_NumberTrait.pValue_int8->Reference();
}

// Number.uint8
Gurax_DeclareClassProperty_R(Number, uint8)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for uint8.");
}

Gurax_ImplementClassPropertyGetter(Number, uint8)
{
	return VTYPE_NumberTrait.pValue_uint8->Reference();
}

// Number.int16
Gurax_DeclareClassProperty_R(Number, int16)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for int16.");
}

Gurax_ImplementClassPropertyGetter(Number, int16)
{
	return VTYPE_NumberTrait.pValue_int16->Reference();
}

// Number.uint16
Gurax_DeclareClassProperty_R(Number, uint16)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for uint16.");
}

Gurax_ImplementClassPropertyGetter(Number, uint16)
{
	return VTYPE_NumberTrait.pValue_uint16->Reference();
}

// Number.int32
Gurax_DeclareClassProperty_R(Number, int32)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for int32.");
}

Gurax_ImplementClassPropertyGetter(Number, int32)
{
	return VTYPE_NumberTrait.pValue_int32->Reference();
}

// Number.uint32
Gurax_DeclareClassProperty_R(Number, uint32)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for uint32.");
}

Gurax_ImplementClassPropertyGetter(Number, uint32)
{
	return VTYPE_NumberTrait.pValue_uint32->Reference();
}

// Number.int64
Gurax_DeclareClassProperty_R(Number, int64)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for int64.");
}

Gurax_ImplementClassPropertyGetter(Number, int64)
{
	return VTYPE_NumberTrait.pValue_int64->Reference();
}

// Number.uint64
Gurax_DeclareClassProperty_R(Number, uint64)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for uint64.");
}

Gurax_ImplementClassPropertyGetter(Number, uint64)
{
	return VTYPE_NumberTrait.pValue_uint64->Reference();
}

// Number.half
Gurax_DeclareClassProperty_R(Number, half)
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for half.");
}

Gurax_ImplementClassPropertyGetter(Number, half)
{
	return VTYPE_NumberTrait.pValue_half->Reference();
}

// Number.float
Gurax_DeclareClassPropertyAlias_R(Number, float_, "float")
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for float.");
}

Gurax_ImplementClassPropertyGetter(Number, float_)
{
	return VTYPE_NumberTrait.pValue_float->Reference();
}

// Number.double
Gurax_DeclareClassPropertyAlias_R(Number, double_, "double")
{
	Declare(VTYPE_NumberTrait, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Number trait for double.");
}

Gurax_ImplementClassPropertyGetter(Number, double_)
{
	return VTYPE_NumberTrait.pValue_double->Reference();
}

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

// math.Sin(Number)
Gurax_ImplementOpUnary(math_Sin, Number)
{
	Double num = Value_Number::GetNumber<Double>(value);
	return new Value_Number(std::sin(num));
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
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(Number, int8));
	Assign(Gurax_CreateClassProperty(Number, uint8));
	Assign(Gurax_CreateClassProperty(Number, int16));
	Assign(Gurax_CreateClassProperty(Number, uint16));
	Assign(Gurax_CreateClassProperty(Number, int32));
	Assign(Gurax_CreateClassProperty(Number, uint32));
	Assign(Gurax_CreateClassProperty(Number, int64));
	Assign(Gurax_CreateClassProperty(Number, uint64));
	Assign(Gurax_CreateClassProperty(Number, half));
	Assign(Gurax_CreateClassProperty(Number, float_));
	Assign(Gurax_CreateClassProperty(Number, double_));
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
	Gurax_AssignOpBinary(Pow,			Number, Number);
	Gurax_AssignOpBinary(Seq,			Number, Number);
	Gurax_AssignOpBinary(Shl,			Number, Number);
	Gurax_AssignOpBinary(Shr,			Number, Number);
	Gurax_AssignOpBinary(Sub,			Number, Number);
	Gurax_AssignOpBinary(Union,			Number, Number);
	Gurax_AssignOpBinary(Xor,			Number, Number);
	Gurax_AssignOpUnary(math_Sin,		Number);
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
