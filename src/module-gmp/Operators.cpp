//==============================================================================
// Operators.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gmp)

Gurax_ImplementOpBinary(Add, mpz, mpz)
{
	const mpz_class& numL = Value_mpz::GetEntity(valueL);
	const mpz_class& numR = Value_mpz::GetEntity(valueR);
	return new Value_mpz(numL + numR);
}

Gurax_ImplementOpBinary(Sub, mpz, mpz)
{
	const mpz_class& numL = Value_mpz::GetEntity(valueL);
	const mpz_class& numR = Value_mpz::GetEntity(valueR);
	return new Value_mpz(numL - numR);
}

Gurax_ImplementOpBinary(Mul, mpz, mpz)
{
	const mpz_class& numL = Value_mpz::GetEntity(valueL);
	const mpz_class& numR = Value_mpz::GetEntity(valueR);
	return new Value_mpz(numL * numR);
}

Gurax_ImplementOpBinary(Mul, mpz, Number)
{
	const mpz_class& numL = Value_mpz::GetEntity(valueL);
	const Double numR = Value_Number::GetNumber<Double>(valueR);
	return new Value_mpz(numL * numR);
}

void AssignOperators()
{
	Gurax_AssignOpBinary(Add, mpz, mpz);
	Gurax_AssignOpBinary(Sub, mpz, mpz);
	Gurax_AssignOpBinary(Mul, mpz, mpz);
	Gurax_AssignOpBinary(Mul, mpz, Number);
}

Gurax_EndModuleScope(gmp)
