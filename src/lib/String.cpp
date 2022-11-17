//==============================================================================
// String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Formatter_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Formatter_String : public Formatter {
private:
	String& _str;
public:
	// Constructor
	Formatter_String(String& str) : _str(str) {}
public:
	// Virtual functions of Formatter
	virtual bool PutChar(char ch) override {
		_str += ch;
		return true;
	}
};

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
const String String::Empty("");

String::CTypes String::_ctypesTbl[256];
int String::_convBinDigitTbl[256];
int String::_convOctDigitTbl[256];
int String::_convHexDigitTbl[256];
char String::_toUpperTbl[256];
char String::_toLowerTbl[256];
char String::_toEscapedTbl[256];

void String::Bootup()
{
	StringReferable::Empty.reset(new StringReferable());
	for (int ch = 0; ch < 256; ++ch) {
		CTypes ctypes = 0;
		if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
			ctypes |= CType::Alpha;
		}
		if ('0' <= ch && ch <= '9') {
			ctypes |= CType::Digit;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f')) {
			ctypes |= CType::HexDigit;
		}
		if ('0' <= ch && ch <= '7') {
			ctypes |= CType::OctDigit;
		}
		if ('0' <= ch && ch <= '1') {
			ctypes |= CType::BinDigit;
		}
		if (ch == ' ' || ch == '\t') {
			ctypes |= CType::White;
		}
		if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
			ctypes |= CType::Space;
		}
		if ((0x81 <= ch && ch <= 0x9f) || (0xe0 <= ch && ch <= 0xef) || (0xfa <= ch && ch <= 0xfc)) {
			ctypes |= CType::SJISFirst;
		}
		if ((0x40 <= ch && ch <= 0x7e) || (0x80 <= ch && ch <= 0xfc)) {
			ctypes |= CType::SJISSecond;
		}
		if ((ch & 0xc0) == 0xc0) {
			ctypes |= CType::UTF8First;
		}
		if ((ch & 0xc0) == 0x80) {
			ctypes |= CType::UTF8Follower;
		}
		if (ch == '_' || ch == '$' || ch == '@') {
			ctypes |= CType::SymbolExtra;
		}
		if ('a' <= ch && ch <= 'z') {
			ctypes |= CType::Lower;
		}
		if ('A' <= ch && ch <= 'Z') {
			ctypes |= CType::Upper;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') ||
			ch == ';' || ch ==  '/' || ch == '?' || ch == ':' || ch == '@' ||
			ch == '&' || ch ==  '=' || ch == '+' || ch == '$' || ch == ',' ||
			ch == '-' || ch == '_' || ch == '.' || ch == '!' || ch == '~' ||
			ch == '*' || ch == '\'' || ch == '(' || ch == ')') {
			ctypes |= CType::URIC;
		}
		if (0x20 <= ch && ch < 0x7f) {
			ctypes |= CType::Print;
		}
		_ctypesTbl[ch] = ctypes;
		_convBinDigitTbl[ch] = ('0' <= ch && ch <= '1')? ch - '0' : -1;
		_convOctDigitTbl[ch] = ('0' <= ch && ch <= '7')? ch - '0' : -1;
		_convHexDigitTbl[ch] =
			('0' <= ch && ch <= '9')? ch - '0' :
			('A' <= ch && ch <= 'F')? ch - 'A' + 10 : ('a' <= ch && ch <= 'f')? ch - 'a' + 10 : -1;
		_toUpperTbl[ch] = ('a' <= ch && ch <= 'z')? ch - 'a' + 'A' : ch;
		_toLowerTbl[ch] = ('A' <= ch && ch <= 'Z')? ch - 'A' + 'a' : ch;
		_toEscapedTbl[ch] =
			(ch == 'a')? '\a' : (ch == 'b')? '\b' : (ch == 'f')? '\f' : (ch == 'n')? '\n' :
			(ch == 'r')? '\r' : (ch == 't')? '\t' : (ch == 'v')? '\v' : (ch == '\\')? '\\' :
			(ch == '\'')? '\'' : (ch == '"')?  '"' : ch;
	}
}

