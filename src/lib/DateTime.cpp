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

TimeDelta* DateTime::operator-(const DateTime& dt) const
{
	RefPtr<DateTime> pDt1(ToUTC());
	RefPtr<DateTime> pDt2(dt.ToUTC());
	Int32 daysDiff = pDt1->GetDayOfYear() - pDt2->GetDayOfYear();
	if (pDt1->GetYear() < pDt2->GetYear()) {
		for (UInt16 year = pDt1->GetYear(); year < pDt2->GetYear(); year++) {
			daysDiff -= GetDaysOfYear(year);
		}
	} else if (pDt1->GetYear() > pDt2->GetYear()) {
		for (UInt16 year = pDt1->GetYear() - 1; year >= pDt2->GetYear(); year--) {
			daysDiff += GetDaysOfYear(year);
		}
	}
	Int32 secsDiff = pDt1->GetSecInDay() - pDt2->GetSecInDay();
	Int32 usecsDiff = pDt1->GetUSec() - pDt2->GetUSec();
	return new TimeDelta(daysDiff, secsDiff, usecsDiff);
}

void DateTime::AddDelta(Int32 days, Int32 secs, Int32 usecs)
{
	Int32 dayOfYear = GetDayOfYear(_year, _month, _day);
	_usecRaw += usecs;
	if (_usecRaw >= 1000000) {
		_usecRaw -= 1000000;
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

DateTime* DateTime::ToUTC() const
{
	if (!HasOffset()) return Clone();
	RefPtr<DateTime> pDt(Clone());
	pDt->AddDelta(0, GetSecsOffset(), 0);
	pDt->SetSecsOffset(0);
	return pDt.release();
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

const Symbol* DateTime::GetSymbolOfWeek(UInt16 year, UInt8 month, UInt8 day)
{
	UInt8 dayOfWeek = GetDayOfWeek(year, month, day);
	return
		(dayOfWeek == 0)? Gurax_Symbol(Sunday) :
		(dayOfWeek == 1)? Gurax_Symbol(Monday) :
		(dayOfWeek == 2)? Gurax_Symbol(Tuesday) :
		(dayOfWeek == 3)? Gurax_Symbol(Wednesday) :
		(dayOfWeek == 4)? Gurax_Symbol(Thursday) :
		(dayOfWeek == 5)? Gurax_Symbol(Friday) :
		(dayOfWeek == 6)? Gurax_Symbol(Saturday) : Symbol::Empty;
}

const Symbol* DateTime::GetSymbolShortOfWeek(UInt16 year, UInt8 month, UInt8 day)
{
	UInt8 dayOfWeek = GetDayOfWeek(year, month, day);
	return
		(dayOfWeek == 0)? Gurax_Symbol(Sun) :
		(dayOfWeek == 1)? Gurax_Symbol(Mon) :
		(dayOfWeek == 2)? Gurax_Symbol(Tue) :
		(dayOfWeek == 3)? Gurax_Symbol(Wed) :
		(dayOfWeek == 4)? Gurax_Symbol(Thu) :
		(dayOfWeek == 5)? Gurax_Symbol(Fri) :
		(dayOfWeek == 6)? Gurax_Symbol(Sat) : Symbol::Empty;
}

String DateTime::GetTZOffsetStr(bool colonFlag) const
{
	if (!HasOffset()) return "";
	Int32 minsOffset = GetMinsOffset();
	if (minsOffset == 0) return "Z";
	String str;
	if (minsOffset < 0) {
		minsOffset = -minsOffset;
		str += "-";
	} else {
		str += "+";
	}
	str.Printf(colonFlag? "%02d:%02d" : "%02d%02d", minsOffset / 60, minsOffset % 60);
	return str;
}

String DateTime::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%04d-%02d-%02d %02d:%02d:%02d.%03d",
			   GetYear(), GetMonth(), GetDay(), GetHour(), GetMin(), GetSec(), GetMSec());
	str += GetTZOffsetStr(true);
	return str;
}

}
