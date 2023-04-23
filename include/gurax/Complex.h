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
	static String formatterFormat;
	static String formatterFormat_Real;
	static String formatterFormat_Imag;
public:
	static const Complex Zero;
public:
	using std::complex<Double>::complex;
	Complex() {}
	Complex(std::complex<Double>& num) : std::complex<Double>(num) {}
public:
	bool IsZero() const { return real() == 0. && imag() == 0.; }
	String& ToString(String& str) const;
	String ToString() const { String str; return ToString(str); }
public:
	explicit operator Bool() const { return !IsZero(); }
	explicit operator Int8() const { return 0; }
	explicit operator UInt8() const { return 0; }
	explicit operator Int16() const { return 0; }
	explicit operator UInt16() const { return 0; }
	explicit operator Int32() const { return 0; }
	explicit operator UInt32() const { return 0; }
	explicit operator Int64() const { return 0; }
	explicit operator UInt64() const { return 0; }
	explicit operator Float() const { return 0; }
	explicit operator Double() const { return 0; }
};

//------------------------------------------------------------------------------
// ComplexList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ComplexList : public ListBase<Complex> {
};

}

#endif
