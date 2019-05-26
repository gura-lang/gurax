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
	AddDelta(td.GetDays(), td.GetSecsPacked(), td.GetUSecsPacked());
	return *this;
}

DateTime& DateTime::operator-=(const TimeDelta& td)
{
	AddDelta(-td.GetDays(), -td.GetSecsPacked(), -td.GetUSecsPacked());
	return *this;
}

TimeDelta* DateTime::operator-(const DateTime& dt) const
{
	RefPtr<DateTime> pDt1(ToUTC());
	RefPtr<DateTime> pDt2(dt.ToUTC());
	Int32 daysDiff = pDt1->GetDayOfYear() - pDt2->GetDayOfYear();
	if (pDt1->GetYear() < pDt2->GetYear()) {
		for (Int16 year = pDt1->GetYear(); year < pDt2->GetYear(); year++) {
			daysDiff -= GetDaysOfYear(year);
		}
	} else if (pDt1->GetYear() > pDt2->GetYear()) {
		for (Int16 year = pDt1->GetYear() - 1; year >= pDt2->GetYear(); year--) {
			daysDiff += GetDaysOfYear(year);
		}
	}
	Int32 secsDiff = pDt1->GetSecPacked() - pDt2->GetSecPacked();
	Int32 usecsDiff = pDt1->GetUSecPacked() - pDt2->GetUSecPacked();
	return new TimeDelta(daysDiff, secsDiff, usecsDiff);
}

void DateTime::AddDelta(Int32 days, Int32 secs, Int32 usecs)
{
	Int32 dayOfYear = GetDayOfYear(_year, _month, _day);
	_usecPacked += usecs;
	if (_usecPacked >= 1000000) {
		_usecPacked -= 1000000;
		_secPacked++;
	} else if (_usecPacked < 0) {
		_usecPacked += 1000000;
		_secPacked--;
	}
	_secPacked += secs;
	if (_secPacked >= 3600 * 24) {
		_secPacked -= 3600 * 24;
		dayOfYear++;
	} else if (_secPacked < 0) {
		_secPacked += 3600 * 24;
		dayOfYear--;
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
	if (_tz.secsOffset == 0) return Clone();
	RefPtr<DateTime> pDt(Clone());
	pDt->AddDelta(0, -GetSecsOffset(), 0);
	pDt->SetSecsOffset(0);
	return pDt.release();
}

UInt64 DateTime::ToUnixTime() const
{
	RefPtr<DateTime> pDt(new DateTime(1970, 1, 1, 0, 0));
	RefPtr<TimeDelta> pTd(*this - *pDt);
	UInt64 rtn = pTd->GetSecsPacked();
	rtn += pTd->GetDays() * 60 * 60 * 24;
	return rtn;
}

Int8 DateTime::GetDaysOfMonth(Int16 year, Int8 month)
{
	static const Int8 daysTbl_Normal[] = {
		0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	};
	static const Int8 daysTbl_Leap[] = {
		0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	};
	if (month < 1 || month > 12) return -1;
	return (IsLeapYear(year)? daysTbl_Leap : daysTbl_Normal)[static_cast<int>(month)];
}

void DateTime::DayOfYearToMonthDay(Int16 year, Int16 dayOfYear, Int8* pMonth, Int8* pDay)
{
	static const Int16 offsetTbl_Normal[] = {
		0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
	};
	static const Int16 offsetTbl_Leap[] = {
		0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
	};
	const Int16 *offsetTbl = IsLeapYear(year)? offsetTbl_Leap : offsetTbl_Normal;
	int i = 0;
	for ( ; i < 12 && dayOfYear >= offsetTbl[i]; i++) ;
	i--;
	*pMonth = static_cast<Int8>(i + 1);
	*pDay = static_cast<Int8>(dayOfYear - offsetTbl[i] + 1);
}

Int16 DateTime::GetDayOfYear(Int16 year, Int8 month, Int8 day)
{
	static const Int16 offsetTbl_Normal[] = {
		0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
	};
	static const Int16 offsetTbl_Leap[] = {
		0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
	};
	if (day < 1 || month < 1 || month > 12) return -1;
	return (IsLeapYear(year)? offsetTbl_Leap : offsetTbl_Normal)[static_cast<int>(month)] + day - 1;
}

// Zeller's congruence. treat 0 as Sunday
Int8 DateTime::GetDayOfWeek(Int16 year, Int8 month, Int8 day)
{
	if (day < 1 || month < 1 || month > 12) return -1;
	if (month <= 2) {
		month += 12, year -= 1;
	}
	Int16 yearH = year / 100, yearL = year % 100;
	int rtn = yearL + yearL / 4 + yearH / 4 - 2 * yearH +
		13 * (static_cast<int>(month) + 1) / 5 + day;
	rtn %= 7;
	if (rtn < 0) rtn += 7;
	return (rtn + 6) % 7;
}

const Symbol* DateTime::GetSymbolOfWeek(Int16 year, Int8 month, Int8 day)
{
	Int8 dayOfWeek = GetDayOfWeek(year, month, day);
	return
		(dayOfWeek == 0)? Gurax_Symbol(Sunday) :
		(dayOfWeek == 1)? Gurax_Symbol(Monday) :
		(dayOfWeek == 2)? Gurax_Symbol(Tuesday) :
		(dayOfWeek == 3)? Gurax_Symbol(Wednesday) :
		(dayOfWeek == 4)? Gurax_Symbol(Thursday) :
		(dayOfWeek == 5)? Gurax_Symbol(Friday) :
		(dayOfWeek == 6)? Gurax_Symbol(Saturday) : Symbol::Empty;
}

const Symbol* DateTime::GetSymbolShortOfWeek(Int16 year, Int8 month, Int8 day)
{
	Int8 dayOfWeek = GetDayOfWeek(year, month, day);
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

Int DateTime::Compare(const DateTime& dt1, const DateTime& dt2)
{
	Int result;
	if ((result = static_cast<Int>(dt1._year) - dt2._year) != 0) {
	} else if ((result = static_cast<Int>(dt1._month) - dt2._month) != 0) {
	} else if ((result = static_cast<Int>(dt1._day) - dt2._day) != 0) {
	} else if ((result = static_cast<Int>(dt1._secPacked) - dt2._secPacked) != 0) {
	} else if ((result = static_cast<Int>(dt1._usecPacked) - dt2._usecPacked) != 0) {
	}
	return result;
}

String DateTime::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%04d-%02d-%02d %02d:%02d:%02d.%03d",
			   GetYear(), GetMonth(), GetDay(), GetHour(), GetMin(), GetSec(), GetMSec());
	if (Int16 usec = GetUSec()) str.Printf("%03d", usec);
	str += GetTZOffsetStr(true);
	return str;
}

}
