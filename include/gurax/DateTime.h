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
private:
	UInt16 _year;
	UInt8 _month;
	UInt8 _day;
	UInt32 _secInDay;
	UInt32 _usec;
	struct {
		bool validFlag;
		Int32 secsOffset;
	} _tz;
public:
	// Constructor
	DateTime() : _year(1970), _month(1), _day(1), _secInDay(0), _usec(0) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(UInt16 year, UInt8 month, UInt8 day, UInt32 secInDay, UInt32 usec) :
		_year(year), _month(month), _day(day), _secInDay(secInDay), _usec(usec) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(UInt16 year, UInt8 month, UInt8 day, UInt32 secInDay, UInt32 usec, Int32 secsOffset) :
		_year(year), _month(month), _day(day), _secInDay(secInDay), _usec(usec) {
		_tz.validFlag = true, _tz.secsOffset = secsOffset;
	}
	// Copy constructor/operator
	DateTime(const DateTime& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _secInDay(dt._secInDay), _usec(dt._usec), _tz(dt._tz) {
	}
	DateTime& operator=(const DateTime& dt) {
		_year = dt._year, _month = dt._month, _day = dt._day, _secInDay = dt._secInDay, _usec = dt._usec, _tz = dt._tz;
		return *this;
	}
	// Move constructor/operator
	DateTime(DateTime&& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _secInDay(dt._secInDay), _usec(dt._usec), _tz(dt._tz) {
	}
	DateTime& operator=(DateTime&& dt) noexcept {
		_year = dt._year, _month = dt._month, _day = dt._day, _secInDay = dt._secInDay, _usec = dt._usec, _tz = dt._tz;
		return *this;
	}
protected:
	// Destructor
	virtual ~DateTime() = default;
public:
	UInt16 GetYear() const { return _year; }
	UInt8 GetMonth() const { return _month; }
	UInt8 GetDay() const { return _day; }
	UInt8 GetHour() const { return GetSecInDay() / 3600; }
	UInt8 GetMin() const { return (GetSecInDay() / 60) % 60; }
	UInt8 GetSec() const { return GetSecInDay() % 60; }
	UInt32 GetSecInDay() const { return _secInDay; }
	UInt32 GetUSec() const { return _usec; }
	bool HasOffset() const { return _tz.validFlag; }
	Int32 GetSecsOffset() const { return _tz.secsOffset; }
	Int32 GetMinsOffset() const { return _tz.secsOffset / 60; }
	UInt16 GetDayOfYear() const { return GetDayOfYear(_year, _month, _day); }
	UInt8 GetDayOfWeek() const { return GetDayOfWeek(_year, _month, _day); }
	UInt8 GetDaysOfMonth() const { return GetDaysOfMonth(_year, _month); }
	void SetYear(UInt16 year) { _year = year; }
	void SetMonth(UInt8 month) { _month = month; }
	void SetDay(UInt8 day) { _day = day; }
	void SetHour(UInt8 hour) { _secInDay = CalcSecInDay(hour, GetMin(), GetSec()); }
	void SetMin(UInt8 min) { _secInDay = CalcSecInDay(GetHour(), min, GetSec()); }
	void SetSec(UInt8 sec) { _secInDay = CalcSecInDay(GetHour(), GetMin(), sec); }
	void SetSecInDay(UInt32 secInDay) { _secInDay = secInDay; }
	void SetUSec(UInt32 usec) { _usec = usec; }
	void InvalidateOffset() { _tz.validFlag = false, _tz.secsOffset = 0; }
	void SetSecsOffset(Int32 secsOffset) { _tz.validFlag = true, _tz.secsOffset = secsOffset; }
	void SetMinsOffset(Int32 minsOffset) { _tz.validFlag = true, _tz.secsOffset = minsOffset * 60; }
public:
	DateTime& operator+=(const TimeDelta& td);
	DateTime& operator-=(const TimeDelta& td);
	TimeDelta* operator-(const DateTime& dt);
public:
	void AddDelta(Int32 days, Int32 secs, Int32 usecs);
	String GetTZOffsetStr(bool colonFlag) const;
	static UInt32 CalcSecInDay(UInt8 hour, UInt8 min, UInt8 sec) {
		return static_cast<UInt32>(hour) * 3600 + static_cast<UInt32>(min) * 60 + sec;
	}
	static bool IsLeapYear(UInt16 year) {
		return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}
	static UInt16 GetDaysOfYear(UInt16 year) {
		return IsLeapYear(year)? 366 : 365;
	}
	static void DayOfYearToMonthDay(UInt16 year, UInt16 dayOfYear, UInt8* pMonth, UInt8* pDay);
	static UInt16 GetDayOfYear(UInt16 year, UInt8 month, UInt8 day);
	static UInt8 GetDayOfWeek(UInt16 year, UInt8 month, UInt8 day);
	static UInt8 GetDaysOfMonth(UInt16 year, UInt8 month);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DateTime& dateTime) const { return this == &dateTime; }
	bool IsEqualTo(const DateTime& dateTime) const { return IsIdentical(dateTime); }
	bool IsLessThan(const DateTime& dateTime) const { return this < &dateTime; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
