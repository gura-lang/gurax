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
	static const Complex Zero;
public:
	using std::complex<Double>::complex;
	Complex() {}
	Complex(std::complex<Double>& num) : std::complex<Double>(num) {}
public:
	bool IsZero() const { return real() == 0. && imag() == 0.; }
	String ToString(const StringStyle& ss) const;
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
class GURAX_DLLDECLARE ComplexList : public ListBase<Complex> {
};

}

#endif
