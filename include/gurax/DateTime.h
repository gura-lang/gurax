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
	Int32 _sec;
	Int32 _usec;
	struct {
		bool validFlag;
		Int32 secsOffset;
	} _tz;
public:
	// Constructor
	DateTime() : _year(0), _month(0), _day(0), _sec(0), _usec(0) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 sec, Int32 usec) :
		_year(year), _month(month), _day(day), _sec(sec), _usec(usec) {
		_tz.validFlag = false, _tz.secsOffset = 0;
	}
	DateTime(Int16 year, Int8 month, Int8 day, Int32 sec, Int32 usec, Int32 secsOffset) :
		_year(year), _month(month), _day(day), _sec(sec), _usec(usec) {
		_tz.validFlag = true, _tz.secsOffset = secsOffset;
	}
	// Copy constructor/operator
	DateTime(const DateTime& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _sec(dt._sec), _usec(dt._usec), _tz(dt._tz) {
	}
	DateTime& operator=(const DateTime& dt) {
		_year = dt._year, _month = dt._month, _day = dt._day, _sec = dt._sec, _usec = dt._usec, _tz = dt._tz;
		return *this;
	}
	// Move constructor/operator
	DateTime(DateTime&& dt) :
		_year(dt._year), _month(dt._month), _day(dt._day), _sec(dt._sec), _usec(dt._usec), _tz(dt._tz) {
	}
	DateTime& operator=(DateTime&& dt) noexcept {
		_year = dt._year, _month = dt._month, _day = dt._day, _sec = dt._sec, _usec = dt._usec, _tz = dt._tz;
		return *this;
	}
protected:
	// Destructor
	virtual ~DateTime() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DateTime& dateTime) const { return this == &dateTime; }
	bool IsEqualTo(const DateTime& dateTime) const { return IsIdentical(dateTime); }
	bool IsLessThan(const DateTime& dateTime) const { return this < &dateTime; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(datetime)"; }
};

}

#endif
