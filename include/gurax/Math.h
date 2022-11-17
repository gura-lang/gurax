//==============================================================================
// Math.h
//==============================================================================
#ifndef GURAX_MATH_H
#define GURAX_MATH_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Math
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Math {
public:
	static const Double E;
	static const Double PI;
public:
	static double RadToDeg(double n) { return 180 * n / PI; }
	static double DegToRad(double n) { return PI * n / 180; }
	static Int64 CalcGCD(Int64 a, Int64 b);
	static Int64 CalcLCM(Int64 a, Int64 b);
};

}

#endif
