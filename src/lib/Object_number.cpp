//==============================================================================
// Object_number.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_number
//------------------------------------------------------------------------------
bool Object_number::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_d(GetInt64(), buff, sizeof(buff)));
}

bool Object_number::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_u(GetUInt64(), buff, sizeof(buff)));
}

bool Object_number::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_b(GetUInt64(), buff, sizeof(buff)));
}

bool Object_number::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_o(GetUInt64(), buff, sizeof(buff)));
}

bool Object_number::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_x(GetUInt64(), buff, sizeof(buff)));
}

bool Object_number::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_e(GetDouble(), buff, sizeof(buff)));
}

bool Object_number::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_f(GetDouble(), buff, sizeof(buff)));
}

bool Object_number::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_g(GetDouble(), buff, sizeof(buff)));
}

bool Object_number::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutChar(GetChar());
}

//------------------------------------------------------------------------------
// Object_number::KlassEx
//------------------------------------------------------------------------------
Object_number::KlassEx Object_number::klass("number");

void Object_number::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
