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

String Complex::ToString(const StringStyle& ss) const
{
	String str;
	if (imag() == 0) {
		str.Format(GetFormatterFormat_Real(), real());
	} else if (real() == 0) {
		str.Format(GetFormatterFormat_Imag(), imag());
	} else {
		str.Format(GetFormatterFormat(), real(), imag());
	}
	return str;
}

}
