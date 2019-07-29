//==============================================================================
// VType_Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Complex(re:Number, im?:Number):map {block?}
Gurax_DeclareFunction(Complex)
{
	Declare(VTYPE_Complex, Flag::Map);
	DeclareArg("re", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("im", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Complex` instance.");
}

Gurax_ImplementFunction(Complex)
{
	// Arguments
	ArgPicker args(argument);
	Double re = args.PickNumber<Double>();
	Double im = args.IsValid()? args.PickNumber<Double>() : 0;
	// Function body
	return ReturnValue(processor, argument, new Value_Complex(Complex(re, im)));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(Complex, im)
{
	Declare(VTYPE_Complex, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The imaginary part of the Complex value.");
}

Gurax_ImplementPropertyGetter(Complex, im)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetComplex().imag());
}

Gurax_DeclareProperty_R(Complex, re)
{
	Declare(VTYPE_Complex, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The real part of the Complex Value.");
}

Gurax_ImplementPropertyGetter(Complex, re)
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
	Assign(Gurax_CreateProperty(Complex, im));
	Assign(Gurax_CreateProperty(Complex, re));
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
