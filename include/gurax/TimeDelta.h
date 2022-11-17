//==============================================================================
// TimeDelta.h
//==============================================================================
#ifndef GURAX_TIMEDELTA_H
#define GURAX_TIMEDELTA_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// TimeDelta
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TimeDelta : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(TimeDelta);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("TimeDelta");
private:
	Int32 _days;
	Int32 _secsPacked;	// regulated within [0, 24 * 60 * 60 - 1]
	Int32 _usecsPacked;	// regulated within [0, 999999]
public:
	// Constructor
	TimeDelta(Int32 days = 0, Int32 secs = 0, Int32 usecs = 0);
	// Copy constructor/operator
	TimeDelta(const TimeDelta& src) : _days(src._days), _secsPacked(src._secsPacked), _usecsPacked(src._usecsPacked) {}
	TimeDelta& operator=(const TimeDelta& src) {
		_days = src._days, _secsPacked = src._secsPacked, _usecsPacked = src._usecsPacked;
		return *this;
	}
	// Move constructor/operator
	TimeDelta(TimeDelta&& src) noexcept : _days(src._days), _secsPacked(src._secsPacked), _usecsPacked(src._usecsPacked) {}
	TimeDelta& operator=(TimeDelta&& src) noexcept {
		_days = src._days, _secsPacked = src._secsPacked, _usecsPacked = src._usecsPacked;
		return *this;
	}
protected:
	// Destructor
	virtual ~TimeDelta() = default;
public:
	Int32 GetDays() const			{ return _days; }
	Int8 GetHours() const			{ return static_cast<Int8>(_secsPacked / 3600); }		// 0-23
	Int8 GetMins() const			{ return static_cast<Int8>((_secsPacked / 60) % 60); }	// 0-59
	Int8 GetSecs() const			{ return static_cast<Int8>(_secsPacked % 60); }			// 0-59
	Int32 GetSecsPacked() const		{ return _secsPacked; }
	Int32 GetMSecs() const			{ return _usecsPacked / 1000; }
	Int32 GetUSecs() const			{ return _usecsPacked % 1000; }
	Int32 GetUSecsPacked() const	{ return _usecsPacked; }
public:
	void SetDays(Int32 days)		{ _days = days;	}
	void SetHours(Int32 hours)		{ _secsPacked = CalcSecsPacked(hours, GetMins(), GetSecs()); Regulate(); }
	void SetMins(Int32 mins)		{ _secsPacked = CalcSecsPacked(GetHours(), mins, GetSecs()); Regulate(); }
	void SetSecs(Int32 secs)		{ _secsPacked = CalcSecsPacked(GetHours(), GetMins(), secs); Regulate(); }
	void SetSecsPacked(Int32 secsPacked) { _secsPacked = secsPacked; Regulate(); }
	void SetMSecs(Int32 msecs)		{ _usecsPacked = CalcUSecsPacked(msecs, GetUSecs()); Regulate(); }
	void SetUSecs(Int32 usecs)		{ _usecsPacked = CalcUSecsPacked(GetMSecs(), usecs); Regulate(); }
	void SetUSecsPacked(Int32 usecsPacked) { _usecsPacked = usecsPacked; Regulate(); }
public:
	bool IsZero() const				{ return _days == 0 && _secsPacked == 0 && _usecsPacked == 0; }
public:
	TimeDelta* operator-() const;
	TimeDelta& operator+=(const TimeDelta& td);
	TimeDelta& operator-=(const TimeDelta& td);
	TimeDelta& operator*=(Double n);
	TimeDelta& operator/=(Double n);
	Double operator/(const TimeDelta& td) const;
	TimeDelta& operator%=(const TimeDelta& td);
	bool operator==(const TimeDelta& td) const { return Compare(*this, td) == 0; }
	bool operator!=(const TimeDelta& td) const { return Compare(*this, td) != 0; }
	bool operator<(const TimeDelta& td) const  { return Compare(*this, td) < 0;  }
	bool operator<=(const TimeDelta& td) const { return Compare(*this, td) <= 0; }
	bool operator>(const TimeDelta& td) const  { return Compare(*this, td) > 0;  }
	bool operator>=(const TimeDelta& td) const { return Compare(*this, td) >= 0; }
public:
	void Regulate();
	static Int32 CalcSecsPacked(Int32 hours, Int32 mins, Int32 secs) {
		return hours * 3600 + mins * 60 + secs;
	}
	static Int32 CalcUSecsPacked(Int32 msecs, Int32 usecs) { return msecs * 1000 + usecs; }
	static Int Compare(const TimeDelta& td1, const TimeDelta& td2);
	static Int64 Pack(Int32 days, Int32 secsPacked, Int32 usecsPacked);
	static void Unpack(Int64 num, Int32* pDays, Int32* pSecsPacked, Int32* pUsecsPacked);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TimeDelta& timeDelta) const { return this == &timeDelta; }
	bool IsEqualTo(const TimeDelta& timeDelta) const { return IsIdentical(timeDelta); }
	bool IsLessThan(const TimeDelta& timeDelta) const { return this < &timeDelta; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
