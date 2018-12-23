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
};

}

#endif