bool String::CheckPosition(size_t len, Int pos, Int posRaw)
{
	if (0 <= pos && static_cast<size_t>(pos) < len) return true;
	IssueError_IndexOutOfRange(len, posRaw);
	return false;
}

bool String::FixPosition(size_t len, Int* pPos)
{
	Int posRaw = *pPos;
	if (*pPos < 0) *pPos += len;
	return CheckPosition(len, *pPos, posRaw);
}

String String::PickChar(size_t idx) const
{
	const_iterator p = begin();
	for ( ; p != end() && idx > 0; p = Forward(p), idx--) ;
	String::const_iterator pEnd = Forward(p);
	String str;
	for ( ; p != pEnd; ++p) str.push_back(*p);
	return str;
}

const char* String::Forward(const char* p, size_t nChars, size_t *pnCharsActual)
{
	size_t nCharsActual = 0;
	for ( ; *p != '\0' && nCharsActual < nChars; nCharsActual++) {
		char ch = *p;
		p++;
		if (IsUTF8First(ch)) {
			while (*p != '\0' && IsUTF8Follower(*p)) p++;
		}
	}
	if (pnCharsActual) *pnCharsActual = nCharsActual;
	return p;
}

const char* String::Backward(const char* p, const char* pHead, size_t nChars, size_t *pnCharsActual)
{
	size_t nCharsActual = 0;
	for ( ; p != pHead && nCharsActual < nChars; nCharsActual++) {
		p--;
		while (p != pHead && IsUTF8Follower(*p)) p--;
	}
	if (pnCharsActual) *pnCharsActual = nCharsActual;
	return p;
}

String::const_iterator String::Forward(const_iterator p, const_iterator pEnd, size_t nChars, size_t *pnCharsActual)
{
	size_t nCharsActual = 0;
	for ( ; p != pEnd && nCharsActual < nChars; nCharsActual++) {
		char ch = *p;
		p++;
		if (IsUTF8First(ch)) {
			while (p != pEnd && IsUTF8Follower(*p)) p++;
		}
	}
	if (pnCharsActual) *pnCharsActual = nCharsActual;
	return p;
}

UInt64 String::NextUTF8(const char** pp)
{
	const char*& p = *pp;
	UInt64 codeUTF8 = 0x000000000000;
	if (*p != '\0') {
		char ch = *p;
		codeUTF8 = static_cast<UInt8>(ch);
		p++;
		if (IsUTF8First(ch)) {
			while (*p != '\0' && IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UInt8>(*p);
				p++;
			}
		}
	}
	return codeUTF8;
}

UInt64 String::NextUTF8(const_iterator* pp) const
{
	const_iterator& p = *pp;
	UInt64 codeUTF8 = 0x000000000000;
	if (p != end()) {
		char ch = *p;
		codeUTF8 = static_cast<UInt8>(ch);
		p++;
		if (IsUTF8First(ch)) {
			while (p != end() && IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UInt8>(*p);
				p++;
			}
		}
	}
	return codeUTF8;
}

UInt32 String::NextUTF32(const char** pp)
{
	const char*& p = *pp;
	UInt32 codeUTF32 = 0x00000000;
	if (*p == '\0') return codeUTF32;
	if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UInt8>(*p);
		p++;
	} else {
		int nFollowers = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x1f;
			nFollowers = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x0f;
			nFollowers = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x07;
			nFollowers = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x03;
			nFollowers = 4;
		} else {
			codeUTF32 = static_cast<UInt8>(*p) & 0x01;
			nFollowers = 5;
		}
		p++;
		for (int i = 0; *p != '\0' && i < nFollowers; ++i, ++p) {
			if ((static_cast<UInt8>(*p) & 0xc0) == 0x80) {
				codeUTF32 = (codeUTF32 << 6) | (static_cast<UInt8>(*p) & 0x3f);
			} else {
				codeUTF32 <<= 6;
			}
		}
	}
	return codeUTF32;
}

