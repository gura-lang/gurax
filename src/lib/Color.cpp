//==============================================================================
// Color.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
const Color Color::zero(	  0,   0,   0,   0);
const Color Color::black(	  0,   0,   0, 255);
const Color Color::maroon(	128,   0,   0, 255);
const Color Color::green(	  0, 128,   0, 255);
const Color Color::olive(	128, 128,   0, 255);
const Color Color::navy(	  0,   0, 128, 255);
const Color Color::purple(	128,   0, 128, 255);
const Color Color::teal(	  0, 128, 128, 255);
const Color Color::gray(	128, 128, 128, 255);
const Color Color::silver(	192, 192, 192, 255);
const Color Color::red(		255,   0,   0, 255);
const Color Color::lime(	  0, 255,   0, 255);
const Color Color::yellow(	255, 255,   0, 255);
const Color Color::blue(	  0,   0, 255, 255);
const Color Color::fuchsia(	255,   0, 255, 255);
const Color Color::aqua(	  0, 255, 255, 255);
const Color Color::white(	255, 255, 255, 255);

String Color::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Color:#%02x%02x%02x,a:%02x", GetR(), GetG(), GetB(), GetA());
	return str;
}

}
