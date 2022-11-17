//==============================================================================
// TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TimeDelta
//------------------------------------------------------------------------------
TimeDelta::TimeDelta(Int32 days, Int32 secsPacked, Int32 usecsPacked) :
	_days(days), _secsPacked(secsPacked), _usecsPacked(usecsPacked)
{
	Regulate();
}

TimeDelta* TimeDelta::operator-() const
{
	return new TimeDelta(-_days, -_secsPacked, -_usecsPacked);
}

TimeDelta& TimeDelta::operator+=(const TimeDelta& td)
{
	_days += td._days;
	_secsPacked += td._secsPacked;
	_usecsPacked += td._usecsPacked;
	Regulate();
	return *this;
}

TimeDelta& TimeDelta::operator-=(const TimeDelta& td)
{
	_days -= td._days;
	_secsPacked -= td._secsPacked;
	_usecsPacked -= td._usecsPacked;
	Regulate();
	return *this;
}

TimeDelta& TimeDelta::operator*=(Double n)
{
	Unpack(static_cast<Int64>(Pack(_days, _secsPacked, _usecsPacked) * n), &_days, &_secsPacked, &_usecsPacked);
	return *this;
}

TimeDelta& TimeDelta::operator/=(Double n)
{
	Unpack(static_cast<Int64>(Pack(_days, _secsPacked, _usecsPacked) / n), &_days, &_secsPacked, &_usecsPacked);
	return *this;
}

Double TimeDelta::operator/(const TimeDelta& td) const
{
	Int64 numDiv = Pack(td._days, td._secsPacked, td._usecsPacked);
	if (numDiv == 0) return 0;
	return static_cast<Double>(Pack(_days, _secsPacked, _usecsPacked)) / numDiv;
}

TimeDelta& TimeDelta::operator%=(const TimeDelta& td)
{
	Int64 numDiv = Pack(td._days, td._secsPacked, td._usecsPacked);
	if (numDiv == 0) return *this;
	Unpack(Pack(_days, _secsPacked, _usecsPacked) % numDiv, &_days, &_secsPacked, &_usecsPacked);
	return *this;
}

void TimeDelta::Regulate()
{
	Unpack(Pack(_days, _secsPacked, _usecsPacked), &_days, &_secsPacked, &_usecsPacked);
}

Int TimeDelta::Compare(const TimeDelta& td1, const TimeDelta& td2)
{
	Int result = 0;
	if ((result = td1._days - td2._days) != 0) {
	} else if ((result = td1._secsPacked - td2._secsPacked) != 0) {
	} else if ((result = td1._usecsPacked - td2._usecsPacked) != 0) {
	}
	return result;
}

Int64 TimeDelta::Pack(Int32 days, Int32 secsPacked, Int32 usecsPacked)
{
	Int64 num = usecsPacked;
	num += static_cast<Int64>(secsPacked) * 1000000;
	num += static_cast<Int64>(days) * 1000000 * 24 * 60 * 60;
	return num;
}

void TimeDelta::Unpack(Int64 num, Int32* pDays, Int32* pSecsPacked, Int32* pUsecsPacked)
{
	if (num >= 0) {
		*pUsecsPacked = static_cast<Int32>(num % 1000000);
		num /= 1000000;
		*pSecsPacked = static_cast<Int32>(num % (24 * 60 * 60));
		num /= 24 * 60 * 60;
		*pDays = static_cast<Int32>(num);
	} else {
		Int64 tmp = -num % (24LL * 60LL * 60LL * 1000000LL);
		*pDays = num / (24LL * 60LL * 60LL * 1000000LL);
		if (tmp == 0) {
			*pUsecsPacked = 0;
			*pSecsPacked = 0;
		} else {
			tmp = 24LL * 60LL * 60LL * 1000000LL - tmp;
			*pUsecsPacked = static_cast<Int32>(tmp % 1000000);
			*pSecsPacked = static_cast<Int32>(tmp / 1000000);
			(*pDays)--;
		}
	}
}

String TimeDelta::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("TimeDelta:%ddays,%02d:%02d:%02d.%03d",
		GetDays(), GetHours(), GetMins(), GetSecs(), GetMSecs());
	if (Int32 usecs = GetUSecs()) str.Format("%03d", usecs);
	return str;
}

}