UInt32 String::NextUTF32(const_iterator* pp) const
{
	const_iterator& p = *pp;
	UInt32 codeUTF32 = 0x00000000;
	if (p == end()) return codeUTF32;
	if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UInt8>(*p);
		p++;
	} else {
		int nFollowers = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x1f;
			nFollowers = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x0f;
			nFollowers = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x07;
			nFollowers = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UInt8>(*p) & 0x03;
			nFollowers = 4;
		} else {
			codeUTF32 = static_cast<UInt8>(*p) & 0x01;
			nFollowers = 5;
		}
		p++;
		for (int i = 0; p != end() && i < nFollowers; ++i, ++p) {
			if ((static_cast<UInt8>(*p) & 0xc0) == 0x80) {
				codeUTF32 = (codeUTF32 << 6) | (static_cast<UInt8>(*p) & 0x3f);
			} else {
				codeUTF32 <<= 6;
			}
		}
	}
	return codeUTF32;
}

String& String::AppendNTimes(const char* str, size_t n)
{
	while (n-- > 0) append(str);
	return *this;
}

String& String::AppendNChars(const char* str, size_t len)
{
	for ( ; *str != '\0' && len > 0; len--) {
		int ch = static_cast<UInt8>(*str);
		push_back(*str);
		str++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*str)) {
				push_back(*str);
				str++;
			}
		}
	}
	return *this;
}

String& String::AppendUTF8(UInt64 codeUTF8)
{
	if (codeUTF8 == 0) {
		push_back('\0');
		return *this;
	}
	size_t i = 0;
	char buff[8];
	for ( ; codeUTF8 != 0 && i < 8; codeUTF8 >>= 8, ++i) {
		buff[i] = static_cast<char>(codeUTF8 & 0xff);
	}
	while (i > 0) push_back(buff[--i]);
	return *this;
}

String& String::AppendUTF32(UInt32 codeUTF32)
{
	char buff[8];
	size_t i = 0;
	UTF32ToUTF8_Unsorted(codeUTF32, buff, &i);
	while (i > 0) push_back(buff[--i]);
	return *this;
}

void String::UTF32ToUTF8(UInt32 codeUTF32, char buff[], size_t *pCnt)
{
	char buffRaw[8];
	UTF32ToUTF8_Unsorted(codeUTF32, buffRaw, pCnt);
	size_t i = *pCnt, j = 0;
	for ( ; i > 0; j++) buff[j] = buffRaw[--i];
}

void String::UTF32ToUTF8_Unsorted(UInt32 codeUTF32, char buff[], size_t *pCnt)
{
	size_t i = 0;
	if ((codeUTF32 & ~0x7f) == 0) {
		buff[i++] = static_cast<char>(codeUTF32);
	} else {
		buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
		codeUTF32 >>= 6;
		if ((codeUTF32 & ~0x1f) == 0) {
			buff[i++] = 0xc0 | static_cast<char>(codeUTF32);
		} else {
			buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
			codeUTF32 >>= 6;
			if ((codeUTF32 & ~0x0f) == 0) {
				buff[i++] = 0xe0 | static_cast<char>(codeUTF32);
			} else {
				buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
				codeUTF32 >>= 6;
				if ((codeUTF32 & ~0x07) == 0) {
					buff[i++] = 0xf0 | static_cast<char>(codeUTF32);
				} else {
					buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
					codeUTF32 >>= 6;
					if ((codeUTF32 & ~0x03) == 0) {
						buff[i++] = 0xf8 | static_cast<char>(codeUTF32);
					} else {
						buff[i++] = 0x80 | static_cast<char>(codeUTF32 & 0x3f);
						codeUTF32 >>= 6;
						buff[i++] = 0xfc | static_cast<char>(codeUTF32);
					}
				}
			}
		}
	}
	*pCnt = i;
}

String& String::FormatV(const char* format, va_list ap)
{
	Formatter_String(*this).FormatV(format, ap);
	return *this;
}

String& String::Format(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return FormatV(format, ap);
}

String& String::FormatValue(const char* format, const Value& value)
{
	Formatter_String(*this).Format(format, value);
	return *this;
}

String& String::FormatValueList(const char* format, const ValueList& valueList)
{
	Formatter_String(*this).Format(format, valueList);
	return *this;
}

char String::DetermineQuote(const char* str)
{
	char chQuote = '\'';
	for (const char* p = str; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '"') return '\'';
		if (ch == '\'') chQuote = '\"';
	}
	return chQuote;
}

