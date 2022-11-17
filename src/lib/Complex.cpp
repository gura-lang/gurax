//==============================================================================
// Complex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Complex
//------------------------------------------------------------------------------
String Complex::_formatterFormat = "%g%+gj";
String Complex::_formatterFormat_Real = "%g";
String Complex::_formatterFormat_Imag = "%gj";

const Complex Complex::Zero;

String Complex::ToString(const StringStyle& ss) const
{
	if (imag() == 0) {
		return String().Format(GetFormatterFormat_Real(), real());
	} else if (real() == 0) {
		return String().Format(GetFormatterFormat_Imag(), imag());
	} else {
		return String().Format(GetFormatterFormat(), real(), imag());
	}
}

}
