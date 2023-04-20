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

String Complex::ToString(const StringStyle& ss) const
{
	if (imag() == 0) {
		return String().Format(formatterFormat_Real.c_str(), real());
	} else if (real() == 0) {
		return String().Format(formatterFormat_Imag.c_str(), imag());
	} else {
		return String().Format(formatterFormat.c_str(), real(), imag());
	}
}

}
