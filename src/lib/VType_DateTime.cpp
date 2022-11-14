//==============================================================================
// VType_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(DateTime, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(DateTime, `en)}

${help.ComposeMethodHelp(DateTime, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// DateTime(str? as String):map:[utc] {block?}
Gurax_DeclareConstructor(DateTime)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(utc));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `DateTime` instance.
)**");
}

Gurax_ImplementConstructor(DateTime)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.IsValid()? args.PickString() : nullptr;
	bool utcFlag = argument.IsSet(Gurax_Symbol(utc));
	// Function body
	RefPtr<DateTime> pDt(str? DateTime::CreateFromString(str) : new DateTime());
	if (!pDt) {
		Error::Issue(ErrorType::FormatError, "invalid format for DateTime");
		return Value::nil();
	}
	if (utcFlag) pDt.reset(pDt->ToUTC());
	return argument.ReturnValue(processor, new Value_DateTime(pDt.release()));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// DateTime.Create(year? as Number, month? as Number, day? as Number,
//     hour? as Number, min? as Number, sec? as Number, msec? as Number, usec? as Number, minsOff? as Number):map {block?}
Gurax_DeclareClassMethod(DateTime, Create)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("year", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("month", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("hour", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("sec", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("msec", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("usec", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("minsOff", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `DateTime` instance.
)**");
}

Gurax_ImplementClassMethod(DateTime, Create)
{
	// Arguments
	ArgPicker args(argument);
	Int16 year	= args.IsValid()? args.PickNumberRanged<Int16>(0, 9999) : 1970;
	Int8 month	= args.IsValid()? args.PickNumberRanged<Int8>(1, 12) : 1;
	Int8 day	= args.IsValid()? args.PickNumberRanged<Int8>(1, 31) : 1;
	Int8 hour	= args.IsValid()? args.PickNumberRanged<Int8>(0, 23) : 0;
	Int8 min	= args.IsValid()? args.PickNumberRanged<Int8>(0, 59) : 0;
	Int8 sec	= args.IsValid()? args.PickNumberRanged<Int8>(0, 59) : 0;
	Int16 msec	= args.IsValid()? args.PickNumberRanged<Int16>(0, 999) : 0;
	Int16 usec	= args.IsValid()? args.PickNumberRanged<Int16>(0, 999) : 0;
	bool validOffsetFlag = args.IsValid();
	Int32 minsOff = validOffsetFlag? args.PickNumber<Int32>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<DateTime> pDt(
		new DateTime(year, month, day, DateTime::CalcSecPacked(hour, min, sec),
					 DateTime::CalcUSecPacked(msec, usec)));
	if (validOffsetFlag) {
		pDt->SetMinsOffset(minsOff);
	}
	return argument.ReturnValue(processor, new Value_DateTime(pDt.release()));
}

// DateTime.Now():[utc] {block?}
Gurax_DeclareClassMethod(DateTime, Now)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(utc));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethod(DateTime, Now)
{
	// Arguments
	bool utcFlag = argument.IsSet(Gurax_Symbol(utc));
	// Function body
	RefPtr<DateTime> pDt(OAL::CreateDateTimeCur(utcFlag));
	return argument.ReturnValue(processor, new Value_DateTime(pDt.release()));
}

// DateTime.FromUnixTime(unixTime as Number):[utc] {block?}
Gurax_DeclareClassMethod(DateTime, FromUnixTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	DeclareArg("unixTime", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(utc));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementClassMethod(DateTime, FromUnixTime)
{
	// Arguments
	ArgPicker args(argument);
	time_t unixTime = args.PickNumberNonNeg<time_t>();
	bool utcFlag = argument.IsSet(Gurax_Symbol(utc));
	// Function body
	RefPtr<DateTime> pDt(OAL::CreateDateTime(unixTime, utcFlag));
	return argument.ReturnValue(processor, new Value_DateTime(pDt.release()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// DateTime#year
Gurax_DeclareProperty_RW(DateTime, year)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The year value of the date.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetYear());
}

Gurax_ImplementPropertySetter(DateTime, year)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int16 num = Value_Number::GetNumberRanged<Int16>(value, 0, 9999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetYear(num);
}

// DateTime#month
Gurax_DeclareProperty_RW(DateTime, month)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 1 and 12 that represents the month value of the date.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, month)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMonth());
}

Gurax_ImplementPropertySetter(DateTime, month)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int8 num = Value_Number::GetNumberRanged<Int8>(value, 1, 12);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMonth(num);
}

// DateTime#day
Gurax_DeclareProperty_RW(DateTime, day)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 1 and 31 that represents the day value of the date.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, day)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetDay());
}

