//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xpm)

//------------------------------------------------------------------------------
// XPMData
//------------------------------------------------------------------------------
Image* XPMData::Read(const Image::Format& format, LineReader& lineReader)
{
	String str;
	int width = 0, height = 0;
	int nColors = 0, nBytes = 0;
	do {
		enum class Stat {
			WidthPre, Width, HeightPre, Height,
			NColorsPre, NColors, NBytesPre, NBytes, Finish,
		} stat = Stat::WidthPre;
		if (!lineReader.DoRead(str)) {
			Error::Issue(ErrorType::FormatError, "can't find XPM header");
			return nullptr;
		}
		const char *p = str.c_str();
		for (;;) {
			char ch = *p++;
			Gurax_BeginPushbackRegion();
			if (stat == Stat::WidthPre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else {
					stat = Stat::Width;
					Gurax_Pushback();
				}
			} else if (stat == Stat::Width) {
				if ('0' <= ch && ch <= '9') {
					width = width * 10 + (ch - '0');
				} else if (ch == ' ' || ch == '\t') {
					stat = Stat::HeightPre;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				}
			} else if (stat == Stat::HeightPre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else {
					stat = Stat::Height;
					Gurax_Pushback();
				}
			} else if (stat == Stat::Height) {
				if ('0' <= ch && ch <= '9') {
					height = height * 10 + (ch - '0');
				} else if (ch == ' ' || ch == '\t') {
					stat = Stat::NColorsPre;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				}
			} else if (stat == Stat::NColorsPre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else {
					stat = Stat::NColors;
					Gurax_Pushback();
				}
			} else if (stat == Stat::NColors) {
				if ('0' <= ch && ch <= '9') {
					nColors = nColors * 10 + (ch - '0');
				} else if (ch == ' ' || ch == '\t') {
					stat = Stat::NBytesPre;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				}
			} else if (stat == Stat::NBytesPre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else {
					stat = Stat::NBytes;
					Gurax_Pushback();
				}
			} else if (stat == Stat::NBytes) {
				if ('0' <= ch && ch <= '9') {
					nBytes = nBytes * 10 + (ch - '0');
				} else if (ch == ' ' || ch == '\t' || ch == '\0') {
					stat = Stat::Finish;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				}
			}
			Gurax_EndPushbackRegion();
			if (ch == '\0') break;
		}
		//::printf("%d %d %d %d\n", width, height, nColors, nBytes);
	} while (0);
	ColorMap colorMap;
	String symbolNull;
	int iColor = 0;
	for ( ; iColor < nColors && lineReader.DoRead(str); iColor++) {
		enum class Stat { Category, CategoryPost, ValuePre, Value } stat = Stat::Category;
		const char* p = str.c_str();
		if (::strlen(p) < nBytes) {
			Error::Issue(ErrorType::FormatError, "invalid XPM header");
			return nullptr;
		}
		char chCategory = '\0';
		String symbol(p, p + nBytes);
		String value;
		p += nBytes;
		for (;;) {
			char ch = *p++;
			if (stat == Stat::Category) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else if (ch == '\0') {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				} else {
					chCategory = ch;
					stat = Stat::CategoryPost;
				}
			} else if (stat == Stat::CategoryPost) {
				if (ch == ' ' || ch == '\t') {
					stat = Stat::ValuePre;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				}
			} else if (stat == Stat::ValuePre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else if (ch == '\0') {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return nullptr;
				} else {
					value.clear();
					value += ch;
					stat = Stat::Value;
				}
			} else if (stat == Stat::Value) {
				if (ch == ' ' || ch == '\t' || ch == '\0') {
					if (chCategory == 'c') break;
					stat = Stat::Category;
				} else {
					value += ch;
				}
			}
			if (ch == '\0') break;
		}
		if (::strcasecmp(value.c_str(), "None") == 0) {
			symbolNull = symbol;
		} else {
			Color color;
			if (!Color::FromString(color, value.c_str(), 255)) return nullptr;
			colorMap[symbol] = color;
		}
		//::printf("%s .. %s\n", symbol.c_str(), value.c_str());
	}
	if (Error::IsIssued()) return nullptr;
	if (iColor < nColors) {
		Error::Issue(ErrorType::FormatError, "invalid XPM header");
		return nullptr;
	}
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(width, height)) return nullptr;
	if (format.IsIdentical(Image::Format::RGBA)) {
		if (!ReadData<Image::PixelRGBA>(*pImage, lineReader, colorMap, symbolNull, width, height, nColors, nBytes)) return nullptr;
	} else {
		if (!ReadData<Image::PixelRGB>(*pImage, lineReader, colorMap, symbolNull, width, height, nColors, nBytes)) return nullptr;
	}
	return pImage.release();
}

Gurax_EndModuleScope(xpm)
