//==============================================================================
// TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TimeDelta
//------------------------------------------------------------------------------
TimeDelta::TimeDelta(Int32 days, Int32 secs, Int32 usecs) :
	_days(days), _secs(secs), _usecs(usecs)
{
	Regulate();
}

TimeDelta* TimeDelta::operator-() const
{
	return new TimeDelta(-_days, -_secs, -_usecs);
}

TimeDelta& TimeDelta::operator+=(const TimeDelta& td)
{
	_days += td._days;
	_secs += td._secs;
	_usecs += td._usecs;
	Regulate();
	return *this;
}

TimeDelta& TimeDelta::operator-=(const TimeDelta& td)
{
	_days -= td._days;
	_secs -= td._secs;
	_usecs -= td._usecs;
	Regulate();
	return *this;
}

bool TimeDelta::operator==(const TimeDelta& td) const
{
	return _days == td._days && _secs == td._secs && _usecs == td._usecs;
}

bool TimeDelta::operator!=(const TimeDelta& td) const
{
	return !operator==(td);
}

bool TimeDelta::operator<(const TimeDelta& td) const
{
	return _days < td._days || _secs < td._secs || _usecs < td._usecs;
}

bool TimeDelta::operator<=(const TimeDelta& td) const
{
	return !operator>(td);
}

bool TimeDelta::operator>(const TimeDelta& td) const
{
	return _days > td._days || _secs > td._secs || _usecs > td._usecs;
}

bool TimeDelta::operator>=(const TimeDelta& td) const
{
	return !operator<(td);
}

void TimeDelta::Regulate()
{
	_secs += _usecs / 1000000;
	_usecs %= 1000000;
	_days += _secs / (3600 * 24);
	_secs %= 3600 * 24;
	if (_usecs < 0) {
		_usecs += 1000000;
		_secs--;
	}
	if (_secs < 0) {
		_secs += 3600 * 24;
		_days--;
	}
}

int TimeDelta::Compare(const TimeDelta& td1, const TimeDelta& td2)
{
	Int32 result = 0;
	if ((result = td1._days - td2._days) != 0) {
	} else if ((result = td1._secs - td2._secs) != 0) {
	} else if ((result = td1._usecs - td2._usecs) != 0) {
	}
	return (result < 0)? -1 : (result > 0)? +1 : 0;
}

String TimeDelta::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%ddays,%02d:%02d:%02d.%03d",
		GetDays(), GetHours(), GetMins(), GetSecs(), GetMSecs());
	return str;
}

}