Gurax_ImplementPropertySetter(DateTime, day)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int8 num = Value_Number::GetNumberRanged<Int8>(value, 1, 31);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetDay(num);
}

// DateTime#hour
Gurax_DeclareProperty_RW(DateTime, hour)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 0 and 23 that represents the hour value the time.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, hour)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetHour());
}

Gurax_ImplementPropertySetter(DateTime, hour)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int8 num = Value_Number::GetNumberRanged<Int8>(value, 0, 23);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetHour(num);
}

// DateTime#min
Gurax_DeclareProperty_RW(DateTime, min)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 0 and 59 that represents the minute value of the time.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, min)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMin());
}

Gurax_ImplementPropertySetter(DateTime, min)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int8 num = Value_Number::GetNumberRanged<Int8>(value, 0, 59);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMin(num);
}

// DateTime#sec
Gurax_DeclareProperty_RW(DateTime, sec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 0 and 59 that represents the second value of the time.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, sec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetSec());
}

Gurax_ImplementPropertySetter(DateTime, sec)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int8 num = Value_Number::GetNumberRanged<Int8>(value, 0, 59);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetSec(num);
}

// DateTime#msec
Gurax_DeclareProperty_RW(DateTime, msec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 0 and 999 that represents the milli-second value of the time.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, msec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetMSec());
}

Gurax_ImplementPropertySetter(DateTime, msec)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int16 num = Value_Number::GetNumberRanged<Int16>(value, 0, 999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetMSec(num);
}

// DateTime#usec
Gurax_DeclareProperty_RW(DateTime, usec)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number between 0 and 999 that represents the micro-second value of the time.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().GetUSec());
}

Gurax_ImplementPropertySetter(DateTime, usec)
{
	auto& valueThis = GetValueThis(valueTarget);
	Int16 num = Value_Number::GetNumberRanged<Int16>(value, 0, 999);
	if (Error::IsIssued()) return;
	valueThis.GetDateTime().SetUSec(num);
}

// DateTime#minsOff
Gurax_DeclareProperty_RW(DateTime, minsOff)
{
	Declare(VTYPE_Number, Flag::Nil);
	AddHelp("en", u8R"**(
The time-zone offset of the time in minute.
Returns `nil` if the `DateTime` instance has no information about time offset. 
)**");
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
		dateTime.SetMinsOffset(Value_Number::GetNumber<Int32>(value));
	} else {
		dateTime.InvalidateOffset();
	}
}

// DateTime#wday
Gurax_DeclareProperty_R(DateTime, wday)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
A number from 0 to 6 that corresponds to the week of the date from Sunday to Saturday.
)**");
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
	AddHelp("en", u8R"**(
The symbol that represents the week of the date.
)**");
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
	AddHelp("en", u8R"**(
The short symbol that represents the week of the date.
)**");
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
	AddHelp("en", u8R"**(
The day offset from the beginning of the year that starts from zero.
)**");
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
	AddHelp("en", u8R"**(
The `DateTime` instance that represents the UTC of the target.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, utc)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_DateTime(valueThis.GetDateTime().ToUTC());
}

// DateTime#unixTime
Gurax_DeclareProperty_R(DateTime, unixTime)
{
	Declare(VTYPE_DateTime, Flag::None);
	AddHelp("en", u8R"**(
The UNIX time of the date.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, unixTime)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetDateTime().ToUnixTime());
}

