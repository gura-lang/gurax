//==============================================================================
// VType_Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

${help.ComposePropertyHelp(Complex, `en)}

# Operator

The following operations are prepared:

- `-Complex` ... Calculates a negative value of `Complex`.
- `+Complex` ... Calculates a positive value of `Complex`.
- `Complex + Complex` ... Calculates the addition.
- `Complex + Number` ... Calculates the addition.
- `Number + Complex` ... Calculates the addition.
- `Complex / Complex` ... Calculates the division.
- `Complex / Number` ... Calculates the division.
- `Number / Complex` ... Calculates the division.
- `Complex == Complex` ... Returns `true` if the left-sided `Complex` is equal to the right-sided `Complex`. 
- `Complex == Number` ... Returns `true` if the left-sided `Complex` is equal to the right-sided `Number`.
- `Number == Complex` ... Returns `true` if the left-sided `Number` is equal to the right-sided `Complex`. 
- `Complex * Complex` ... Calculates the multiplication.
- `Complex * Number` ... Calculates the multiplication.
- `Number * Complex` ... Calculates the multiplication.
- `Complex != Complex` ... Returns `true` if the left-sided `Complex` is not equal to the right-sided `Complex`.
- `Complex != Number` ... Returns `true` if the left-sided `Complex` is not equal to the right-sided `Number`.
- `Number != Complex` ... Returns `true` if the left-sided `Number` is not equal to the right-sided `Complex`.
- `Complex - Complex` ... Calculates the subtraction.
- `Complex - Number` ... Calculates the subtraction.
- `Number - Complex` ... Calculates the subtraction.

# Cast Operation

The following cast operations are prepared:

^ `Number` as `Complex` ... Creates a `Complex` from the `Number`.

${help.ComposeConstructorHelp(Complex, `en)}

