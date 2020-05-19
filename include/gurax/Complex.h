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
	Complex() {}
	Complex(std::complex<Double>& num) : std::complex<Double>(num) {}
public:
	bool IsZero() const { return real() == 0. && imag() == 0.; }
	String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// ComplexList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ComplexList : public std::vector<Complex>
{
public:
	using std::vector<Complex>::vector;
};

}

#endif
