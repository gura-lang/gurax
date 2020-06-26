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
protected:
	static String _formatterFormat;
	static String _formatterFormat_Real;
	static String _formatterFormat_Imag;
public:
	using std::complex<Double>::complex;
	Complex() {}
	Complex(std::complex<Double>& num) : std::complex<Double>(num) {}
public:
	bool IsZero() const { return real() == 0. && imag() == 0.; }
	String ToString(const StringStyle& ss) const;
public:
	static void SetFormatterFormat(String formatterFormat) {
		_formatterFormat = formatterFormat;
	}
	static const char* GetFormatterFormat() {
		return _formatterFormat.c_str();
	}
	static void SetFormatterFormat_Real(String formatterFormat) {
		_formatterFormat_Real = formatterFormat;
	}
	static const char* GetFormatterFormat_Real() {
		return _formatterFormat_Real.c_str();
	}
	static void SetFormatterFormat_Imag(String formatterFormat) {
		_formatterFormat_Imag = formatterFormat;
	}
	static const char* GetFormatterFormat_Imag() {
		return _formatterFormat_Imag.c_str();
	}
};

//------------------------------------------------------------------------------
// ComplexList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ComplexList {
public:
	using V = std::vector<Complex>;
	V v;
};

}

#endif