//------------------------------------------------------------------------------
// Implementation of class property
//------------------------------------------------------------------------------
// DateTime.tzOffset
Gurax_DeclareClassProperty_R(DateTime, tzOffset)
{
	Declare(VTYPE_TimeDelta, Flag::None);
	AddHelp("en", u8R"**(
Time zone offset in seconds.
)**");
}

Gurax_ImplementPropertyGetter(DateTime, tzOffset)
{
	// Function body
	RefPtr<TimeDelta> pTimeDelta(new TimeDelta(0, OAL::GetSecsOffsetTZ(), 0));
	return new Value_TimeDelta(pTimeDelta.release());
}

//------------------------------------------------------------------------------
// Implementation of operator
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

// DateTime == DateTime
Gurax_ImplementOpBinary(Eq, DateTime, DateTime)
{
	const DateTime& td1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& td2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(td1 == td2);
}

// DateTime != DateTime
Gurax_ImplementOpBinary(Ne, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(dt1 != dt2);
}

// DateTime < DateTime
Gurax_ImplementOpBinary(Lt, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(dt1 < dt2);
}

// DateTime <= DateTime
Gurax_ImplementOpBinary(Le, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(dt1 <= dt2);
}

// DateTime > DateTime
Gurax_ImplementOpBinary(Gt, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(dt1 > dt2);
}

// DateTime >= DateTime
Gurax_ImplementOpBinary(Ge, DateTime, DateTime)
{
	const DateTime& dt1 = Value_DateTime::GetDateTime(valueL);
	const DateTime& dt2 = Value_DateTime::GetDateTime(valueR);
	return new Value_Bool(dt1 >= dt2);
}

//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
VType_DateTime VTYPE_DateTime("DateTime");

void VType_DateTime::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(DateTime));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(DateTime, Create));
	Assign(Gurax_CreateClassMethod(DateTime, Now));
	Assign(Gurax_CreateClassMethod(DateTime, FromUnixTime));
	// Assignment of property
	Assign(Gurax_CreateProperty(DateTime, year));
	Assign(Gurax_CreateProperty(DateTime, month));
	Assign(Gurax_CreateProperty(DateTime, day));
	Assign(Gurax_CreateProperty(DateTime, hour));
	Assign(Gurax_CreateProperty(DateTime, min));
	Assign(Gurax_CreateProperty(DateTime, sec));
	Assign(Gurax_CreateProperty(DateTime, msec));
	Assign(Gurax_CreateProperty(DateTime, usec));
	Assign(Gurax_CreateProperty(DateTime, minsOff));
	Assign(Gurax_CreateProperty(DateTime, wday));
	Assign(Gurax_CreateProperty(DateTime, week));
	Assign(Gurax_CreateProperty(DateTime, weekShort));
	Assign(Gurax_CreateProperty(DateTime, yday));
	Assign(Gurax_CreateProperty(DateTime, utc));
	Assign(Gurax_CreateProperty(DateTime, unixTime));
	// Assignment of class property
	Assign(Gurax_CreateClassProperty(DateTime, tzOffset));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, DateTime, TimeDelta);
	Gurax_AssignOpBinary(Sub, DateTime, TimeDelta);
	Gurax_AssignOpBinary(Sub, DateTime, DateTime);
	Gurax_AssignOpBinary(Eq, DateTime, DateTime);
	Gurax_AssignOpBinary(Ne, DateTime, DateTime);
	Gurax_AssignOpBinary(Lt, DateTime, DateTime);
	Gurax_AssignOpBinary(Le, DateTime, DateTime);
	Gurax_AssignOpBinary(Gt, DateTime, DateTime);
	Gurax_AssignOpBinary(Ge, DateTime, DateTime);
}

Value* VType_DateTime::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* str = Value_String::GetString(value);
		RefPtr<DateTime> pDt(DateTime::CreateFromString(str));
		if (!pDt) {
			Error::Issue(ErrorType::FormatError, "invalid format for DateTime");
			return nullptr;
		}
		return new Value_DateTime(pDt.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------
VType& Value_DateTime::vtype = VTYPE_DateTime;

String Value_DateTime::ToString(const StringStyle& ss) const
{
	String strEntity = GetDateTime().ToString(ss);
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

}
