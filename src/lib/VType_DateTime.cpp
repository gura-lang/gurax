//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// DateTime(year?:Number, month?:Number, day?:Number,
//          hour?:Number, min?:Number, sec?:Number, usec?:Number, minsOff?:Number)
Gurax_DeclareFunction(DateTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareArg("year", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("month", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("day", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("hour", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("min", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("sec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("usec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("minsOff", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `DateTime` instance.");
}

Gurax_ImplementFunction(DateTime)
{
	// Arguments
	ArgPicker args(argument);
	UInt16 year	= args.IsDefined()? args.PickUInt16() : 1970;
	UInt8 month	= args.IsDefined()? args.PickUInt8() : 1;
	UInt8 day	= args.IsDefined()? args.PickUInt8() : 1;
	UInt8 hour	= args.IsDefined()? args.PickUInt8() : 0;
	UInt8 min	= args.IsDefined()? args.PickUInt8() : 0;
	UInt8 sec	= args.IsDefined()? args.PickUInt8() : 0;
	UInt32 usec	= args.IsDefined()? args.PickUInt32() : 0;
	bool validOffsetFlag = args.IsDefined();
	Int32 minsOff = validOffsetFlag? args.PickInt32() : 0;
	// Function body
	RefPtr<DateTime> pDateTime(new DateTime(year, month, day, DateTime::CalcSecInDay(hour, min, sec), usec));
	if (validOffsetFlag) {
		pDateTime->SetMinsOffset(minsOff);
	}
	return new Value_DateTime(pDateTime.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// DateTime#year
Gurax_DeclareProperty_RW(DateTime, year)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The year value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetYear());
}

Gurax_ImplementPropertySetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetYear(Value_Number::GetUInt16(value));
}

// DateTime#month
Gurax_DeclareProperty_RW(DateTime, month)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The month value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, month)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMonth());
}

Gurax_ImplementPropertySetter(DateTime, month)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetMonth(Value_Number::GetUInt8(value));
}

// DateTime#day
Gurax_DeclareProperty_RW(DateTime, day)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The day value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, day)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetDay());
}

Gurax_ImplementPropertySetter(DateTime, day)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetDay(Value_Number::GetUInt8(value));
}

// DateTime#hour
Gurax_DeclareProperty_RW(DateTime, hour)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The hour value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, hour)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetHour());
}

Gurax_ImplementPropertySetter(DateTime, hour)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetHour(Value_Number::GetUInt8(value));
}

// DateTime#min
Gurax_DeclareProperty_RW(DateTime, min)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The minute value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, min)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMin());
}

Gurax_ImplementPropertySetter(DateTime, min)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetMin(Value_Number::GetUInt8(value));
}

// DateTime#sec
Gurax_DeclareProperty_RW(DateTime, sec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The second value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, sec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetSec());
}

Gurax_ImplementPropertySetter(DateTime, sec)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetSec(Value_Number::GetUInt8(value));
}

// DateTime#usec
Gurax_DeclareProperty_RW(DateTime, usec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The micro second value of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetUSec());
}

Gurax_ImplementPropertySetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetDateTime().SetUSec(Value_Number::GetUInt8(value));
}
//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
VType_DateTime VTYPE_DateTime("DateTime");

void VType_DateTime::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(DateTime));
	// Assignment of property
	Assign(Gurax_CreateProperty(DateTime, year));
	Assign(Gurax_CreateProperty(DateTime, month));
	Assign(Gurax_CreateProperty(DateTime, day));
	Assign(Gurax_CreateProperty(DateTime, hour));
	Assign(Gurax_CreateProperty(DateTime, min));
	Assign(Gurax_CreateProperty(DateTime, sec));
	Assign(Gurax_CreateProperty(DateTime, usec));
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------
String Value_DateTime::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetDateTime().ToString(ss);
	str += ">";
	return str;
}

String Value_DateTime::ToStringDetail(const StringStyle& ss) const
{
	return GetDateTime().ToString(ss);
}

}
