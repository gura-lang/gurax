//==============================================================================
// Rational.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Rational
//------------------------------------------------------------------------------
const Rational Rational::Zero;

Rational Rational::Regulate() const
{
	Int64 numer = _numer, denom = _denom;
	Regulate(&numer, &denom);
	return Rational(numer, denom);
}

void Rational::Regulate(Int64* pNumer, Int64* pDenom)
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

Rational Rational::MakeRegulated(Int64 numer, Int64 denom)
{
	Regulate(&numer, &denom);
	return Rational(numer, denom);
}

Rational Rational::MakeFromDouble(Double num)
{
	return Rational();
}

void Rational::IssueError_DenominatorZero()
{
}

String Rational::ToString(const StringStyle& ss) const
{
	return "Rational";
}

Rational Rational::operator+() const
{
	return Regulate();
}

Rational Rational::operator-() const
{
	return Rational::MakeRegulated(-_numer, _denom);
}

Rational& Rational::operator+=(const Rational& r)
{
	Int64 numerA = GetNumer(), denomA = GetDenom();
	Int64 numerB = r.GetNumer(), denomB = r.GetDenom();
	if (denomA == 0 || denomB == 0) {
		_numer = 0, _denom = 1;
	} else if (denomA == denomB) {
		_numer = numerA + numerB;
		Regulate(&_numer, &_denom);
	} else {
		_numer = numerA * denomB + numerB * denomA;
		_denom = denomA * denomB;
		Regulate(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator-=(const Rational& r)
{
	Int64 numerA = GetNumer(), denomA = GetDenom();
	Int64 numerB = r.GetNumer(), denomB = r.GetDenom();
	if (denomA == 0 || denomB == 0) {
		_numer = 0, _denom = 1;
	} else if (denomA == denomB) {
		_numer = numerA - numerB;
		Regulate(&_numer, &_denom);
	} else {
		_numer = numerA * denomB - numerB * denomA;
		_denom = denomA * denomB;
		Regulate(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator*=(const Rational& r)
{
	Int64 numerA = GetNumer(), denomA = GetDenom();
	Int64 numerB = r.GetNumer(), denomB = r.GetDenom();
	if (denomA == 0 || denomB == 0) {
		_numer = 0, _denom = 1;
	} else {
		_numer = numerA * numerB;
		_denom = denomA * denomB;
		Regulate(&_numer, &_denom);
	}
	return *this;
}

Rational& Rational::operator/=(const Rational& r)
{
	Int64 numerA = GetNumer(), denomA = GetDenom();
	Int64 numerB = r.GetNumer(), denomB = r.GetDenom();
	if (denomA == 0 || numerB == 0) {
		_numer = 0, _denom = 1;
	} else {
		_numer = numerA * denomB;
		_denom = denomA * numerB;
		Regulate(&_numer, &_denom);
	}
	return *this;
}

#if 0
bool operator==(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax == bx;
}

bool operator!=(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax != bx;
}

bool operator<(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax < bx;
}

bool operator>(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax > bx;
}

bool operator<=(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax <= bx;
}

bool operator>=(const Rational& a, const Rational& b)
{
	int ax = a.GetNumer() * b.GetDenom(), bx = b.GetNumer() * a.GetDenom();
	return ax >=  bx;
}
#endif

}
