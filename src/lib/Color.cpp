//==============================================================================
// Color.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
// These Color names come from: https://www.w3.org/TR/css-color-3/
const Color Color::zero		(  0,   0,   0,   0);
const Color Color::black	(  0,   0,   0, 255);
const Color Color::silver	(192, 192, 192, 255);
const Color Color::gray		(128, 128, 128, 255);
const Color Color::white	(255, 255, 255, 255);
const Color Color::maroon	(128,   0,   0, 255);
const Color Color::red		(255,   0,   0, 255);
const Color Color::purple	(128,   0, 128, 255);
const Color Color::fuchsia	(255,   0, 255, 255);
const Color Color::green	(  0, 128,   0, 255);
const Color Color::lime		(  0, 255,   0, 255);
const Color Color::olive	(128, 128,   0, 255);
const Color Color::yellow	(255, 255,   0, 255);
const Color Color::navy		(  0,   0, 128, 255);
const Color Color::blue		(  0,   0, 255, 255);
const Color Color::teal		(  0, 128, 128, 255);
const Color Color::aqua		(  0, 255, 255, 255);

const Color::NamedEntry Color::_namedEntries[] = {
	{ "aliceblue",				PackRGBA(240, 248, 255, 255) },
	{ "antiquewhite",			PackRGBA(250, 235, 215, 255) },
	{ "aqua",					PackRGBA(  0, 255, 255, 255) },
	{ "aquamarine",				PackRGBA(127, 255, 212, 255) },
	{ "azure",					PackRGBA(240, 255, 255, 255) },
	{ "beige",					PackRGBA(245, 245, 220, 255) },
	{ "bisque",					PackRGBA(255, 228, 196, 255) },
	{ "black",					PackRGBA(  0,   0,   0, 255) },
	{ "blanchedalmond",			PackRGBA(255, 235, 205, 255) },
	{ "blue",					PackRGBA(  0,   0, 255, 255) },
	{ "blueviolet",				PackRGBA(138,  43, 226, 255) },
	{ "brown",					PackRGBA(165,  42,  42, 255) },
	{ "burlywood",				PackRGBA(222, 184, 135, 255) },
	{ "cadetblue",				PackRGBA( 95, 158, 160, 255) },
	{ "chartreuse",				PackRGBA(127, 255,   0, 255) },
	{ "chocolate",				PackRGBA(210, 105,  30, 255) },
	{ "coral",					PackRGBA(255, 127,  80, 255) },
	{ "cornflowerblue",			PackRGBA(100, 149, 237, 255) },
	{ "cornsilk",				PackRGBA(255, 248, 220, 255) },
	{ "crimson",				PackRGBA(220,  20,  60, 255) },
	{ "cyan",					PackRGBA(  0, 255, 255, 255) },
	{ "darkblue",				PackRGBA(  0,   0, 139, 255) },
	{ "darkcyan",				PackRGBA(  0, 139, 139, 255) },
	{ "darkgoldenrod",			PackRGBA(184, 134,  11, 255) },
	{ "darkgray",				PackRGBA(169, 169, 169, 255) },
	{ "darkgreen",				PackRGBA(  0, 100,   0, 255) },
	{ "darkgrey",				PackRGBA(169, 169, 169, 255) },
	{ "darkkhaki",				PackRGBA(189, 183, 107, 255) },
	{ "darkmagenta",			PackRGBA(139,   0, 139, 255) },
	{ "darkolivegreen",			PackRGBA( 85, 107,  47, 255) },
	{ "darkorange",				PackRGBA(255, 140,   0, 255) },
	{ "darkorchid",				PackRGBA(153,  50, 204, 255) },
	{ "darkred",				PackRGBA(139,   0,   0, 255) },
	{ "darksalmon",				PackRGBA(233, 150, 122, 255) },
	{ "darkseagreen",			PackRGBA(143, 188, 143, 255) },
	{ "darkslateblue",			PackRGBA( 72,  61, 139, 255) },
	{ "darkslategray",			PackRGBA( 47,  79,  79, 255) },
	{ "darkslategrey",			PackRGBA( 47,  79,  79, 255) },
	{ "darkturquoise",			PackRGBA(  0, 206, 209, 255) },
	{ "darkviolet",				PackRGBA(148,   0, 211, 255) },
	{ "deeppink",				PackRGBA(255,  20, 147, 255) },
	{ "deepskyblue",			PackRGBA(  0, 191, 255, 255) },
	{ "dimgray",				PackRGBA(105, 105, 105, 255) },
	{ "dimgrey",				PackRGBA(105, 105, 105, 255) },
	{ "dodgerblue",				PackRGBA( 30, 144, 255, 255) },
	{ "firebrick",				PackRGBA(178,  34,  34, 255) },
	{ "floralwhite",			PackRGBA(255, 250, 240, 255) },
	{ "forestgreen",			PackRGBA( 34, 139,  34, 255) },
	{ "fuchsia",				PackRGBA(255,   0, 255, 255) },
	{ "gainsboro",				PackRGBA(220, 220, 220, 255) },
	{ "ghostwhite",				PackRGBA(248, 248, 255, 255) },
	{ "gold",					PackRGBA(255, 215,   0, 255) },
	{ "goldenrod",				PackRGBA(218, 165,  32, 255) },
	{ "gray",					PackRGBA(128, 128, 128, 255) },
	{ "green",					PackRGBA(  0, 128,   0, 255) },
	{ "greenyellow",			PackRGBA(173, 255,  47, 255) },
	{ "grey",					PackRGBA(128, 128, 128, 255) },
	{ "honeydew",				PackRGBA(240, 255, 240, 255) },
	{ "hotpink",				PackRGBA(255, 105, 180, 255) },
	{ "indianred",				PackRGBA(205,  92,  92, 255) },
	{ "indigo",					PackRGBA( 75,   0, 130, 255) },
	{ "ivory",					PackRGBA(255, 255, 240, 255) },
	{ "khaki",					PackRGBA(240, 230, 140, 255) },
	{ "lavender",				PackRGBA(230, 230, 250, 255) },
	{ "lavenderblush",			PackRGBA(255, 240, 245, 255) },
	{ "lawngreen",				PackRGBA(124, 252,   0, 255) },
	{ "lemonchiffon",			PackRGBA(255, 250, 205, 255) },
	{ "lightblue",				PackRGBA(173, 216, 230, 255) },
	{ "lightcoral",				PackRGBA(240, 128, 128, 255) },
	{ "lightcyan",				PackRGBA(224, 255, 255, 255) },
	{ "lightgoldenrodyellow",	PackRGBA(250, 250, 210, 255) },
	{ "lightgray",				PackRGBA(211, 211, 211, 255) },
	{ "lightgreen",				PackRGBA(144, 238, 144, 255) },
	{ "lightgrey",				PackRGBA(211, 211, 211, 255) },
	{ "lightpink",				PackRGBA(255, 182, 193, 255) },
	{ "lightsalmon",			PackRGBA(255, 160, 122, 255) },
	{ "lightseagreen",			PackRGBA( 32, 178, 170, 255) },
	{ "lightskyblue",			PackRGBA(135, 206, 250, 255) },
	{ "lightslategray",			PackRGBA(119, 136, 153, 255) },
	{ "lightslategrey",			PackRGBA(119, 136, 153, 255) },
	{ "lightsteelblue",			PackRGBA(176, 196, 222, 255) },
	{ "lightyellow",			PackRGBA(255, 255, 224, 255) },
	{ "lime",					PackRGBA(  0, 255,   0, 255) },
	{ "limegreen",				PackRGBA( 50, 205,  50, 255) },
	{ "linen",					PackRGBA(250, 240, 230, 255) },
	{ "magenta",				PackRGBA(255,   0, 255, 255) },
	{ "maroon",					PackRGBA(128,   0,   0, 255) },
	{ "mediumaquamarine",		PackRGBA(102, 205, 170, 255) },
	{ "mediumblue",				PackRGBA(  0,   0, 205, 255) },
	{ "mediumorchid",			PackRGBA(186,  85, 211, 255) },
	{ "mediumpurple",			PackRGBA(147, 112, 219, 255) },
	{ "mediumseagreen",			PackRGBA( 60, 179, 113, 255) },
	{ "mediumslateblue",		PackRGBA(123, 104, 238, 255) },
	{ "mediumspringgreen",		PackRGBA(  0, 250, 154, 255) },
	{ "mediumturquoise",		PackRGBA( 72, 209, 204, 255) },
	{ "mediumvioletred",		PackRGBA(199,  21, 133, 255) },
	{ "midnightblue",			PackRGBA( 25,  25, 112, 255) },
	{ "mintcream",				PackRGBA(245, 255, 250, 255) },
	{ "mistyrose",				PackRGBA(255, 228, 225, 255) },
	{ "moccasin",				PackRGBA(255, 228, 181, 255) },
	{ "navajowhite",			PackRGBA(255, 222, 173, 255) },
	{ "navy",					PackRGBA(  0,   0, 128, 255) },
	{ "oldlace",				PackRGBA(253, 245, 230, 255) },
	{ "olive",					PackRGBA(128, 128,   0, 255) },
	{ "olivedrab",				PackRGBA(107, 142,  35, 255) },
	{ "orange",					PackRGBA(255, 165,   0, 255) },
	{ "orangered",				PackRGBA(255,  69,   0, 255) },
	{ "orchid",					PackRGBA(218, 112, 214, 255) },
	{ "palegoldenrod",			PackRGBA(238, 232, 170, 255) },
	{ "palegreen",				PackRGBA(152, 251, 152, 255) },
	{ "paleturquoise",			PackRGBA(175, 238, 238, 255) },
	{ "palevioletred",			PackRGBA(219, 112, 147, 255) },
	{ "papayawhip",				PackRGBA(255, 239, 213, 255) },
	{ "peachpuff",				PackRGBA(255, 218, 185, 255) },
	{ "peru",					PackRGBA(205, 133,  63, 255) },
	{ "pink",					PackRGBA(255, 192, 203, 255) },
	{ "plum",					PackRGBA(221, 160, 221, 255) },
	{ "powderblue",				PackRGBA(176, 224, 230, 255) },
	{ "purple",					PackRGBA(128,   0, 128, 255) },
	{ "red",					PackRGBA(255,   0,   0, 255) },
	{ "rosybrown",				PackRGBA(188, 143, 143, 255) },
	{ "royalblue",				PackRGBA( 65, 105, 225, 255) },
	{ "saddlebrown",			PackRGBA(139,  69,  19, 255) },
	{ "salmon",					PackRGBA(250, 128, 114, 255) },
	{ "sandybrown",				PackRGBA(244, 164,  96, 255) },
	{ "seagreen",				PackRGBA( 46, 139,  87, 255) },
	{ "seashell",				PackRGBA(255, 245, 238, 255) },
	{ "sienna",					PackRGBA(160,  82,  45, 255) },
	{ "silver",					PackRGBA(192, 192, 192, 255) },
	{ "skyblue",				PackRGBA(135, 206, 235, 255) },
	{ "slateblue",				PackRGBA(106,  90, 205, 255) },
	{ "slategray",				PackRGBA(112, 128, 144, 255) },
	{ "slategrey",				PackRGBA(112, 128, 144, 255) },
	{ "snow",					PackRGBA(255, 250, 250, 255) },
	{ "springgreen",			PackRGBA(  0, 255, 127, 255) },
	{ "steelblue",				PackRGBA( 70, 130, 180, 255) },
	{ "tan",					PackRGBA(210, 180, 140, 255) },
	{ "teal",					PackRGBA(  0, 128, 128, 255) },
	{ "thistle",				PackRGBA(216, 191, 216, 255) },
	{ "tomato",					PackRGBA(255,  99,  71, 255) },
	{ "turquoise",				PackRGBA( 64, 224, 208, 255) },
	{ "violet",					PackRGBA(238, 130, 238, 255) },
	{ "wheat",					PackRGBA(245, 222, 179, 255) },
	{ "white",					PackRGBA(255, 255, 255, 255) },
	{ "whitesmoke",				PackRGBA(245, 245, 245, 255) },
	{ "yellow",					PackRGBA(255, 255,   0, 255) },
	{ "yellowgreen",			PackRGBA(154, 205,  50, 255) },
	{ "zero",					PackRGBA(  0,   0,   0,   0) },
};

