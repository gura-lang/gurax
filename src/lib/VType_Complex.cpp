//==============================================================================
// VType_Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(Complex, im)
{
	Declare(VTYPE_Complex, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The imaginary part of the number. Always returns zero.");
}

Gurax_ImplementPropertyGetter(Complex, im)
{
	return Value::Zero();
}

Gurax_DeclareProperty_R(Complex, re)
{
	Declare(VTYPE_Complex, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The real part of the number. Always returns the number itself.");
}

Gurax_ImplementPropertyGetter(Complex, re)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Complex(valueThis.GetComplex<Double>());
}

//------------------------------------------------------------------------------
// VType_Complex
//------------------------------------------------------------------------------
VType_Complex VTYPE_Complex("Complex");

void VType_Complex::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
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
	str.Printf(":%g>", GetComplex<Double>());
	return str;
}

String Value_Complex::ToStringDetail(const StringStyle& ss) const
{
	String str;
	str.Printf("%g", GetComplex<Double>());
	return str;
}

bool Value_Complex::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_d(GetComplex<Int64>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_u(GetComplex<UInt64>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_b(GetComplex<UInt64>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_o(GetComplex<UInt64>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_x(GetComplex<UInt64>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_e(GetComplex<Double>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_f(GetComplex<Double>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_g(GetComplex<Double>(), buff, sizeof(buff)));
}

bool Value_Complex::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutChar(GetComplex<Char>());
}

}
