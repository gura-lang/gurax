//==============================================================================
// Rational.h
//==============================================================================
#ifndef GURAX_RATIONAL_H
#define GURAX_RATIONAL_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Rational
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Rational {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Rational");
protected:
	Int64 _numer;
	Int64 _denom;
public:
	static String formatterFormat;
	static String formatterFormat_Int;
public:
	static const Rational Zero;
public:
	// Constructor
	Rational() : _numer(0), _denom(1) {}
	Rational(Int64 numer) : _numer(numer), _denom(1) {}
	Rational(Int64 numer, Int64 denom) : _numer(numer), _denom(denom) {}
	// Copy constructor/operator
	Rational(const Rational& src) : _numer(src._numer), _denom(src._denom) {}
	Rational& operator=(const Rational& src) {
		_numer = src._numer, _denom = src._denom;
		return *this;
	}
	// Move constructor/operator
	Rational(Rational&& src) noexcept : _numer(src._numer), _denom(src._denom) {}
	Rational& operator=(Rational&& src) noexcept {
		_numer = src._numer, _denom = src._denom;
		return *this;
	}
public:
	~Rational() = default;
public:
	void SetNumer(Int64 numer) { _numer = numer; }
	void SetDenom(Int64 denom) { _denom = denom; }
	Int64 GetNumer() const { return _numer; }
	Int64 GetDenom() const { return _denom; }
	Double ToDouble() const { return static_cast<Double>(_numer) / _denom; }
	int GetSign() const { return (_numer == 0)? 0 : (_numer > 0)? +1 : -1; }
	bool IsInteger() const { return _denom == 1; }
	bool IsZero() const { return _numer == 0; }
	bool IsPos() const { return _numer > 0; }
	bool IsNeg() const { return _numer < 0; }
	bool IsNonPos() const { return _numer <= 0; }
	bool IsNonNeg() const { return _numer >= 0; }
public:
	Rational Canonicalize() const;
	Rational CanonicalizeQuick() const;
	static void Canonicalize(Int64* pNumer, Int64* pDenom);
	static void CanonicalizeQuick(Int64* pNumer, Int64* pDenom);
	static Rational MakeCanonicalized(Int64 numer, Int64 denom);
	static Rational MakeCanonicalizedQuick(Int64 numer, Int64 denom);
	static Rational MakeFromDouble(Double num);
public:
	Rational operator+() const;
	Rational operator-() const;
	Rational& operator+=(const Rational& rat);
	Rational& operator-=(const Rational& rat);
	Rational& operator*=(const Rational& rat);
	Rational& operator/=(const Rational& rat);
	Rational& operator/=(Double num);
public:
	static void IssueError_DenomZero();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Rational& other) const { return this == &other; }
	bool IsEqualTo(const Rational& other) const { return IsIdentical(other); }
	bool IsLessThan(const Rational& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

inline Rational operator+(const Rational& ratL, const Rational& ratR) { return Rational(ratL) += ratR; }
inline Rational operator-(const Rational& ratL, const Rational& ratR) { return Rational(ratL) -= ratR; }
inline Rational operator*(const Rational& ratL, const Rational& ratR) { return Rational(ratL) *= ratR; }
inline Rational operator/(const Rational& ratL, const Rational& ratR) { return Rational(ratL) /= ratR; }
inline Rational operator/(const Rational& ratL, const Double numR) { return Rational(ratL) /= numR; }
GURAX_DLLDECLARE Rational operator/(Double numL, const Rational& ratR);

inline bool operator==(const Rational& ratL, const Rational& ratR) {
	return ratL.GetNumer() * ratR.GetDenom() == ratL.GetDenom() * ratR.GetNumer();
}
inline bool operator<(const Rational& ratL, const Rational& ratR) {
	return ratL.GetNumer() * ratR.GetDenom() < ratL.GetDenom() * ratR.GetNumer();
}
inline bool operator!=(const Rational& ratL, const Rational& ratR) { return !operator==(ratL, ratR); }
inline bool operator>(const Rational& ratL, const Rational& ratR) { return operator<(ratR, ratL); }
inline bool operator<=(const Rational& ratL, const Rational& ratR) { return !operator>(ratL, ratR); }
inline bool operator>=(const Rational& ratL, const Rational& ratR) { return !operator<(ratL, ratR); }

}

#endif
