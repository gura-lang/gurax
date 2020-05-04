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

Rational Rational::Reduce() const
{
	return Rational();
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

}
