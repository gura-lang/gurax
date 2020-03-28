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
	int _numer;
	int _denom;
public:
	// Constructor
	Rational() : _numer(0), _denom(1) {}
	Rational(int numer) : _numer(numer), _denom(1) {}
	Rational(int numer, int denom) : _numer(numer), _denom(denom) {}
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
	void SetNumer(int numer) { _numer = numer; }
	void SetDenom(int denom) { _denom = denom; }
	int GetNumer() const { return _numer; }
	int GetDenom() const { return _denom; }
public:
	Rational Reduce() const;
	static Rational MakeFromFP(Double num);
public:
	static void IssueError_DenominatorZero();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Rational& other) const { return this == &other; }
	bool IsEqualTo(const Rational& other) const { return IsIdentical(other); }
	bool IsLessThan(const Rational& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