String String::Enquote(const char* str, char chQuote)
{
	String strRtn;
	strRtn += chQuote;
	for (const char* p = str; *p != '\0'; p++) {
		char ch = *p;
		if (ch == '\a') {
			strRtn += "\\a";
		} else if (ch == '\b') {
			strRtn += "\\b";
		} else if (ch == '\f') {
			strRtn += "\\f";
		} else if (ch == '\n') {
			strRtn += "\\n";
		} else if (ch == '\r') {
			strRtn += "\\r";
		} else if (ch == '\t') {
			strRtn += "\\t";
		} else if (ch == '\v') {
			strRtn += "\\v";
		} else if (ch == chQuote) {
			strRtn += '\\';
			strRtn += chQuote;
		} else if (ch == '\\') {
			strRtn += "\\\\";
		} else if (IsUTF8First(ch) || IsUTF8Follower(ch)) {
			strRtn += ch;
		} else if (ch < 0x20 || ch >= 0x7f) {
			char tmp[16];
			::sprintf(tmp, "\\x%02x", static_cast<UInt8>(ch));
			strRtn += tmp;
		} else {
			strRtn += ch;
		}
	}
	strRtn += chQuote;
	return strRtn;
}

String String::EncodeURI(const char* str)
{
	String strRtn;
	for (const char* p = str; *p; p++) {
		char ch = *p;
		if (String::IsURIC(ch)) {
			strRtn += ch;
		} else {
			char buff[8];
			::sprintf(buff, "%%%02X", static_cast<UInt8>(ch));
			strRtn += buff;
		}
	}
	return strRtn;
}

String String::DecodeURI(const char* str)
{
	String strRtn;
	enum class Stat { Normal, Percent, } stat = Stat::Normal;
	int nNibbles = 0;
	UInt8 data = 0x00;
	for (const char *p = str; *p; p++) {
		char ch = *p;
		switch (stat) {
		case Stat::Normal: {
			if (ch == '%') {
				nNibbles = 0;
				data = 0x00;
				stat = Stat::Percent;
			} else {
				strRtn += ch;
			}
			break;
		}
		case Stat::Percent: {
			if ('0' <= ch && ch <= '9') {
				data = (data << 4) + (ch - '0');
			} else if ('A' <= ch && ch <= 'F') {
				data = (data << 4) + (ch - 'A' + 10);
			} else if ('a' <= ch && ch <= 'f') {
				data = (data << 4) + (ch - 'a' + 10);
			}
			nNibbles++;
			if (nNibbles == 2) {
				strRtn += static_cast<char>(data);
				stat = Stat::Normal;
			}
			break;
		}
		default:
			break;
		}
	}
	return strRtn;
}

String String::EscapeHTML(const char* str, bool quoteFlag)
{
	String strRtn;
	for (const char *p = str; *p; p++) {
		char ch = *p;
		if (ch == '&') {
			strRtn += "&amp;";
		} else if (ch == '>') {
			strRtn += "&gt;";
		} else if (ch == '<') {
			strRtn += "&lt;";
		} else if (quoteFlag && ch == '"') {
			strRtn += "&quot;";
		} else {
			strRtn += ch;
		}
	}
	return strRtn;
}

String String::UnescapeHTML(const char* str)
{
	String strRtn;
	enum class Stat { Normal, Escape, } stat = Stat::Normal;
	String field;
	for (const char *p = str; *p; p++) {
		char ch = *p;
		switch (stat) {
		case Stat::Normal: {
			if (ch == '&') {
				field.clear();
				stat = Stat::Escape;
			} else {
				strRtn += ch;
			}
			break;
		}
		case Stat::Escape: {
			if (ch == ';') {
				if (field == "amp") {
					strRtn += '&';
				} else if (field == "gt") {
					strRtn += '>';
				} else if (field == "lt") {
					strRtn += '<';
				} else if (field == "quot") {
					strRtn += '"';
				}
				stat = Stat::Normal;
			} else {
				field += ch;
			}
			break;
		}
		default:
			break;
		}
	}
	return strRtn;
}

