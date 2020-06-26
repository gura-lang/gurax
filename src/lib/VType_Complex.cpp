//==============================================================================
// VType_Complex.cpp
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
// Implementation of constructor
//------------------------------------------------------------------------------
// Complex(real:Number, imag?:Number):map {block?}
Gurax_DeclareConstructor(Complex)
{
	Declare(VTYPE_Complex, Flag::Map);
	DeclareArg("real", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imag", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Complex` instance.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert a complex number into a string.");
}

Gurax_ImplementClassPropertyGetter(Complex, format)
{
	return new Value_String(Complex::GetFormatterFormat());
}

Gurax_ImplementClassPropertySetter(Complex, format)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::Float,
			Formatter::VaType::None)) return;
	Complex::SetFormatterFormat(format);
}

// Complex.formatImag:String
Gurax_DeclareClassProperty_RW(Complex, formatImag)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert the Imag part of a complex number into a string.");
}

Gurax_ImplementClassPropertyGetter(Complex, formatImag)
{
	return new Value_String(Complex::GetFormatterFormat_Imag());
}

Gurax_ImplementClassPropertySetter(Complex, formatImag)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::None)) return;
	Complex::SetFormatterFormat_Imag(format);
}

// Complex.formatReal:String
Gurax_DeclareClassProperty_RW(Complex, formatReal)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Format string used to convert the real part of a complex number into a string.");
}

Gurax_ImplementClassPropertyGetter(Complex, formatReal)
{
	return new Value_String(Complex::GetFormatterFormat_Real());
}

Gurax_ImplementClassPropertySetter(Complex, formatReal)
{
	const String& format = Value_String::GetStringSTL(value);
	if (!Formatter().VerifyFormat(format.c_str(),
			Formatter::VaType::Float, Formatter::VaType::None)) return;
	Complex::SetFormatterFormat_Real(format);
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Complex#abs
Gurax_DeclareProperty_R(Complex, abs)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The absolute value of the number.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The argument value of the number. Always returns zero.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The imaginary part of the Complex value.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The norm value of the number.");
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
	AddHelp(
		Gurax_Symbol(en),
		"The real part of the Complex Value.");
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
Gurax_ImplementBinary(Add, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL + numR);
}

// Complex + Number
Gurax_ImplementBinary(Add, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL + numR);
}

// Number + Complex
Gurax_ImplementBinary(Add, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL + numR);
}

// Complex == Complex
Gurax_ImplementBinary(Eq, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL == numR);
}

// Complex == Number
Gurax_ImplementBinary(Eq, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL == numR);
}

// Number == Complex
Gurax_ImplementBinary(Eq, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL == numR);
}

// Complex / Complex
Gurax_ImplementBinary(Div, Complex, Complex)
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
Gurax_ImplementBinary(Div, Complex, Number)
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
Gurax_ImplementBinary(Div, Number, Complex)
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
Gurax_ImplementBinary(Mul, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL * numR);
}

// Complex * Number
Gurax_ImplementBinary(Mul, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL * numR);
}

// Number * Complex
Gurax_ImplementBinary(Mul, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL * numR);
}

// Complex != Complex
Gurax_ImplementBinary(Ne, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL != numR);
}

// Complex != Number
Gurax_ImplementBinary(Ne, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Bool(numL != numR);
}

// Number != Complex
Gurax_ImplementBinary(Ne, Number, Complex)
{
	Double numL = Value_Number::GetNumber<Double>(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Bool(numL != numR);
}

// Complex - Complex
Gurax_ImplementBinary(Sub, Complex, Complex)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	const Complex& numR = Value_Complex::GetComplex(valueR);
	return new Value_Complex(numL - numR);
}

// Complex - Number
Gurax_ImplementBinary(Sub, Complex, Number)
{
	const Complex& numL = Value_Complex::GetComplex(valueL);
	Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_Complex(numL - numR);
}

// Number - Complex
Gurax_ImplementBinary(Sub, Number, Complex)
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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
	Gurax_AssignBinary(Add,	Complex, Complex);
	Gurax_AssignBinary(Add,	Complex, Number);
	Gurax_AssignBinary(Add,	Number, Complex);
	Gurax_AssignBinary(Div,	Complex, Complex);
	Gurax_AssignBinary(Div,	Complex, Number);
	Gurax_AssignBinary(Div,	Number, Complex);
	Gurax_AssignBinary(Eq,	Complex, Complex);
	Gurax_AssignBinary(Eq,	Complex, Number);
	Gurax_AssignBinary(Eq,	Number, Complex);
	Gurax_AssignBinary(Mul,	Complex, Complex);
	Gurax_AssignBinary(Mul,	Complex, Number);
	Gurax_AssignBinary(Mul,	Number, Complex);
	Gurax_AssignBinary(Ne,	Complex, Complex);
	Gurax_AssignBinary(Ne,	Complex, Number);
	Gurax_AssignBinary(Ne,	Number, Complex);
	Gurax_AssignBinary(Sub,	Complex, Complex);
	Gurax_AssignBinary(Sub,	Complex, Number);
	Gurax_AssignBinary(Sub,	Number, Complex);
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
	String strEntity = GetComplex().ToString(ss);
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

bool Value_Complex::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	formatterFlags.FormatNumber_e(GetComplex().real(), buff, sizeof(buff));
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	formatterFlags.FormatNumber_e(GetComplex().imag(), buff, sizeof(buff));
	::strcat(buff, "j");
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	return true;
}

bool Value_Complex::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	formatterFlags.FormatNumber_f(GetComplex().real(), buff, sizeof(buff));
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	formatterFlags.FormatNumber_f(GetComplex().imag(), buff, sizeof(buff));
	::strcat(buff, "j");
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	return true;
}

bool Value_Complex::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	formatterFlags.FormatNumber_g(GetComplex().real(), buff, sizeof(buff));
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	formatterFlags.FormatNumber_g(GetComplex().imag(), buff, sizeof(buff));
	::strcat(buff, "j");
	if (!formatter.PutAlignedString(formatterFlags, buff)) return false;
	return true;
}

ComplexList Value_Complex::GetComplexList(const ValueList& values)
{
	ComplexList nums;
	nums.v.reserve(values.size());
	for (Value* pValue : values) {
		nums.v.push_back(GetComplex(*pValue));
	}
	return nums;
}

}
