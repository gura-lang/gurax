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
public:
	// Constructor
	TimeDelta() {}
	// Copy constructor/operator
	TimeDelta(const TimeDelta& src) = delete;
	TimeDelta& operator=(const TimeDelta& src) = delete;
	// Move constructor/operator
	TimeDelta(TimeDelta&& src) = delete;
	TimeDelta& operator=(TimeDelta&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~TimeDelta() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const TimeDelta* pTimeDelta) const { return this == pTimeDelta; }
	bool IsEqualTo(const TimeDelta* pTimeDelta) const { return IsIdentical(pTimeDelta); }
	bool IsLessThan(const TimeDelta* pTimeDelta) const { return this < pTimeDelta; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(timedelta)"; }
};

}

#endif