Double String::ToDouble(const char* str, bool* pSuccessFlag)
{
	Double num;
	char* next = nullptr;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X' || IsOctDigit(str[1]))) {
		num = static_cast<Double>(::strtoull(str, &next, 0));
	} else if (str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
		num = static_cast<Double>(::strtoull(str + 2, &next, 2));
	} else {
		num = ::strtod(str, &next);
	}
	if (pSuccessFlag) *pSuccessFlag = (*next == '\0');
	return num;
}

Int64 String::ToInt64(const char* str, bool* pSuccessFlag)
{
	char* next = nullptr;
	Int64 num = ::strtoull(str, &next, 0);
	if (pSuccessFlag) *pSuccessFlag = (*next == '\0');
	return num;
}

size_t String::CalcHash(const char* str)
{
	size_t hash = 0;
	for ( ; *str != '\0'; ++str) hash = hash * 137 + *str;
	return hash;
}

size_t String::CalcHash(const char* str, size_t len)
{
	size_t hash = 0;
	for ( ; len > 0; ++str, --len) hash = hash * 137 + *str;
	return hash;
}

bool String::EndsWith(const char* str, char ch)
{
	size_t len = ::strlen(str);
	return (len > 0) && *(str + len - 1) == ch;
}

bool String::EndsWith(char ch) const
{
	size_t len = size();
	return (len > 0) && *(c_str() + len - 1) == ch;
}

bool String::EndsWithPathSep(const char* str)
{
	size_t len = ::strlen(str);
	return (len > 0) && PathName::IsSep(*(str + len - 1));
}

bool String::EndsWithPathSep() const
{
	size_t len = size();
	return (len > 0) && PathName::IsSep(*(c_str() + len - 1));
}

size_t String::Length(const char* str)
{
	size_t len = 0;
	for (const char* p = str; *p != '\0'; len++) {
		char ch = *p++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*p)) p++;
		}
	}
	return len;
}

size_t String::CalcPos(const char* str, const char* sub)
{
	size_t len = 0;
	for (const char* p = str; *p != '\0' && p != sub; len++) {
		char ch = *p++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*p)) p++;
		}
	}
	return len;
}

size_t String::CalcPos(const_iterator pStr, const_iterator pStrSub)
{
	size_t len = 0;
	for (const_iterator p = pStr; p != pStrSub; len++) {
		char ch = *p++;
		if (IsUTF8First(ch)) {
			while (IsUTF8Follower(*p)) p++;
		}
	}
	return len;
}

size_t String::Width(const char* str)
{
	size_t width = 0;
	for (const char* p = str; *p != '\0'; ) {
		UInt32 codeUTF32 = NextUTF32(&p);
		Codec::WidthProp widthProp = Codec::GetWidthProp(codeUTF32);
		if (widthProp == Codec::WidthProp::A ||
			widthProp == Codec::WidthProp::W ||
			widthProp == Codec::WidthProp::F) {
			width += 2;
		} else {
			width += 1;
		}
	}
	return width;
}

String String::Center(const char* str, size_t width, const char* padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	char chPadding = *padding? *padding : ' ';
	String strRtn;
	size_t widthRight = (width - widthBody) / 2;
	size_t widthLeft = width - widthBody - widthRight;
	while (widthLeft-- > 0) strRtn += chPadding;
	strRtn += str;
	while (widthRight-- > 0) strRtn += chPadding;
	return strRtn;
}

String String::LJust(const char* str, size_t width, const char* padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	char chPadding = *padding? *padding : ' ';
	String strRtn;
	size_t widthRight = width - widthBody;
	strRtn += str;
	while (widthRight-- > 0) strRtn += chPadding;
	return strRtn;
}

String String::RJust(const char* str, size_t width, const char* padding)
{
	size_t widthBody = Width(str);
	if (width <= widthBody) return String(str);
	char chPadding = *padding? *padding : ' ';
	String strRtn;
	size_t widthLeft = width - widthBody;
	while (widthLeft-- > 0) strRtn += chPadding;
	strRtn += str;
	return strRtn;
}

String String::Left(const char* str, size_t len)
{
	String strRtn;
	strRtn.AppendNChars(str, len);
	return strRtn;
}

