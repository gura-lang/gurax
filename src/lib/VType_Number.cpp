//==============================================================================
// VType_Number.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
Gurax_DeclareProperty_R(Number, im)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The imaginary part of the number. Always returns zero.");
}

Gurax_ImplementPropertyGetter(Number, im)
{
	return Value::Zero();
}

Gurax_DeclareProperty_R(Number, re)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The real part of the number. Always returns the number itself.");
}

Gurax_ImplementPropertyGetter(Number, re)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDouble());
}

//------------------------------------------------------------------------------
// VType_Number
//------------------------------------------------------------------------------
VType_Number VTYPE_Number("Number");

void VType_Number::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Number, im));
	Assign(Gurax_CreateProperty(Number, re));
}

//------------------------------------------------------------------------------
// Value_Number
//------------------------------------------------------------------------------
Int Value_Number::GetInt(Int numMin, Int numMax) const
{
	Int num = GetInt();
	if (num < numMin || numMax < num) {
		Error::Issue(ErrorType::RangeError, "the number must be between &d and %d", numMin, numMax);
	}
	return num;
}

String Value_Number::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%g>", GetDouble());
	return str;
}

String Value_Number::ToStringDetail(const StringStyle& ss) const
{
	String str;
	str.Printf("%g", GetDouble());
	return str;
}

bool Value_Number::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_d(GetInt64(), buff, sizeof(buff)));
}

bool Value_Number::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_u(GetUInt64(), buff, sizeof(buff)));
}

bool Value_Number::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_b(GetUInt64(), buff, sizeof(buff)));
}

bool Value_Number::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_o(GetUInt64(), buff, sizeof(buff)));
}

bool Value_Number::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_x(GetUInt64(), buff, sizeof(buff)));
}

bool Value_Number::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_e(GetDouble(), buff, sizeof(buff)));
}

bool Value_Number::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_f(GetDouble(), buff, sizeof(buff)));
}

bool Value_Number::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::Prec::Null) {
		formatterFlags.precision = FormatterFlags::Prec::Default;
	}
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_g(GetDouble(), buff, sizeof(buff)));
}

bool Value_Number::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutChar(GetChar());
}

}