${help.ComposeMethodHelp(Complex, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Complex(real as Number, imag? as Number):map {block?}
Gurax_DeclareConstructor(Complex)
{
	Declare(VTYPE_Complex, Flag::Map);
	DeclareArg("real", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("imag", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Complex` instance.
)""");
}

Gurax_ImplementConstructor(Complex)
{
	// Arguments
	ArgPicker args(argument);
	Double real = args.PickNumber<Double>();
	Double imag = args.IsValid()? args.PickNumber<Double>() : 0;
	// Function body
	return argument.ReturnValue(processor, new Value_Complex(Complex(real, imag)));
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// Complex.format:String
Gurax_DeclareClassProperty_RW(Complex, format)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Format string used to convert a complex number into a string.
)""");
}

Gurax_ImplementClassPropertyGetter(Complex, format)
{
	return new Value_String(Complex::formatterFormat);
}

Gurax_ImplementClassPropertySetter(Complex, format)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::Float,
			Formatter::VaType::None)) return;
	Complex::formatterFormat = format;
}

// Complex.formatImag:String
Gurax_DeclareClassProperty_RW(Complex, formatImag)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Format string used to convert the Imag part of a complex number into a string.
)""");
}

Gurax_ImplementClassPropertyGetter(Complex, formatImag)
{
	return new Value_String(Complex::formatterFormat_Imag);
}

Gurax_ImplementClassPropertySetter(Complex, formatImag)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::None)) return;
	Complex::formatterFormat_Imag = format;
}

// Complex.formatReal:String
Gurax_DeclareClassProperty_RW(Complex, formatReal)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Format string used to convert the real part of a complex number into a string.
)""");
}

Gurax_ImplementClassPropertyGetter(Complex, formatReal)
{
	return new Value_String(Complex::formatterFormat_Real);
}

Gurax_ImplementClassPropertySetter(Complex, formatReal)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::None)) return;
	Complex::formatterFormat_Real = format;
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Complex#abs
Gurax_DeclareProperty_R(Complex, abs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The absolute value of the number.
)""");
}

Gurax_ImplementPropertyGetter(Complex, abs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(std::abs(valueThis.GetComplex()));
}

// Complex#arg
Gurax_DeclareProperty_R(Complex, arg)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The argument value of the number. Always returns zero.
)""");
}

Gurax_ImplementPropertyGetter(Complex, arg)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(std::arg(valueThis.GetComplex()));
}

// Complex#imag
Gurax_DeclareProperty_R(Complex, imag)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The imaginary part of the Complex value.
)""");
}

Gurax_ImplementPropertyGetter(Complex, imag)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetComplex().imag());
}

// Complex#norm
Gurax_DeclareProperty_R(Complex, norm)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The norm value of the number.
)""");
}

Gurax_ImplementPropertyGetter(Complex, norm)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(std::norm(valueThis.GetComplex()));
}

// Complex#real
Gurax_DeclareProperty_R(Complex, real)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The real part of the Complex Value.
)""");
}

Gurax_ImplementPropertyGetter(Complex, real)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetComplex().real());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// -Complex
Gurax_ImplementOpUnary(Neg, Complex)
{
	const Complex& num = Value_Complex::GetComplex(value);
	return new Value_Complex(-num);
}

// +Complex
Gurax_ImplementOpUnary(Pos, Complex)
{
	return value.Clone();
}

// Complex + Complex
Gurax_ImplementOpBinary(Add, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL + numR);
}

// Complex + Number
Gurax_ImplementOpBinary(Add, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL + numR);
}

// Number + Complex
Gurax_ImplementOpBinary(Add, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL + numR);
}

// Complex == Complex
Gurax_ImplementOpBinary(Eq, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL == numR);
}

// Complex == Number
Gurax_ImplementOpBinary(Eq, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL == numR);
}

// Number == Complex
Gurax_ImplementOpBinary(Eq, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL == numR);
}

// Complex / Complex
Gurax_ImplementOpBinary(Div, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	if (numR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Complex(numL / numR);
}

// Complex / Number
Gurax_ImplementOpBinary(Div, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	if (numR == 0.) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Complex(numL / numR);
}

// Number / Complex
Gurax_ImplementOpBinary(Div, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	if (numR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return Value::undefined();
	}
	return new Value_Complex(numL / numR);
}

// Complex * Complex
Gurax_ImplementOpBinary(Mul, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL * numR);
}

// Complex * Number
Gurax_ImplementOpBinary(Mul, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL * numR);
}

// Number * Complex
Gurax_ImplementOpBinary(Mul, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL * numR);
}

// Complex != Complex
Gurax_ImplementOpBinary(Ne, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL != numR);
}

// Complex != Number
Gurax_ImplementOpBinary(Ne, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL != numR);
}

// Number != Complex
Gurax_ImplementOpBinary(Ne, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL != numR);
}

// Complex - Complex
Gurax_ImplementOpBinary(Sub, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL - numR);
}

// Complex - Number
Gurax_ImplementOpBinary(Sub, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL - numR);
}

// Number - Complex
Gurax_ImplementOpBinary(Sub, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL - numR);
}

//------------------------------------------------------------------------------
// Implementation of suffix manager
//------------------------------------------------------------------------------
Gurax_ImplementSuffixMgr_Compose(Number, j)
{
	bool successFlag = false;
	Double num = strRef.GetStringSTL().ToDouble(&successFlag);
	if (!successFlag) {
		String::IssueError_InvalidFormatOfNumber();
		return;
	}
	composer.Add_Value(new Value_Complex(Complex(0, num)), *pExpr);				// [Value]
}

//------------------------------------------------------------------------------
// VType_Complex
//------------------------------------------------------------------------------
VType_Complex VTYPE_Complex("Complex");

void VType_Complex::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Complex));
	// Assignment of class property
	Assign(Gurax_CreateProperty(Complex, format));
	Assign(Gurax_CreateProperty(Complex, formatImag));
	Assign(Gurax_CreateProperty(Complex, formatReal));
	// Assignment of property
	Assign(Gurax_CreateProperty(Complex, abs));
	Assign(Gurax_CreateProperty(Complex, arg));
	Assign(Gurax_CreateProperty(Complex, imag));
	Assign(Gurax_CreateProperty(Complex, norm));
	Assign(Gurax_CreateProperty(Complex, real));
	// Assignment of operator
	Gurax_AssignOpUnary(Neg,	Complex);
	Gurax_AssignOpUnary(Pos,	Complex);
	Gurax_AssignOpBinary(Add,	Complex, Complex);
	Gurax_AssignOpBinary(Add,	Complex, Number);
	Gurax_AssignOpBinary(Add,	Number, Complex);
	Gurax_AssignOpBinary(Div,	Complex, Complex);
	Gurax_AssignOpBinary(Div,	Complex, Number);
	Gurax_AssignOpBinary(Div,	Number, Complex);
	Gurax_AssignOpBinary(Eq,	Complex, Complex);
	Gurax_AssignOpBinary(Eq,	Complex, Number);
	Gurax_AssignOpBinary(Eq,	Number, Complex);
	Gurax_AssignOpBinary(Mul,	Complex, Complex);
	Gurax_AssignOpBinary(Mul,	Complex, Number);
	Gurax_AssignOpBinary(Mul,	Number, Complex);
	Gurax_AssignOpBinary(Ne,	Complex, Complex);
	Gurax_AssignOpBinary(Ne,	Complex, Number);
	Gurax_AssignOpBinary(Ne,	Number, Complex);
	Gurax_AssignOpBinary(Sub,	Complex, Complex);
	Gurax_AssignOpBinary(Sub,	Complex, Number);
	Gurax_AssignOpBinary(Sub,	Number, Complex);
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Number, j);
}

Value* VType_Complex::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Number)) {
		return new Value_Complex(Complex(Value_Number::GetNumber<Double>(value)));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Complex
//------------------------------------------------------------------------------
VType& Value_Complex::vtype = VTYPE_Complex;

String Value_Complex::ToString(const StringStyle& ss) const
{
	String strEntity = GetComplex().ToString();
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

bool Value_Complex::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	Double real = GetComplex().real();
	Double imag = GetComplex().imag();
	if (real != 0. || imag == 0.) {
		formatterFlags.FormatNumber_e(real, buff, sizeof(buff));
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	if (imag != 0.) {
		if (real != 0. && imag > 0.) formatter.PutChar('+');
		formatterFlags.FormatNumber_e(imag, buff, sizeof(buff));
		::strcat(buff, "j");
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	return true;
}

bool Value_Complex::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	Double real = GetComplex().real();
	Double imag = GetComplex().imag();
	if (real != 0. || imag == 0.) {
		formatterFlags.FormatNumber_f(real, buff, sizeof(buff));
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	if (imag != 0.) {
		if (real != 0. && imag > 0.) formatter.PutChar('+');
		formatterFlags.FormatNumber_f(imag, buff, sizeof(buff));
		::strcat(buff, "j");
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	return true;
}

bool Value_Complex::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	Double real = GetComplex().real();
	Double imag = GetComplex().imag();
	if (real != 0. || imag == 0.) {
		formatterFlags.FormatNumber_g(real, buff, sizeof(buff));
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	if (imag != 0.) {
		if (real != 0. && imag > 0.) formatter.PutChar('+');
		formatterFlags.FormatNumber_g(imag, buff, sizeof(buff));
		::strcat(buff, "j");
		if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	}
	return true;
}

ComplexList Value_Complex::GetComplexList(const ValueList& values)
{
	ComplexList nums;
	nums.reserve(values.size());
	for (Value* pValue : values) {
		nums.push_back(GetComplex(*pValue));
	}
	return nums;
}

bool Value_Complex::DoSerialize(Stream& stream) const
{
	return stream.SerializeComplex(_num);
}

Value* VType_Complex::DoDeserialize(Stream& stream) const
{
	Complex num;
	if (!stream.DeserializeComplex(num)) return nullptr;
	return new Value_Complex(num);
}

}
