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
		str.Format("%g", real());
	} else if (real() == 0) {
		str.Format("%gj", imag());
	} else {
		str.Format("%g%+gj", real(), imag());
	}
	return str;
}

}
