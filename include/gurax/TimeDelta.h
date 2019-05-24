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
	Int32 _days;	// -999999999 <= _days <= 999999999
	Int32 _secs;	// 0 <= _secs <= 3600 * 24 - 1
	Int32 _usecs;	// 0 <= _usecs <= 999999
public:
	// Constructor
	TimeDelta(Int32 days = 0, Int32 secs = 0, Int32 usecs = 0);
	// Copy constructor/operator
	TimeDelta(const TimeDelta& src) : _days(src._days), _secs(src._secs), _usecs(src._usecs) {}
	TimeDelta& operator=(const TimeDelta& src) {
		_days = src._days, _secs = src._secs, _usecs = src._usecs;
		return *this;
	}
	// Move constructor/operator
	TimeDelta(TimeDelta&& src) : _days(src._days), _secs(src._secs), _usecs(src._usecs) {}
	TimeDelta& operator=(TimeDelta&& src) noexcept {
		_days = src._days, _secs = src._secs, _usecs = src._usecs;
		return *this;
	}
protected:
	// Destructor
	virtual ~TimeDelta() = default;
public:
	Int32 GetDays() const		{ return _days; }
	Int8 GetHours() const		{ return static_cast<Int8>(_secs / 3600); }			// 0-23
	Int8 GetMins() const		{ return static_cast<Int8>((_secs / 60) % 60); }	// 0-59
	Int8 GetSecs() const		{ return static_cast<Int8>(_secs % 60); }			// 0-59
	Int32 GetSecsRaw() const	{ return _secs; }
	Int32 GetMSecs() const		{ return _usecs / 1000; }
	Int32 GetUSecs() const		{ return _usecs; }
public:
	void SetDays(Int32 days)	{ _days = days;	}
	void SetHours(Int32 hours)	{ _secs = CalcSecsRaw(hours, GetMins(), GetSecs()); Regulate(); }
	void SetMins(Int32 mins)	{ _secs = CalcSecsRaw(GetHours(), mins, GetSecs()); Regulate(); }
	void SetSecs(Int32 secs)	{ _secs = CalcSecsRaw(GetHours(), GetMins(), secs); Regulate(); }
	void SetSecsRaw(Int32 secs)	{ _secs = secs; Regulate(); }
	void SetMSecs(Int32 msecs)	{ _usecs = msecs * 1000; Regulate(); }
	void SetUSecs(Int32 usecs)	{ _usecs = usecs; Regulate(); }
public:
	TimeDelta& operator+=(const TimeDelta& td);
	TimeDelta& operator-=(const TimeDelta& td);
public:
	void Regulate();
	static int Compare(const TimeDelta& td1, const TimeDelta& td2);
	static Int32 CalcSecsRaw(Int32 hours, Int32 mins, Int32 secs) {
		return hours * 3600 + mins * 60 + secs;
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TimeDelta& timeDelta) const { return this == &timeDelta; }
	bool IsEqualTo(const TimeDelta& timeDelta) const { return IsIdentical(timeDelta); }
	bool IsLessThan(const TimeDelta& timeDelta) const { return this < &timeDelta; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
