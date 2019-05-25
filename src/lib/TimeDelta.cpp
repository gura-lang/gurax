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

TimeDelta& TimeDelta::operator*=(int n)
{
	Unpack(Pack(_days, _secs, _usecs) * n, &_days, &_secs, &_usecs);
	return *this;
}

TimeDelta& TimeDelta::operator/=(int n)
{
	Unpack(Pack(_days, _secs, _usecs) / n, &_days, &_secs, &_usecs);
	return *this;
}

void TimeDelta::Regulate()
{
	Unpack(Pack(_days, _secs, _usecs), &_days, &_secs, &_usecs);
}

Int TimeDelta::Compare(const TimeDelta& td1, const TimeDelta& td2)
{
	Int result = 0;
	if ((result = td1._days - td2._days) != 0) {
	} else if ((result = td1._secs - td2._secs) != 0) {
	} else if ((result = td1._usecs - td2._usecs) != 0) {
	}
	return result;
}

Int64 TimeDelta::Pack(Int32 days, Int32 secs, Int32 usecs)
{
	Int64 num = usecs;
	num += static_cast<Int64>(secs) * 1000000;
	num += static_cast<Int64>(days) * 1000000 * 24 * 60 * 60;
	return num;
}

void TimeDelta::Unpack(Int64 num, Int32* pDays, Int32* pSecs, Int32* pUsecs)
{
	*pUsecs = static_cast<Int32>(num % 1000000);
	num /= 1000000;
	*pSecs = static_cast<Int32>(num % (24 * 60 * 60));
	num /= 24 * 60 * 60;
	*pDays = static_cast<Int32>(num);
}

String TimeDelta::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%ddays,%02d:%02d:%02d.%03d",
		GetDays(), GetHours(), GetMins(), GetSecs(), GetMSecs());
	return str;
}

}
