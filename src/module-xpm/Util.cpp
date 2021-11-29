//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xpm)

class XPMData {
public:
	bool Read();
private:
	virtual bool DoReadLine(String& str) = 0;
};

bool XPMData::Read()
{
	using ColorMap = std::map<String, Color>;
	String str;
	int width = 0, height = 0;
	int nColors = 0, nBytes = 0;
	do {
		enum class Stat {
			WidthPre, Width, HeightPre, Height,
			NColorsPre, NColors, NBytesPre, NBytes, Finish,
		} stat = Stat::WidthPre;
		if (!DoReadLine(str)) {
			Error::Issue(ErrorType::FormatError, "can't find XPM header");
			return false;
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
					return false;
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
					return false;
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
					return false;
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
					return false;
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
	for ( ; iColor < nColors && DoReadLine(str); iColor++) {
		enum class Stat { Category, CategoryPost, ValuePre, Value } stat = Stat::Category;
		const char *p = str.c_str();
		if (::strlen(p) < nBytes) {
			Error::Issue(ErrorType::FormatError, "invalid XPM header");
			return false;
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
					return false;
				} else {
					chCategory = ch;
					stat = Stat::CategoryPost;
				}
			} else if (stat == Stat::CategoryPost) {
				if (ch == ' ' || ch == '\t') {
					stat = Stat::ValuePre;
				} else {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return false;
				}
			} else if (stat == Stat::ValuePre) {
				if (ch == ' ' || ch == '\t') {
					// nothing to do
				} else if (ch == '\0') {
					Error::Issue(ErrorType::FormatError, "invalid XPM header");
					return false;
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
			//Color color = Color::CreateNamedColor(env, value.c_str(), 255);
			//if (sig.IsSignalled()) return false;
			//colorMap[symbol] = color;
		}
		//::printf("%s .. %s\n", symbol.c_str(), value.c_str());
	}
	if (iColor < nColors) {
		Error::Issue(ErrorType::FormatError, "invalid XPM header");
		return false;
	}
#if 0
	if (!pImage->AllocBuffer(sig, width, height, 0xff)) return false;
	std::unique_ptr<Image::Scanner>
					pScannerDst(pImage->CreateScanner(Image::SCAN_LeftTopHorz));
	bool alphaFlag = (pImage->GetFormat() == Image::FORMAT_RGBA);
	for (int y = 0; y < height && pValue != valList.end(); y++, pValue++) {
		const char *p = pValue->GetString();
		String symbol;
		int x = 0;
		for ( ; x < width && *p != '\0'; p++) {
			char ch = *p;
			symbol += ch;
			if (symbol.size() == nBytes) {
				if (symbol == symbolNull) {
					if (alphaFlag) {
						pScannerDst->StorePixel(0, 0, 0, 0);
					} else {
						pScannerDst->StorePixel(0, 0, 0);
					}
				} else {
					ColorMap::iterator iter = colorMap.find(symbol);
					if (iter == colorMap.end()) {
						Error::Issue(ErrorType::FormatError, "undefined color symbol");
						return false;
					}
					const Color &color = iter->second;
					pScannerDst->StorePixel(color.GetR(), color.GetG(), color.GetB(), 255);
				}
				pScannerDst->Next();
				x++;
				symbol.clear();
			}
		}
	}
#endif
	return true;
}


Gurax_EndModuleScope(xpm)
