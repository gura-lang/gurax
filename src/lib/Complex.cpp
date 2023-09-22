//==============================================================================
// Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Complex
//------------------------------------------------------------------------------
//String Complex::formatterFormat = "%g%+gj";
//String Complex::formatterFormat_Real = "%g";
//String Complex::formatterFormat_Imag = "%g";

const Complex Complex::Zero;

#if 0
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
#endif

String& Complex::ToString(String& str) const
{
	if (IsZero()) {
		Number<Double>::ToString(str, 0.);
	} else {
		if (real() != 0) {
			Number<Double>::ToString(str, real());
		}
		if (imag() != 0) {
			if (real() != 0 && imag() > 0) str += '+';
			Number<Double>::ToString(str, imag());
			str += 'j';
		}
	}	
	return str;
}

}
