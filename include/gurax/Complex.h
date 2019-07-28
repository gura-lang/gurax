//==============================================================================
// Complex
//==============================================================================
#ifndef GURAX_COMPLEX_H
#define GURAX_COMPLEX_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Complex
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Complex : public std::complex<Double> {
public:
	using std::complex<Double>::complex;
};

}

#endif
