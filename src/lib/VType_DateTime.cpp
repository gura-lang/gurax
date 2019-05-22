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
	UInt16 year	= args.IsValid()? args.PickUInt16() : 1970;
	UInt8 month	= args.IsValid()? args.PickUInt8() : 1;
	UInt8 day	= args.IsValid()? args.PickUInt8() : 1;
	UInt8 hour	= args.IsValid()? args.PickUInt8() : 0;
	UInt8 min	= args.IsValid()? args.PickUInt8() : 0;
	UInt8 sec	= args.IsValid()? args.PickUInt8() : 0;
	UInt32 usec	= args.IsValid()? args.PickUInt32() : 0;
	bool validOffsetFlag = args.IsValid();
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
		"A number between 1 and 12 that represents the month value of the date.");
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
		"A number between 1 and 31 that represents the day value of the date.");
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
		"A number between 0 and 23 that represents the hour value the time.");
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
		"A number between 0 and 59 that represents the minute value of the time.");
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
		"A number between 0 and 59 that represents the second value of the time.");
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
		"A number between 0 and 999999 that represents the micro-second value of the time.");
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

// DateTime#minsOff
Gurax_DeclareProperty_RW(DateTime, minsOff)
{
	Declare(VTYPE_Number, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"The time-zone offset of the time in minute.\n"
		"Returns `nil` if the `DateTime` instance has no information about time offset. ");
}

Gurax_ImplementPropertyGetter(DateTime, minsOff)
{
	auto& valueThis = GetValueThis(valueTarget);
	const DateTime& dateTime = valueThis.GetDateTime();
	return dateTime.HasOffset()? new Value_Number(dateTime.GetMinsOffset()) : Value::nil();
}

Gurax_ImplementPropertySetter(DateTime, minsOff)
{
	auto& valueThis = GetValueThis(valueTarget);
	DateTime& dateTime = valueThis.GetDateTime();
	if (value.IsValid()) {
		dateTime.SetMinsOffset(Value_Number::GetInt32(value));
	} else {
		dateTime.InvalidateOffset();
	}
}

// DateTime#wday
Gurax_DeclareProperty_R(DateTime, wday)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A number from 0 to 6 that corresponds to the week of the date from Sunday to Saturday.");
}

Gurax_ImplementPropertyGetter(DateTime, wday)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetDayOfWeek());
}

// DateTime#week
Gurax_DeclareProperty_R(DateTime, week)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The symbol that represents the week of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, week)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 dayOfWeek = valueThis.GetDateTime().GetDayOfWeek();
	const Symbol *pSymbol =
		(dayOfWeek == 0)? Gurax_Symbol(sunday) :
		(dayOfWeek == 1)? Gurax_Symbol(monday) :
		(dayOfWeek == 2)? Gurax_Symbol(tuesday) :
		(dayOfWeek == 3)? Gurax_Symbol(wednesday) :
		(dayOfWeek == 4)? Gurax_Symbol(thursday) :
		(dayOfWeek == 5)? Gurax_Symbol(friday) :
		(dayOfWeek == 6)? Gurax_Symbol(saturday) : Symbol::Empty;
	return new Value_Symbol(pSymbol);
}

// DateTime#yday
Gurax_DeclareProperty_R(DateTime, yday)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The day offset from the beginning of the year that starts from zero.");
}

Gurax_ImplementPropertyGetter(DateTime, yday)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetDayOfYear());
}

//------------------------------------------------------------------------------
// Operator
//------------------------------------------------------------------------------
// DateTime + TimeDelta
Gurax_ImplementOpBinary(Add, DateTime, TimeDelta)
{
	const DateTime& dt = Value_DateTime::GetDateTime(valueL);
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<DateTime> pDt(new DateTime(dt));
	*pDt += td;
	return new Value_DateTime(pDt.release());
}

// DateTime - TimeDelta
Gurax_ImplementOpBinary(Sub, DateTime, TimeDelta)
{
	const DateTime& dt = Value_DateTime::GetDateTime(valueL);
	const TimeDelta& td = Value_TimeDelta::GetTimeDelta(valueR);
	RefPtr<DateTime> pDt(new DateTime(dt));
	*pDt -= td;
	return new Value_DateTime(pDt.release());
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
	Assign(Gurax_CreateProperty(DateTime, minsOff));
	Assign(Gurax_CreateProperty(DateTime, wday));
	Assign(Gurax_CreateProperty(DateTime, week));
	Assign(Gurax_CreateProperty(DateTime, yday));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, DateTime, TimeDelta);
	Gurax_AssignOpBinary(Sub, DateTime, TimeDelta);
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
