//==============================================================================
// Rational.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Rational
//------------------------------------------------------------------------------
Rational Rational::Reduce() const
{
	return Rational();
}

Rational Rational::MakeFromFP(Double num)
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
