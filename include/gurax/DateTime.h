//==============================================================================
// DateTime.h
//==============================================================================
#ifndef GURAX_DATETIME_H
#define GURAX_DATETIME_H
#include "Referable.h"

namespace Gurax {

class TimeDelta;

//------------------------------------------------------------------------------
// DateTime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DateTime : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DateTime);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("DateTime");
public:
	struct TimeZone {
		bool validFlag;
		Int32 secsOffset;
	};
private:
	Int16 _year;
	Int8 _month;
	Int8 _day;
	Int32 _secPacked;
	Int32 _usecPacked;
	TimeZone _tz;
public:
	// Constructor
	DateTime() : _year(1970), _month(1), _day(1), _secPacked(0), _usecPacked(0) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 secPacked, Int32 usecPacked) :
		_year(year), _month(month), _day(day), _secPacked(secPacked), _usecPacked(usecPacked) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 secPacked, Int32 usecPacked, Int32 secsOffset) :
		_year(year), _month(month), _day(day), _secPacked(secPacked), _usecPacked(usecPacked) {
		_tz.validFlag = true, _tz.secsOffset = secsOffset;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 secPacked, Int32 usecPacked, const TimeZone& tz) :
		_year(year), _month(month), _day(day), _secPacked(secPacked), _usecPacked(usecPacked), _tz(tz) {}
	// Copy constructor/operator
	DateTime(const DateTime& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _secPacked(dt._secPacked), _usecPacked(dt._usecPacked), _tz(dt._tz) {
	}
	DateTime& operator=(const DateTime& dt) {
		_year = dt._year, _month = dt._month, _day = dt._day, _secPacked = dt._secPacked, _usecPacked = dt._usecPacked, _tz = dt._tz;
		return *this;
	}
	// Move constructor/operator
	DateTime(DateTime&& dt) noexcept :
		_year(dt._year), _month(dt._month), _day(dt._day), _secPacked(dt._secPacked), _usecPacked(dt._usecPacked), _tz(dt._tz) {
	}
	DateTime& operator=(DateTime&& dt) noexcept {
		_year = dt._year, _month = dt._month, _day = dt._day, _secPacked = dt._secPacked, _usecPacked = dt._usecPacked, _tz = dt._tz;
		return *this;
	}
protected:
	// Destructor
	virtual ~DateTime() = default;
public:
	DateTime* Clone() const { return new DateTime(*this); }
public:
	bool Serialize(Stream& stream) const;
	static DateTime* Deserialize(Stream& stream);
public:
	Int16 GetYear() const { return _year; }
	Int8 GetMonth() const { return _month; }
	Int8 GetDay() const { return _day; }
	Int8 GetHour() const { return GetSecPacked() / 3600; }
	Int8 GetMin() const { return (GetSecPacked() / 60) % 60; }
	Int8 GetSec() const { return GetSecPacked() % 60; }
	Int32 GetSecPacked() const { return _secPacked; }
	Int16 GetMSec() const { return static_cast<Int16>(_usecPacked / 1000); }
	Int16 GetUSec() const { return static_cast<Int16>(_usecPacked % 1000); }
	Int32 GetUSecPacked() const { return _usecPacked; }
	bool HasOffset() const { return _tz.validFlag; }
	Int32 GetSecsOffset() const { return _tz.secsOffset; }
	Int32 GetMinsOffset() const { return _tz.secsOffset / 60; }
	Int16 GetDayOfYear() const { return GetDayOfYear(_year, _month, _day); }
	Int8 GetDayOfWeek() const { return GetDayOfWeek(_year, _month, _day); }
	const Symbol* GetSymbolOfWeek() const { return GetSymbolOfWeek(_year, _month, _day); }
	const Symbol* GetSymbolShortOfWeek() const { return GetSymbolShortOfWeek(_year, _month, _day); }
	Int8 GetDaysOfMonth() const { return GetDaysOfMonth(_year, _month); }
public:
	void SetYear(Int16 year) { _year = year; }
	void SetMonth(Int8 month) { _month = month; }
	void SetDay(Int8 day) { _day = day; }
	void SetHour(Int8 hour) { _secPacked = CalcSecPacked(hour, GetMin(), GetSec()); }
	void SetMin(Int8 min) { _secPacked = CalcSecPacked(GetHour(), min, GetSec()); }
	void SetSec(Int8 sec) { _secPacked = CalcSecPacked(GetHour(), GetMin(), sec); }
	void SetSecPacked(Int32 secPacked) { _secPacked = secPacked; }
	void SetMSec(Int16 msec) { _usecPacked = CalcUSecPacked(msec, GetUSec()); }
	void SetUSec(Int16 usec) { _usecPacked = CalcUSecPacked(GetMSec(), usec); }
	void SetUSecPacked(Int32 usecPacked) { _usecPacked = usecPacked; }
	void InvalidateOffset() { _tz.validFlag = false, _tz.secsOffset = 0; }
	void SetSecsOffset(Int32 secsOffset) { _tz.validFlag = true, _tz.secsOffset = secsOffset; }
	void SetMinsOffset(Int32 minsOffset) { _tz.validFlag = true, _tz.secsOffset = minsOffset * 60; }
public:
	DateTime& operator+=(const TimeDelta& td);
	DateTime& operator-=(const TimeDelta& td);
	TimeDelta* operator-(const DateTime& dt) const;
	bool operator==(const DateTime& dt) const { return Compare(*this, dt) == 0; }
	bool operator!=(const DateTime& dt) const { return Compare(*this, dt) != 0; }
	bool operator<(const DateTime& dt) const  { return Compare(*this, dt) < 0;  }
	bool operator<=(const DateTime& dt) const { return Compare(*this, dt) <= 0; }
	bool operator>(const DateTime& dt) const  { return Compare(*this, dt) > 0;  }
	bool operator>=(const DateTime& dt) const { return Compare(*this, dt) >= 0; }
public:
	static DateTime* CreateFromString(const char* str, const char** next = nullptr);
	void AddDelta(Int32 days, Int32 secs, Int32 usecs);
	DateTime* ToUTC() const;
	UInt64 ToUnixTime() const;
	String GetTZOffsetStr(bool colonFlag) const;
	static Int32 CalcSecPacked(Int8 hour, Int8 min, Int8 sec) {
		return static_cast<Int32>(hour) * 3600 + static_cast<Int32>(min) * 60 + sec;
	}
	static Int32 CalcUSecPacked(Int16 msec, Int16 usec) { return static_cast<Int32>(msec) * 1000 + usec; }
	static Int Compare(const DateTime& dt1, const DateTime& dt2);
	static bool IsLeapYear(Int16 year) {
		return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}
	static Int16 GetDaysOfYear(Int16 year) {
		return IsLeapYear(year)? 366 : 365;
	}
	static bool IsValidDate(int year, int month, int day);
	static bool IsValidTime(int hour, int min, int sec);
	static void DayOfYearToMonthDay(Int16 year, Int16 dayOfYear, Int8* pMonth, Int8* pDay);
	static Int16 GetDayOfYear(Int16 year, Int8 month, Int8 day);
	static Int8 GetDayOfWeek(Int16 year, Int8 month, Int8 day);
	static const Symbol* GetSymbolOfWeek(Int16 year, Int8 month, Int8 day);
	static const Symbol* GetSymbolShortOfWeek(Int16 year, Int8 month, Int8 day);
	static Int8 GetDaysOfMonth(Int16 year, Int8 month);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DateTime& dateTime) const { return this == &dateTime; }
	bool IsEqualTo(const DateTime& dateTime) const { return IsIdentical(dateTime); }
	bool IsLessThan(const DateTime& dateTime) const { return this < &dateTime; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
