//==============================================================================
// Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Complex
//------------------------------------------------------------------------------
String Complex::formatterFormat = "%g%+gj";
String Complex::formatterFormat_Real = "%g";
String Complex::formatterFormat_Imag = "%gj";

const Complex Complex::Zero;

String& Complex::ToString(String& str) const
{
	if (imag() == 0) {
		str.Format(formatterFormat_Real.c_str(), real());
	} else if (real() == 0) {
		str.Format(formatterFormat_Imag.c_str(), imag());
	} else {
		str.Format(formatterFormat.c_str(), real(), imag());
	}
	return str;
}

}
