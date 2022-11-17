//==============================================================================
// DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DateTime
//------------------------------------------------------------------------------
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

// capable of parsing the following formats
// RFC1123   Sat, 06 Nov 2010 08:49:37 GMT
// RFC1036   Saturday, 06-Nov-10 08:49:37 GMT
// asctime() Sat Nov  6 08:49:37 2010
//           Sat Nov  6 08:49:37 +0000 2010
// W3C       2010-11-06T08:49:37Z
// No format 2010-11-06
DateTime* DateTime::CreateFromString(const char* str, const char** next)
{
	enum class Stat {
		Start, End,
		Weekday, Date,
		DateAscTime_Month, DateAscTime_Day,
		DateAscTime_YearPre, DateAscTime_Year,
		DateRFC_Year, DateRFC_Month, DateRFC_Day,
		W3C_Year, W3C_Month, W3C_Day,
		Time, Time_Hour, Time_Min, Time_Sec,
		TimeZone, TimeZoneName, TimeZoneDigit,
		SkipWhite,
	} stat = Stat::Start, statNext = Stat::Start;
	const char* monthNames[] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
	};
	int nCols = 0;
	String token;
	int year = 0, month = 0, day = 0;
	int hour = 0, min = 0, sec = 0;
	String timeZone;
	const char* p = str;
	for (;;) {
		char ch =* p;
		bool pushbackFlag = false;
		switch (stat) {
		case Stat::Start: {
			if (String::IsAlpha(ch)) {
				pushbackFlag = true;
				stat = Stat::Weekday;
			} else if (String::IsDigit(ch)) {
				pushbackFlag = true;
				stat = Stat::W3C_Year;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::Weekday: {
			if (String::IsAlpha(ch)) {
				token += ch;
			} else if (String::IsWhite(ch) || ch == ',') {
				if (token.size() < 3) return nullptr;
				token.clear();
				statNext = Stat::Date;
				stat = Stat::SkipWhite;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::Date: {
			if (String::IsAlpha(ch)) {
				pushbackFlag = true;
				stat = Stat::DateAscTime_Month;
			} else if (String::IsDigit(ch)) {
				pushbackFlag = true;
				stat = Stat::DateRFC_Day;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::W3C_Year: {
			if (String::IsDigit(ch)) {
				nCols++;
				year = year * 10 + (ch - '0');
				if (nCols > 4) return nullptr;
			} else if (ch == '-') {
				if (nCols > 4) return nullptr;
				nCols = 0;
				stat = Stat::W3C_Month;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::W3C_Month: {
			if (String::IsDigit(ch)) {
				nCols++;
				month = month * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (ch == '-') {
				if (nCols > 2) return nullptr;
				nCols = 0;
				stat = Stat::W3C_Day;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::W3C_Day: {
			if (String::IsDigit(ch)) {
				nCols++;
				day = day * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (ch == 'T' || String::IsWhite(ch)) {
				if (nCols > 2) return nullptr;
				nCols = 0;
				statNext = Stat::TimeZone;
				stat = Stat::Time;
			} else if (ch == '\0') {
				// nothing to do
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateAscTime_Month: {
			if (String::IsAlpha(ch)) {
				token += ch;
			} else if (String::IsWhite(ch)) {
				size_t i = 0;
				for (i = 0; i < Gurax_ArraySizeOf(monthNames); i++) {
					if (::strcasecmp(token.c_str(), monthNames[i]) == 0) break;
				}
				if (i == Gurax_ArraySizeOf(monthNames)) return nullptr;
				month = i + 1;
				token.clear();
				statNext = Stat::DateAscTime_Day;
				stat = Stat::SkipWhite;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateAscTime_Day: {
			if (String::IsDigit(ch)) {
				nCols++;
				day = day * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (String::IsWhite(ch)) {
				nCols = 0;
				statNext = Stat::DateAscTime_YearPre;
				stat = Stat::Time;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateAscTime_YearPre: {
			if (String::IsDigit(ch)) {
				pushbackFlag = true;
				stat = Stat::DateAscTime_Year;
			} else if (String::IsAlpha(ch) || ch == '+' || ch == '-') {
				pushbackFlag = true;
				statNext = Stat::DateAscTime_YearPre;
				stat = Stat::TimeZone;
			} else if (String::IsWhite(ch)) {
				// nothing to do
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateAscTime_Year: {
			if (String::IsDigit(ch)) {
				nCols++;
				year = year * 10 + (ch - '0');
				if (nCols > 4) return nullptr;
			} else {
				ch = '\0';
			}
			break;
		}
		case Stat::DateRFC_Day: {
			if (String::IsDigit(ch)) {
				nCols++;
				day = day * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (String::IsWhite(ch) || ch == '-') {
				nCols = 0;
				statNext = Stat::DateRFC_Month;
				stat = Stat::SkipWhite;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateRFC_Month: {
			if (String::IsAlpha(ch)) {
				token += ch;
			} else if (String::IsWhite(ch) || ch == '-') {
				size_t i = 0;
				for (i = 0; i < Gurax_ArraySizeOf(monthNames); i++) {
					if (::strcasecmp(token.c_str(), monthNames[i]) == 0) break;
				}
				if (i == Gurax_ArraySizeOf(monthNames)) return nullptr;
				month = i + 1;
				token.clear();
				statNext = Stat::DateRFC_Year;
				stat = Stat::SkipWhite;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::DateRFC_Year: {
			if (String::IsDigit(ch)) {
				nCols++;
				year = year * 10 + (ch - '0');
				if (nCols > 4) return nullptr;
			} else if (String::IsWhite(ch)) {
				if (nCols == 2) {
					year += (year < 70)? 2000 : 1900;
				} else if (nCols > 4) {
					return nullptr;
				}
				nCols = 0;
				statNext = Stat::TimeZone;
				stat = Stat::Time;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::Time: {
			if (String::IsWhite(ch)) {
				// nothing to do
			} else if (String::IsDigit(ch)) {
				pushbackFlag = true;
				stat = Stat::Time_Hour;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::Time_Hour: {
			if (String::IsDigit(ch)) {
				nCols++;
				hour = hour * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (ch == ':') {
				if (nCols > 2) return nullptr;
				nCols = 0;
				stat = Stat::Time_Min;
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::Time_Min: {
			if (String::IsDigit(ch)) {
				nCols++;
				min = min * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else if (ch == ':') {
				if (nCols > 2) return nullptr;
				nCols = 0;
				stat = Stat::Time_Sec;
			} else {
				if (nCols > 2) return nullptr;
				nCols = 0;
				pushbackFlag = true;
				stat = statNext;
				statNext = Stat::End;
			}
			break;
		}
		case Stat::Time_Sec: {
			if (String::IsDigit(ch)) {
				nCols++;
				sec = sec * 10 + (ch - '0');
				if (nCols > 2) return nullptr;
			} else {
				if (nCols > 2) return nullptr;
				nCols = 0;
				pushbackFlag = true;
				stat = statNext;
				statNext = Stat::End;
			}
			break;
		}
		case Stat::TimeZone: {
			if (String::IsAlpha(ch)) {
				pushbackFlag = true;
				stat = Stat::TimeZoneName;
			} else if (ch == '+' || ch == '-') {
				timeZone.clear();
				timeZone += ch;
				stat = Stat::TimeZoneDigit;
			} else if (ch == '\0' || String::IsWhite(ch)) {
				// nothing to do
			} else {
				return nullptr;
			}
			break;
		}
		case Stat::TimeZoneName: {
			if (String::IsAlpha(ch)) {
				timeZone += ch;
			} else {
				pushbackFlag = true;
				stat = statNext;
				statNext = Stat::End;
			}
			break;
		}
		case Stat::TimeZoneDigit: {
			if (String::IsDigit(ch)) {
				timeZone += ch;
				if (timeZone.size() > 5) return nullptr;
			} else if (ch == ':' && timeZone.size() == 3) {
				// accept ':' character between hour and minute fields
			} else {
				if (timeZone.size() != 5) return nullptr;
				pushbackFlag = true;
				stat = statNext;
				statNext = Stat::End;
			}
			break;
		}
		case Stat::SkipWhite: {
			if (String::IsWhite(ch)) {
				// nothing to do
			} else {
				pushbackFlag = true;
				stat = statNext;
				statNext = Stat::End;
			}
			break;
		}
		case Stat::End: {
			ch = '\0';
			break;
		}
		}
		if (pushbackFlag) {
			// nothing to do
		} else if (ch == '\0') {
			break;
		} else {
			p++;
		}
	}
	if (next) *next = p;
	if (!IsValidDate(year, month, day) || !IsValidTime(hour, min, sec)) return nullptr;
	RefPtr<DateTime> pDt(new DateTime(
		static_cast<Int16>(year), static_cast<Int8>(month), static_cast<Int8>(day),
		static_cast<Int32>(hour * 3600 + min * 60 + sec), 0));
	if (timeZone.empty()) {
		//pDt->SetSecsOffset(OAL::GetSecsOffsetTZ());
		// nothing to do
	} else if (String::IsAlpha(timeZone[0])) {
		// the list contains timezone names that are described in RFC 822 and JST.
		static const struct {
			const char* name;
			Int32 minsOffset;
		} tbl[] = {
			{ "GMT",	  0 * 60	},
			{ "UT",		  0 * 60	},
			{ "Z",		  0 * 60	},
			{ "A",		 -1 * 60	},
			{ "M",		-12 * 60	},
			{ "N",		  1 * 60	},
			{ "Y",		 12 * 60	},
			{ "JST",	  9 * 60	},
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(tbl); i++) {
			if (::strcasecmp(timeZone.c_str(), tbl[i].name) == 0) {
				pDt->SetMinsOffset(tbl[i].minsOffset);
				break;
			}
		}
	} else if (timeZone[0] == '+' || timeZone[0] == '-') {
		//int signNum = (timeZone[0] == '-')? -1 : +1;
		int hours = (timeZone[1] - '0') * 10 + (timeZone[2] - '0');
		int mins = (timeZone[3] - '0') * 10 + (timeZone[4] - '0');
		pDt->SetMinsOffset(hours * 60 + mins);
	}
	return pDt.release();
}

DateTime* DateTime::ToUTC() const
{
	//if (_tz.secsOffset == 0) return Clone();
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
	rtn += static_cast<UInt64>(pTd->GetDays()) * 60 * 60 * 24;
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

bool DateTime::IsValidDate(int year, int month, int day)
{
	if (year < 0 || year > 9999) return false;
	if (month < 1 || month > 12) return false;
	int days = GetDaysOfMonth(year, month);
	return 1 <= day && day <= days;
}

bool DateTime::IsValidTime(int hour, int min, int sec)
{
	if (hour < 0 || hour > 23) return false;
	if (min < 0 || min > 59) return false;
	return 0 <= sec && sec < 60;
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
	str.Format(colonFlag? "%02d:%02d" : "%02d%02d", minsOffset / 60, minsOffset % 60);
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
	str.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d",
			   GetYear(), GetMonth(), GetDay(), GetHour(), GetMin(), GetSec(), GetMSec());
	if (Int16 usec = GetUSec()) str.Format("%03d", usec);
	str += GetTZOffsetStr(true);
	return str;
}

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

}
