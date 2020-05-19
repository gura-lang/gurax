//==============================================================================
// Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Complex
//------------------------------------------------------------------------------
String Complex::ToString(const StringStyle& ss) const
{
	String str;
	if (imag() == 0) {
		str.Printf("%g", real());
	} else if (real() == 0) {
		str.Printf("%gj", imag());
	} else {
		str.Printf("%g%+gj", real(), imag());
	}
	return str;
}

}
