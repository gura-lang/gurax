//==============================================================================
// Pixel.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Pixel
//------------------------------------------------------------------------------
String Pixel::ToString(const StringStyle& ss) const
{
	String str;
	str += "Pixel:[";
	str += _color.ToString(ss);
	str.Printf("]:x=%d:y=%d", _x, _y);
	return str;
}

}
