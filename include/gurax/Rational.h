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
public:
	Rational Regulate() const;
	static void Regulate(Int64* pNumer, Int64* pDenom);
	static Rational MakeRegulated(Int64 numer, Int64 denom);
	static Rational MakeFromDouble(Double num);
public:
	Rational operator+() const;
	Rational operator-() const;
	Rational& operator+=(const Rational& rat);
	Rational& operator-=(const Rational& rat);
	Rational& operator*=(const Rational& rat);
	Rational& operator/=(const Rational& rat);
public:
	static void IssueError_DenominatorZero();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Rational& other) const { return this == &other; }
	bool IsEqualTo(const Rational& other) const { return IsIdentical(other); }
	bool IsLessThan(const Rational& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Rational operator+(const Rational& ratA, const Rational& ratB) { return Rational(ratA) += ratB; }
Rational operator-(const Rational& ratA, const Rational& ratB) { return Rational(ratA) -= ratB; }
Rational operator*(const Rational& ratA, const Rational& ratB) { return Rational(ratA) *= ratB; }
Rational operator/(const Rational& ratA, const Rational& ratB) { return Rational(ratA) /= ratB; }

bool operator==(const Rational& ratA, const Rational& ratB) {
	return ratA.GetNumer() * ratB.GetDenom() == ratA.GetDenom() * ratB.GetNumer();
}
bool operator<(const Rational& ratA, const Rational& ratB) {
	return ratA.GetNumer() * ratB.GetDenom() < ratA.GetDenom() * ratB.GetNumer();
}
bool operator!=(const Rational& ratA, const Rational& ratB) { return !operator==(ratA, ratB); }
bool operator>(const Rational& ratA, const Rational& ratB) { return operator<(ratB, ratA); }
bool operator<=(const Rational& ratA, const Rational& ratB) { return !operator>(ratA, ratB); }
bool operator>=(const Rational& ratA, const Rational& ratB) { return !operator<(ratA, ratB); }

}

#endif
