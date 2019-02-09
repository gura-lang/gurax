//==============================================================================
// Object_Number.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_Number
//------------------------------------------------------------------------------
bool Object_Number::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_d(GetInt64(), buff, sizeof(buff)));
}

bool Object_Number::Format_u(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_u(GetUInt64(), buff, sizeof(buff)));
}

bool Object_Number::Format_b(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_b(GetUInt64(), buff, sizeof(buff)));
}

bool Object_Number::Format_o(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_o(GetUInt64(), buff, sizeof(buff)));
}

bool Object_Number::Format_x(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_x(GetUInt64(), buff, sizeof(buff)));
}

bool Object_Number::Format_e(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_e(GetDouble(), buff, sizeof(buff)));
}

bool Object_Number::Format_f(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_f(GetDouble(), buff, sizeof(buff)));
}

bool Object_Number::Format_g(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	if (formatterFlags.precision == FormatterFlags::PREC_Null) formatterFlags.precision = FormatterFlags::PREC_Default;
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_g(GetDouble(), buff, sizeof(buff)));
}

bool Object_Number::Format_c(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutChar(GetChar());
}

//------------------------------------------------------------------------------
// VType_Number
//------------------------------------------------------------------------------
VType_Number VTYPE_Number("Number");

void VType_Number::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
