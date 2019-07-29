//==============================================================================
// VType_Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Complex(real:Number, imag?:Number):map {block?}
Gurax_DeclareFunction(Complex)
{
	Declare(VTYPE_Complex, Flag::Map);
	DeclareArg("real", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imag", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Complex` instance.");
}

Gurax_ImplementFunction(Complex)
{
	// Arguments
	ArgPicker args(argument);
	Double real = args.PickNumber<Double>();
	Double imag = args.IsValid()? args.PickNumber<Double>() : 0;
	// Function body
	return ReturnValue(processor, argument, new Value_Complex(Complex(real, imag)));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Complex#abs
Gurax_DeclareProperty_R(Complex, abs)
{
	Declare(VTYPE_Complex, Flag::None);
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
	Declare(VTYPE_Complex, Flag::None);
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
	Declare(VTYPE_Complex, Flag::None);
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
	Declare(VTYPE_Complex, Flag::None);
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
	Declare(VTYPE_Complex, Flag::None);
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
// VType_Complex
//------------------------------------------------------------------------------
VType_Complex VTYPE_Complex("Complex");

void VType_Complex::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Complex));
	// Assignment of property
	Assign(Gurax_CreateProperty(Complex, abs));
	Assign(Gurax_CreateProperty(Complex, arg));
	Assign(Gurax_CreateProperty(Complex, imag));
	Assign(Gurax_CreateProperty(Complex, norm));
	Assign(Gurax_CreateProperty(Complex, real));
}

//------------------------------------------------------------------------------
// Value_Complex
//------------------------------------------------------------------------------
String Value_Complex::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	const Complex& num = GetComplex();
	if (num.imag() > 0) {
		str.Printf(":%g+%gj>", num.real(), num.imag());
	} else if (num.imag() < 0) {
		str.Printf(":%g%gj>", num.real(), num.imag());
	} else {
		str.Printf(":%g>", num.real());
	}
	return str;
}

String Value_Complex::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
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
	nums.reserve(values.size());
	for (Value* pValue : values) {
		nums.push_back(GetComplex(*pValue));
	}
	return nums;
}

}
