//==============================================================================
// Random.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------
Random::Random()
{
	::gmp_randinit_default(_state);
}

Random::~Random()
{
	::gmp_randclear(_state);
}

void Random::SetSeed(const mpz_class& seed)
{
	::gmp_randseed(_state, seed.get_mpz_t());
}

mpf_class Random::GenFloat(mp_bitcnt_t prec)
{
	mpf_t num;
	mpf_init(num);
	mpf_urandomb(num, _state, prec);
	return mpf_class(num);
}

mpz_class Random::GenInt(const mpz_class& range)
{
	mpz_t num;
	mpz_init(num);
	mpz_urandomm(num, _state, range.get_mpz_t());
	return mpz_class(num);
}

mpz_class Random::GenIntBits(mp_bitcnt_t bits)
{
	mpz_t num;
	mpz_init(num);
	mpz_urandomb(num, _state, bits);
	return mpz_class(num);
}

String Random::ToString(const StringStyle& ss) const
{
	return String().Format("gmp.Random");
}

Gurax_EndModuleScope(gmp)