void Color::Bootup()
{
	for (size_t i = 0; i < Gurax_ArraySizeOf(_namedEntries); i++) {
		const NamedEntry& namedEntry = _namedEntries[i];
		Color color(namedEntry.packed);
		ColorStringMap::Instance.GetMap()[namedEntry.name] = color;
		ColorSymbolMap::Instance.GetMap()[Symbol::Add(namedEntry.name)] = color;
	}
}

bool Color::FromString(Color& color, const char* str, UInt8 alpha)
{
	auto HexToUInt8 = [](const char* str, UInt8* pNum) {
		int nibbleH = String::ConvHexDigit(*str);
		int nibbleL = String::ConvHexDigit(*(str + 1));
		if (nibbleH < 0 || nibbleL < 0) {
			Error::Issue(ErrorType::ValueError, "invalid format of color name");
			return false;
		}
		*pNum = static_cast<UInt8>((nibbleH << 4) | nibbleL);
		return true;
	};
	if (*str == '#') {
		UInt8 r = 0, g = 0, b =0;
		str++;
		size_t len = ::strlen(str);
		if (len == 6) {
			if (!HexToUInt8(str, &r) || !HexToUInt8(str + 2, &g) || !HexToUInt8(str + 4, &b)) {
				return false;
			}
		} else {
			Error::Issue(ErrorType::FormatError, "invalid format of color name");
			return false;
		}
		color = Color(r, g, b, alpha);
		return true;
	} else {
		const Color* pColor = Lookup(str);
		if (!pColor) {
			Error::Issue(ErrorType::KeyError, "unknown color name: %s", str);
			return false;
		}
		color = Color(pColor->GetPacked(), alpha);
		return true;
	}
}

const Color* Color::Lookup(const char* name)
{
	return ColorStringMap::Instance.Lookup(name);
}

const Color* Color::Lookup(const Symbol* pSymbol)
{
	return ColorSymbolMap::Instance.Lookup(pSymbol);
}

String Color::ToString(const StringStyle& ss) const
{
	return String().Format("#%02x%02x%02x,%02x", GetR(), GetG(), GetB(), GetA());
}

//------------------------------------------------------------------------------
// ColorStringMap
//------------------------------------------------------------------------------
ColorStringMap ColorStringMap::Instance;

const Color* ColorStringMap::Lookup(const char* str) const
{
	auto iter = _map.find(str);
	return (iter == _map.end())? nullptr : &iter->second;
}

//------------------------------------------------------------------------------
// ColorSymbolMap
//------------------------------------------------------------------------------
ColorSymbolMap ColorSymbolMap::Instance;

const Color* ColorSymbolMap::Lookup(const Symbol* pSymbol) const
{
	auto iter = _map.find(pSymbol);
	return (iter == _map.end())? nullptr : &iter->second;
}

}
