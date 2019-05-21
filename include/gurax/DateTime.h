//==============================================================================
// DateTime.h
//==============================================================================
#ifndef GURAX_DATETIME_H
#define GURAX_DATETIME_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DateTime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DateTime : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DateTime);
private:
	Int16 _year;
	Int8 _month;
	Int8 _day;
	Int32 _secInDay;
	Int32 _usecInDay;
	struct {
		bool validFlag;
		Int32 secsOffset;
	} _tz;
public:
	// Constructor
	DateTime() : _year(0), _month(0), _day(0), _secInDay(0), _usecInDay(0) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 secInDay, Int32 usecInDay) :
		_year(year), _month(month), _day(day), _secInDay(secInDay), _usecInDay(usecInDay) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 secInDay, Int32 usecInDay, Int32 secsOffset) :
		_year(year), _month(month), _day(day), _secInDay(secInDay), _usecInDay(usecInDay) {
		_tz.validFlag = true, _tz.secsOffset = secsOffset;
	}
	// Copy constructor/operator
	DateTime(const DateTime& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _secInDay(dt._secInDay), _usecInDay(dt._usecInDay), _tz(dt._tz) {
	}
	DateTime& operator=(const DateTime& dt) {
		_year = dt._year, _month = dt._month, _day = dt._day, _secInDay = dt._secInDay, _usecInDay = dt._usecInDay, _tz = dt._tz;
		return *this;
	}
	// Move constructor/operator
	DateTime(DateTime&& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _secInDay(dt._secInDay), _usecInDay(dt._usecInDay), _tz(dt._tz) {
	}
	DateTime& operator=(DateTime&& dt) noexcept {
		_year = dt._year, _month = dt._month, _day = dt._day, _secInDay = dt._secInDay, _usecInDay = dt._usecInDay, _tz = dt._tz;
		return *this;
	}
protected:
	// Destructor
	virtual ~DateTime() = default;
public:
	Int16 GetYear() const { return _year; }
	Int8 GetMonth() const { return _month; }
	Int8 GetDay() const { return _day; }
	Int8 GetHour() const { return GetSecInDay() / 3600; }
	Int8 GetMin() const { return (GetSecInDay() / 60) % 60; }
	Int8 GetSec() const { return GetSecInDay() % 60; }
	Int32 GetUSec() const { return GetUSecInDay(); }
	Int32 GetSecInDay() const { return _secInDay; }
	Int32 GetUSecInDay() const { return _usecInDay; }
	void SetYear(Int16 year) { _year = year; }
	void SetMonth(Int8 month) { _month = month; }
	void SetDay(Int8 day) { _day = day; }
	void SetSecInDay(Int32 secInDay) { _secInDay = secInDay; }
	void SetUSecInDay(Int32 usecInDay) { _usecInDay = usecInDay; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DateTime& dateTime) const { return this == &dateTime; }
	bool IsEqualTo(const DateTime& dateTime) const { return IsIdentical(dateTime); }
	bool IsLessThan(const DateTime& dateTime) const { return this < &dateTime; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
