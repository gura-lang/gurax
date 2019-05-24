//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// DateTime(year?:Number, month?:Number, day?:Number,
//          hour?:Number, min?:Number, sec?:Number, msec?:Number, usec?:Number, minsOff?:Number)
Gurax_DeclareFunction(DateTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareArg("year", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("month", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("day", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("hour", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("min", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("sec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareArg("msec", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
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
	UInt16 msec	= args.IsValid()? args.PickUInt16() : 0;
	UInt16 usec	= args.IsValid()? args.PickUInt16() : 0;
	bool validOffsetFlag = args.IsValid();
	Int32 minsOff = validOffsetFlag? args.PickInt32() : 0;
	// Function body
	RefPtr<DateTime> pDateTime(
		new DateTime(year, month, day, DateTime::CalcSecInDay(hour, min, sec),
					 DateTime::CalcUSecRaw(msec, usec)));
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
	UInt16 num = Value_Number::GetRanged<UInt16>(value, 0, 9999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetYear(num);
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
	UInt8 num = Value_Number::GetRanged<UInt8>(value, 1, 12);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMonth(num);
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
	UInt8 num = Value_Number::GetRanged<UInt8>(value, 1, 31);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetDay(num);
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
	UInt8 num = Value_Number::GetRanged<UInt8>(value, 0, 23);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetHour(num);
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
	UInt8 num = Value_Number::GetRanged<UInt8>(value, 0, 59);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMin(num);
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
	UInt8 num = Value_Number::GetRanged<UInt8>(value, 0, 59);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetSec(num);
}

// DateTime#msec
Gurax_DeclareProperty_RW(DateTime, msec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A number between 0 and 999 that represents the milli-second value of the time.");
}

Gurax_ImplementPropertyGetter(DateTime, msec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMSec());
}

Gurax_ImplementPropertySetter(DateTime, msec)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt16 num = Value_Number::GetRanged<UInt16>(value, 0, 999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMSec(num);
}

// DateTime#usec
Gurax_DeclareProperty_RW(DateTime, usec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"A number between 0 and 999 that represents the micro-second value of the time.");
}

Gurax_ImplementPropertyGetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetUSec());
}

Gurax_ImplementPropertySetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt16 num = Value_Number::GetRanged<UInt16>(value, 0, 999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetUSec(num);
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
		dateTime.SetMinsOffset(Value_Number::Get<Int32>(value));
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
	return new Value_Symbol(valueThis.GetDateTime().GetSymbolOfWeek());
}

// DateTime#weekShort
Gurax_DeclareProperty_R(DateTime, weekShort)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The short symbol that represents the week of the date.");
}

Gurax_ImplementPropertyGetter(DateTime, weekShort)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetDateTime().GetSymbolShortOfWeek());
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

// DateTime#utc
Gurax_DeclareProperty_R(DateTime, utc)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The `DateTime` instance that represents the UTC of the target.");
}

Gurax_ImplementPropertyGetter(DateTime, utc)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_DateTime(valueThis.GetDateTime().ToUTC());
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

// DateTime - DateTime
Gurax_ImplementOpBinary(Sub, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	RefPtr<TimeDelta> pTd(dt1 - dt2);
	return new Value_TimeDelta(pTd.release());
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
	Assign(Gurax_CreateProperty(DateTime, weekShort));
	Assign(Gurax_CreateProperty(DateTime, yday));
	Assign(Gurax_CreateProperty(DateTime, utc));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, DateTime, TimeDelta);
	Gurax_AssignOpBinary(Sub, DateTime, TimeDelta);
	Gurax_AssignOpBinary(Sub, DateTime, DateTime);
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
