//==============================================================================
// Math.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Math
//------------------------------------------------------------------------------
const Double Math::PI = 3.14159265358979323846;
const Double Math::E = 2.71828182845904523536;

Int64 Math::CalcGCD(Int64 a, Int64 b)
{
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == b) return a;
	Int64 left = a, right = b;
	if (a < b) {
		left = b, right = a;
	}
	Int64 gcd = right;
	for (;;) {
		Int64 div = left / right;
		Int64 rest = left - div * right;
		if (rest == 0) break;
		gcd = rest;
		left = right, right = rest;
	}
	return gcd;
}

Int64 Math::CalcLCM(Int64 a, Int64 b)
{
	return a * b / CalcGCD(a, b);
}

}
