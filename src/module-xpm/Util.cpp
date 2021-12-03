//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xpm)

class XPMData {
public:
	using ColorMap = std::map<String, Color>;
	class LineReader {
	public:
		virtual bool DoRead(String& str) = 0;
	};
	class LineReader_Iterator : public LineReader {
	private:
		Iterator& _iter;
	public:
		LineReader_Iterator(Iterator& iter) : _iter(iter) {}
		virtual bool DoRead(String& str) {
			RefPtr<Value> pValue(_iter.NextValue());
			if (!pValue) return false;
			str = Value_String::GetString(*pValue);
			return true;
		}
	};
public:
	Image* Read(const Image::Format& format, LineReader& lineReader);
private:
	template<typename T_Pixel>
	static bool ReadData(Image& image, LineReader& lineReader, const ColorMap& colorMap,
					const String& symbolNull, int width, int height, int nColors, int nBytes);
};

template<typename T_Pixel>
bool XPMData::ReadData(Image& image, LineReader& lineReader, const ColorMap& colorMap,
					const String& symbolNull, int width, int height, int nColors, int nBytes)
{
	String str;
	UInt8* pDst = image.GetPointerC();
	for (int y = 0; y < height; y++) {
		if (!lineReader.DoRead(str)) {
			Error::Issue(ErrorType::FormatError, "invalid XPM data");
			return false;
		}
		String symbol;
		int x = 0;
		for (String::const_iterator p = str.begin() ; x < width && p != str.end(); p++) {
			char ch = *p;
			symbol += ch;
			if (symbol.size() == nBytes) {
				if (symbol == symbolNull) {
					T_Pixel::SetRGBA(pDst, 0, 0, 0, 0);
				} else {
					auto iter = colorMap.find(symbol);
					if (iter == colorMap.end()) {
						Error::Issue(ErrorType::FormatError, "undefined color symbol");
						return false;
					}
					const Color& color = iter->second;
					T_Pixel::SetRGBA(pDst, color.GetR(), color.GetG(), color.GetB(), 255);
				}
				pDst += T_Pixel::bytesPerPixel;
				x++;
				symbol.clear();
			}
		}
	}
	return true;
}

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
#if 0
	UInt8* pDst = pImage->GetPointerC();
	String str;
	for (int y = 0; y < height; y++) {
		if (!lineReader.DoRead(str)) return nullptr;
		String symbol;
		int x = 0;
		for (String::const_iterator p = str.begin() ; x < width && p != str.end(); p++) {
			char ch = *p;
			symbol += ch;
			if (symbol.size() == nBytes) {
				if (symbol == symbolNull) {
					if (alphaFlag) {
						Image::PixelRGBA::SetPacked(pDst, 0x00000000);
					} else {
						Image::PixelRGB::SetRGB(pDst, 0, 0, 0);
					}
				} else {
					ColorMap::iterator iter = colorMap.find(symbol);
					if (iter == colorMap.end()) {
						Error::Issue(ErrorType::FormatError, "undefined color symbol");
						return nullptr;
					}
					const Color& color = iter->second;
					//Image::PixelRGBpScannerDst->StorePixel(color.GetR(), color.GetG(), color.GetB(), 255);
				}
				//pScannerDst->Next();
				x++;
				symbol.clear();
			}
		}
	}
#endif
	return pImage.release();
}

Gurax_EndModuleScope(xpm)
