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
class GURAX_DLLDECLARE Rational : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Rational);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Rational");
public:
	// Constructor
	Rational() {}
	// Copy constructor/operator
	Rational(const Rational& src) = delete;
	Rational& operator=(const Rational& src) = delete;
	// Move constructor/operator
	Rational(Rational&& src) = delete;
	Rational& operator=(Rational&& src) noexcept = delete;
protected:
	~Rational() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Rational& other) const { return this == &other; }
	bool IsEqualTo(const Rational& other) const { return IsIdentical(other); }
	bool IsLessThan(const Rational& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
