//==============================================================================
// Rational.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Rational
//------------------------------------------------------------------------------
const Rational Rational::Zero;
String Rational::formatterFormat("%lld/%lldr");
String Rational::formatterFormat_Int("%lldr");

Rational Rational::Canonicalize() const
{
	Int64 numer = _numer, denom = _denom;
	Canonicalize(&numer, &denom);
	return Rational(numer, denom);
}

Rational Rational::CanonicalizeQuick() const
{
	Int64 numer = _numer, denom = _denom;
	CanonicalizeQuick(&numer, &denom);
	return Rational(numer, denom);
}

void Rational::Canonicalize(Int64* pNumer, Int64* pDenom)
{
	Int64& numer = *pNumer;
	Int64& denom = *pDenom;
	if (numer == 0) {
		denom = 1;
	} else if (denom == 0) {
		numer = 0;
		denom = 1;
	} else {
		Int64 gcd = Math::CalcGCD(numer, denom);
		numer /= gcd;
		denom /= gcd;
		if (denom < 0) {
			numer = -numer;
			denom = -denom;
		}
	}
}

void Rational::CanonicalizeQuick(Int64* pNumer, Int64* pDenom)
{
	Int64& numer = *pNumer;
	Int64& denom = *pDenom;
	if (denom == 0) {
		numer = 0;
		denom = 1;
	} else if (denom < 0) {
		numer = -numer;
		denom = -denom;
	}
}

Rational Rational::MakeCanonicalized(Int64 numer, Int64 denom)
{
	Canonicalize(&numer, &denom);
	return Rational(numer, denom);
}

Rational Rational::MakeCanonicalizedQuick(Int64 numer, Int64 denom)
{
	CanonicalizeQuick(&numer, &denom);
	return Rational(numer, denom);
}

Rational Rational::MakeFromDouble(Double num)
{
	return Rational(static_cast<Int64>(num));
}

void Rational::IssueError_DenomZero()
{
	Error::Issue(ErrorType::DividedByZero, "denominator can't be zero");
}

String Rational::ToString(const StringStyle& ss) const
{
	return (GetDenom() == 1)?
		String().Format(formatterFormat_Int.c_str(), GetNumer()) :
		String().Format(formatterFormat.c_str(), GetNumer(), GetDenom());
}

Rational Rational::operator+() const
{
	return Canonicalize();
}

Rational Rational::operator-() const
{
	return Rational::MakeCanonicalized(-_numer, _denom);
}

Rational& Rational::operator+=(const Rational& rat)
{
	Int64 numerL = GetNumer(), denomL = GetDenom();
	Int64 numerR = rat.GetNumer(), denomR = rat.GetDenom();
	if (denomL == 0 || denomR == 0) {
		_numer = 0, _denom = 1;
	} else if (denomL == denomR) {
		_numer = numerL + numerR;
		Canonicalize(&_numer, &_denom);
	} else {
		_numer = numerL * denomR + numerR * denomL;
		_denom = denomL * denomR;
		Canonicalize(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator-=(const Rational& rat)
{
	Int64 numerL = GetNumer(), denomL = GetDenom();
	Int64 numerR = rat.GetNumer(), denomR = rat.GetDenom();
	if (denomL == 0 || denomR == 0) {
		_numer = 0, _denom = 1;
	} else if (denomL == denomR) {
		_numer = numerL - numerR;
		Canonicalize(&_numer, &_denom);
	} else {
		_numer = numerL * denomR - numerR * denomL;
		_denom = denomL * denomR;
		Canonicalize(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator*=(const Rational& rat)
{
	Int64 numerL = GetNumer(), denomL = GetDenom();
	Int64 numerR = rat.GetNumer(), denomR = rat.GetDenom();
	if (denomL == 0 || denomR == 0) {
		_numer = 0, _denom = 1;
	} else {
		_numer = numerL * numerR;
		_denom = denomL * denomR;
		Canonicalize(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator/=(const Rational& rat)
{
	Int64 numerL = GetNumer(), denomL = GetDenom();
	Int64 numerR = rat.GetNumer(), denomR = rat.GetDenom();
	if (denomL == 0 || numerR == 0) {
		_numer = 0, _denom = 1;
	} else {
		_numer = numerL * denomR;
		_denom = denomL * numerR;
		Canonicalize(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator/=(Double num)
{
	Int64 numCasted = static_cast<Int64>(num);
	if (num != numCasted) return operator/=(MakeFromDouble(num));
	Int64 numerL = GetNumer(), denomL = GetDenom();
	Int64 numerR = numCasted;
	if (denomL == 0 || numerR == 0) {
		_numer = 0, _denom = 1;
	} else {
		_numer = numerL;
		_denom = denomL * numerR;
		Canonicalize(&_numer, &_denom);
	}
	return *this;
}

Rational operator/(Double numL, const Rational& ratR)
{
	Int64 numCastedL = static_cast<Int64>(numL);
	if (numL != numCastedL) return operator/(Rational::MakeFromDouble(numL), ratR);
	// assumes that numL is an integer number
	Int64 numerL = numCastedL;
	Int64 numerR = ratR.GetNumer(), denomR = ratR.GetDenom();
	Int64 numer = 0, denom = 1;
	if (numerR != 0) {
		numer = numerL * denomR;
		denom = numerR;
		Rational::Canonicalize(&numer, &denom);
	}
	return Rational(numer, denom);

}

}
