//==============================================================================
// Random.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_RANDOM_H
#define GURAX_MODULE_GMP_RANDOM_H
#include <gurax.h>
#include <gmpxx.h>

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Random : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Random);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("gmp.Random");
protected:
	gmp_randstate_t _state;
public:
	// Constructor
	Random();
	// Copy constructor/operator
	Random(const Random& src) = delete;
	Random& operator=(const Random& src) = delete;
	// Move constructor/operator
	Random(Random&& src) noexcept = delete;
	Random& operator=(Random&& src) noexcept = delete;
protected:
	~Random();
public:
	void SetSeed(const mpz_class& seed);
	mpf_class GenFloat(mp_bitcnt_t prec);
	mpz_class GenInt(const mpz_class& range);
	mpz_class GenIntBits(mp_bitcnt_t bits);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Random& other) const { return this == &other; }
	bool IsEqualTo(const Random& other) const { return IsIdentical(other); }
	bool IsLessThan(const Random& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};



Gurax_EndModuleScope(gmp)

#endif
