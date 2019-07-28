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
	//str.Printf(":%g>", GetComplex<Double>());
	return str;
}

String Value_Complex::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str.Printf("%g", GetComplex<Double>());
	return str;
}

bool Value_Complex::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
#if 0
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_e(GetComplex<Double>(), buff, sizeof(buff)));
#endif
	return false;
}

bool Value_Complex::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
#if 0
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_f(GetComplex<Double>(), buff, sizeof(buff)));
#endif
	return false;
}

bool Value_Complex::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
#if 0
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatComplex_g(GetComplex<Double>(), buff, sizeof(buff)));
#endif
	return false;
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