String String::Right(const char* str, size_t len)
{
	size_t lenSrc = Length(str);
	if (lenSrc > len) {
		str = Forward(str, lenSrc - len);
	}
	return String(str);
}

String String::Mid(const char* str, int start, size_t len)
{
	int lenSrc = static_cast<int>(Length(str));
	if (start < 0) {
		start += lenSrc;
		if (start < 0) start = 0;
	}
	if (start >= lenSrc || len == 0) {
		return String("");
	} else if (static_cast<int>(len) < lenSrc - start) {
		str = Forward(str, start);
		String strRtn;
		strRtn.AppendNChars(str, len);
		return strRtn;
	} else {
		str = Forward(str, start);
		return String(str);
	}
}

String String::Upper(const char* str)
{
	String strRtn;
	for (const char* p = str; *p != '\0';  p++) strRtn += ToUpper(*p);
	return strRtn;
}

String String::Lower(const char* str)
{
	String strRtn;
	for (const char* p = str; *p != '\0';  p++) strRtn += ToLower(*p);
	return strRtn;
}

String String::Capitalize(const char* str)
{
	String strRtn;
	const char* p = str;
	if (*p != '\0') {
		strRtn += ToUpper(*p);
		strRtn += p + 1;
	}
	return strRtn;
}

String String::Strip(const char* str, bool stripLeftFlag, bool stripRightFlag)
{
	size_t len = ::strlen(str);
	if (len == 0) return String::Empty;
	const char* p1 = str;
	const char* p2 = str + len - 1;
	if (stripLeftFlag) {
		for ( ; IsSpace(*p1); p1++) ;
	}
	if (stripRightFlag) {
		for ( ; p2 > p1 && IsSpace(*p2); p2--) ;
		if (IsSpace(*p2)) return String("");
	}
	return String(p1, p2 - p1 + 1);
}

String String::Chop(const char* str, bool eolOnlyFlag)
{
	size_t len = ::strlen(str);
	if (len == 0) return String::Empty;
	const char* p = str + len;
	if (*(p - 1) == '\n') {
		p--;
		if (p > str && *(p - 1) == '\r') p--;
	} else if (eolOnlyFlag) {
		// nothing to do
	} else if (IsUTF8Follower(*(p - 1))) {
		p--;
		if (p > str) p--;
		while (p > str && !IsUTF8First(*p)) p--;
	} else {
		p--;
	}
	return String(str, p);
}

void String::Split(StringList& strs, const char* str, char sep)
{
	const char* p = str;
	while (*p) {
		const char* pFind = ::strchr(p, sep);
		if (pFind) {
			strs.push_back(String(p, pFind));
			p = pFind + 1;
			if (!*p) {
				strs.push_back(p);
				break;
			}
		} else {
			strs.push_back(p);
			break;
		}
	}
}

String String::Repeat(const char* str, size_t n)
{
	String strRtn;
	strRtn.reserve(::strlen(str) * n);
	for (size_t i = 0; i < n; i++) strRtn += str;
	return strRtn;
}

bool String::IsCTypes(const char* str, CTypes ctypes)
{
	if (!*str) return false;
	for (const char* p = str; *p; p++) {
		if ((GetCTypes(*p) & ctypes) == 0) return false;
	}
	return true;
}

void String::IssueError_InvalidFormatOfNumber()
{
	Error::Issue(ErrorType::FormatError, "invalid format of number");
}

void String::IssueError_IndexOutOfRange(size_t len, Int pos)
{
	Error::Issue(ErrorType::IndexError,
				 "specified position %d exceeds the string's size of %zu", pos, len);
}

//------------------------------------------------------------------------------
// StringList
//------------------------------------------------------------------------------
const StringList StringList::Empty;

StringList& StringList::Sort(SortOrder sortOrder)
{
	SortByOrder<String::LessThan, String::GreaterThan>(sortOrder);
	return *this;
}

//------------------------------------------------------------------------------
// StringSet
//------------------------------------------------------------------------------
const StringSet StringSet::Empty;

//------------------------------------------------------------------------------
// StringReferable
//------------------------------------------------------------------------------
RefPtr<StringReferable> StringReferable::Empty;

}
