//==============================================================================
// DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DateTime
//------------------------------------------------------------------------------
DateTime& DateTime::operator+=(const TimeDelta& td)
{
	AddDelta(td.GetDays(), td.GetSecsRaw(), td.GetUSecs());
	return *this;
}

DateTime& DateTime::operator-=(const TimeDelta& td)
{
	AddDelta(-td.GetDays(), -td.GetSecsRaw(), -td.GetUSecs());
	return *this;
}

TimeDelta* DateTime::operator-(const DateTime& dt)
{
	return nullptr;
}

void DateTime::AddDelta(Int32 days, Int32 secs, Int32 usecs)
{
	Int32 dayOfYear = GetDayOfYear(_year, _month, _day);
	_usec += usecs;
	if (_usec >= 1000000) {
		_usec -= 1000000;
		_secInDay++;
	}
	_secInDay += secs;
	if (_secInDay >= 3600 * 24) {
		_secInDay -= 3600 * 24;
		dayOfYear++;
	}
	dayOfYear += days;
	if (dayOfYear >= 0) {
		while (dayOfYear >= GetDaysOfYear(_year)) {
			dayOfYear -= GetDaysOfYear(_year);
			_year++;
		}
	} else {
		while (dayOfYear < 0) {
			_year--;
			dayOfYear += GetDaysOfYear(_year);
		}
	}
	DayOfYearToMonthDay(_year, static_cast<Int16>(dayOfYear), &_month, &_day);
}

UInt8 DateTime::GetDaysOfMonth(UInt16 year, UInt8 month)
{
	static const UInt8 daysTbl_Normal[] = {
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	};
	static const UInt8 daysTbl_Leap[] = {
		0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	};
	if (month < 1 || month > 12) return -1;
	return (IsLeapYear(year)? daysTbl_Leap : daysTbl_Normal)[static_cast<int>(month)];
}

UInt16 DateTime::GetDayOfYear(UInt16 year, UInt8 month, UInt8 day)
{
	static const UInt16 offsetTbl_Normal[] = {
		0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
	};
	static const UInt16 offsetTbl_Leap[] = {
		0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
	};
	if (day < 1 || month < 1 || month > 12) return -1;
	return (IsLeapYear(year)? offsetTbl_Leap : offsetTbl_Normal)[static_cast<int>(month)] + day - 1;
}

void DateTime::DayOfYearToMonthDay(UInt16 year, UInt16 dayOfYear, UInt8* pMonth, UInt8* pDay)
{
	static const UInt16 offsetTbl_Normal[] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
	};
	static const UInt16 offsetTbl_Leap[] = {
		0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
	};
	const UInt16 *offsetTbl = IsLeapYear(year)? offsetTbl_Leap : offsetTbl_Normal;
	int i = 0;
	for ( ; i < 12 && dayOfYear >= offsetTbl[i]; i++) ;
	i--;
	*pMonth = static_cast<UInt8>(i + 1);
	*pDay = static_cast<UInt8>(dayOfYear - offsetTbl[i] + 1);
}

// Zeller's congruence. treat 0 as Sunday
UInt8 DateTime::GetDayOfWeek(UInt16 year, UInt8 month, UInt8 day)
{
	if (day < 1 || month < 1 || month > 12) return -1;
	if (month <= 2) {
		month += 12, year -= 1;
	}
	UInt16 yearH = year / 100, yearL = year % 100;
	int rtn = yearL + yearL / 4 + yearH / 4 - 2 * yearH +
		13 * (static_cast<int>(month) + 1) / 5 + day;
	rtn %= 7;
	if (rtn < 0) rtn += 7;
	return (rtn + 6) % 7;
}

#if 0

TimeDelta DateTime::Minus(const DateTime &dt) const
{
	DateTime dt1, dt2;
	if (HasTZOffset() && dt.HasTZOffset()) {
		dt1 = ToUTC();
		dt2 = dt.ToUTC();
	} else {
		dt1 = *this;
		dt2 = dt;
	}
	Int32 daysDiff = dt1.GetDayOfYear() - dt2.GetDayOfYear();
	if (dt1.GetYear() < dt2.GetYear()) {
		for (UInt16 year = dt1.GetYear(); year < dt2.GetYear(); year++) {
			daysDiff -= GetDaysOfYear(year);
		}
	} else if (dt1.GetYear() > dt2.GetYear()) {
		for (UInt16 year = dt1.GetYear() - 1; year >= dt2.GetYear(); year--) {
			daysDiff += GetDaysOfYear(year);
		}
	}
	Int32 secsDiff = dt1.GetSecRaw() - dt2.GetSecRaw();
	Int32 usecsDiff = dt1.GetUSec() - dt2.GetUSec();
	return TimeDelta(daysDiff, secsDiff, usecsDiff);
}
#endif

String DateTime::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%04d-%02d-%02d %02d:%02d:%02d",
			   GetYear(), GetMonth(), GetDay(), GetHour(), GetMin(), GetSec());
	return str;
}

}
