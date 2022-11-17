//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_XPM_UTIL_H
#define GURAX_MODULE_XPM_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(xpm)

//------------------------------------------------------------------------------
// XPMData
//------------------------------------------------------------------------------
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
			if (!pValue->IsType(VTYPE_String)) {
				Error::Issue(ErrorType::TypeError, "value must be of String type");
				return false;
			}
			str = Value_String::GetString(*pValue);
			return true;
		}
	};
public:
	static bool Read(Image& image, LineReader& lineReader);
	static bool ReadIterator(Image& image, Iterator& iter) {
		LineReader_Iterator lineReader(iter);
		return Read(image, lineReader);
	}
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

Gurax_EndModuleScope(xpm)

#endif
