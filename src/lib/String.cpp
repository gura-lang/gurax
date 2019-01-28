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

UInt32 String::_ctypeTbl[256];
int String::_convBinDigitTbl[256];
int String::_convOctDigitTbl[256];
int String::_convHexDigitTbl[256];
char String::_toUpperTbl[256];
char String::_toLowerTbl[256];
char String::_toEscapedTbl[256];

void String::Bootup()
{
	for (int ch = 0; ch < 256; ++ch) {
		UInt32 num = 0;
		if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
			num |= CType::Alpha;
		}
		if ('0' <= ch && ch <= '9') {
			num |= CType::Digit;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f')) {
			num |= CType::HexDigit;
		}
		if ('0' <= ch && ch <= '7') {
			num |= CType::OctDigit;
		}
		if ('0' <= ch && ch <= '1') {
			num |= CType::BinDigit;
		}
		if (ch == ' ' || ch == '\t') {
			num |= CType::White;
		}
		if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
			num |= CType::Space;
		}
		if ((0x81 <= ch && ch <= 0x9f) || (0xe0 <= ch && ch <= 0xef) || (0xfa <= ch && ch <= 0xfc)) {
			num |= CType::SJISFirst;
		}
		if ((0x40 <= ch && ch <= 0x7e) || (0x80 <= ch && ch <= 0xfc)) {
			num |= CType::SJISSecond;
		}
		if ((ch & 0xc0) == 0xc0) {
			num |= CType::UTF8First;
		}
		if ((ch & 0xc0) == 0x80) {
			num |= CType::UTF8Follower;
		}
		if (ch == '_' || ch == '$' || ch == '@') {
			num |= CType::SymbolExtra;
		}
		if ('a' <= ch && ch <= 'z') {
			num |= CType::Lower;
		}
		if ('A' <= ch && ch <= 'Z') {
			num |= CType::Upper;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') ||
			ch == ';' || ch ==  '/' || ch == '?' || ch == ':' || ch == '@' ||
			ch == '&' || ch ==  '=' || ch == '+' || ch == '$' || ch == ',' ||
			ch == '-' || ch == '_' || ch == '.' || ch == '!' || ch == '~' ||
			ch == '*' || ch == '\'' || ch == '(' || ch == ')') {
			num |= CType::URIC;
		}
		_ctypeTbl[ch] = num;
		_convBinDigitTbl[ch] = ('0' <= ch && ch <= '1')? ch - '0' : 0;
		_convOctDigitTbl[ch] = ('0' <= ch && ch <= '7')? ch - '0' : 0;
		_convHexDigitTbl[ch] =
			('0' <= ch && ch <= '9')? ch - '0' :
			('A' <= ch && ch <= 'F')? ch - 'A' + 10 : ('a' <= ch && ch <= 'f')? ch - 'a' + 10 : 0;
		_toUpperTbl[ch] = ('a' <= ch && ch <= 'z')? ch - 'a' + 'A' : ch;
		_toLowerTbl[ch] = ('A' <= ch && ch <= 'Z')? ch - 'A' + 'a' : ch;
		_toEscapedTbl[ch] =
			(ch == 'a')? '\a' : (ch == 'b')? '\b' : (ch == 'f')? '\f' : (ch == 'n')? '\n' :
			(ch == 'r')? '\r' : (ch == 't')? '\t' : (ch == 'v')? '\v' : (ch == '\\')? '\\' :
			(ch == '\'')? '\'' : (ch == '"')?  '"' : ch;
	}
}

String String::PickChar(size_t idx) const
{
	const_iterator p = begin();
	for ( ; p != end() && idx > 0; p = Forward(p), idx--) ;
	String::const_iterator pEnd = Forward(p);
	String rtn;
	for ( ; p != pEnd; ++p) rtn.push_back(*p);
	return rtn;
}

String::const_iterator String::Forward(const_iterator p, size_t nChars, size_t *pnCharsActual) const
{
	size_t nCharsActual = 0;
	for ( ; p != end() && nCharsActual < nChars; nCharsActual++) {
		char ch = *p;
		p++;
		if (IsUTF8First(ch)) {
			while (p != end() && IsUTF8Follower(*p)) p++;
		}
	}
	if (pnCharsActual) *pnCharsActual = nCharsActual;
	return p;
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

UInt64 String::NextUTF8(const_iterator* pp) const
{
	const_iterator& p = *pp;
	UInt64 codeUTF8 = 0x000000000000;
	if (p != end()) {
		char ch = *p;
		codeUTF8 = static_cast<UChar>(ch);
		p++;
		if (IsUTF8First(ch)) {
			while (p != end() && IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UChar>(*p);
				p++;
			}
		}
	}
	return codeUTF8;
}

UInt64 String::NextUTF8(const char** pp)
{
	const char*& p = *pp;
	UInt64 codeUTF8 = 0x000000000000;
	if (*p != '\0') {
		char ch = *p;
		codeUTF8 = static_cast<UChar>(ch);
		p++;
		if (IsUTF8First(ch)) {
			while (*p != '\0' && IsUTF8Follower(*p)) {
				codeUTF8 = (codeUTF8 << 8) | static_cast<UChar>(*p);
				p++;
			}
		}
	}
	return codeUTF8;
}

UInt32 String::NextUTF32(const_iterator* pp) const
{
	const_iterator& p = *pp;
	UInt32 codeUTF32 = 0x00000000;
	if (p == end()) {
		// nothing to do
	} else if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UChar>(*p);
		p++;
	} else {
		int cntChars = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x1f;
			cntChars = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x0f;
			cntChars = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x07;
			cntChars = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UChar>(*p) & 0x03;
			cntChars = 4;
		} else {
			codeUTF32 = static_cast<UChar>(*p) & 0x01;
			cntChars = 5;
		}
		p++;
		for (int i = 0; p != end() && i < cntChars &&
				 (static_cast<UChar>(*p) & 0xc0) == 0x80; ++i, ++p) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return codeUTF32;
}

UInt32 String::NextUTF32(const char** pp)
{
	const char*& p = *pp;
	UInt32 codeUTF32 = 0x00000000;
	if (*p == '\0') {
		// nothing to do
	} else if ((*p & 0x80) == 0x00) {
		codeUTF32 = static_cast<UChar>(*p);
		p++;
	} else {
		int cntChars = 0;
		if ((*p & 0xe0) == 0xc0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x1f;
			cntChars = 1;
		} else if ((*p & 0xf0) == 0xe0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x0f;
			cntChars = 2;
		} else if ((*p & 0xf8) == 0xf0) {
			codeUTF32 = static_cast<UChar>(*p) & 0x07;
			cntChars = 3;
		} else if ((*p & 0xfc) == 0xf8) {
			codeUTF32 = static_cast<UChar>(*p) & 0x03;
			cntChars = 4;
		} else {
			codeUTF32 = static_cast<UChar>(*p) & 0x01;
			cntChars = 5;
		}
		p++;
		for (int i = 0; *p != '\0' && i < cntChars &&
				 		(static_cast<UChar>(*p) & 0xc0) == 0x80; ++i, ++p) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return codeUTF32;
}

String& String::AppendN(const char* str, size_t n)
{
	while (n-- > 0) append(str);
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
	int i = 0;
	char buff[8];
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
	while (i > 0) push_back(buff[--i]);
	return *this;
}

String& String::PrintfV(const char* format, va_list ap)
{
	Formatter_String(*this).Format(format, ap);
	return *this;
}

String& String::Printf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return PrintfV(format, ap);
}

String& String::PrintFmt(const char* format, const ObjectList& objectList)
{
	Formatter_String(*this).Format(format, objectList);
	return *this;
}

String String::MakeQuoted(const char* str, bool surroundFlag)
{
	String strRtn;
	char chQuote = (::strchr(str, '\'') && !::strchr(str, '"'))? '"' : '\'';
	if (surroundFlag) strRtn += chQuote;
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
			::sprintf(tmp, "\\x%02x", static_cast<UChar>(ch));
			strRtn += tmp;
		} else {
			strRtn += ch;
		}
	}
	if (surroundFlag) strRtn += chQuote;
	return strRtn;
}

Double String::ToNumber(const char* str, bool* pSuccessFlag)
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

size_t String::Length(const char* str)
{
	size_t len = 0;
	for (const char* p = str ; *p != '\0'; len++) {
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

//------------------------------------------------------------------------------
// StringList
//------------------------------------------------------------------------------
StringList& StringList::Sort(SortOrder sortOrder)
{
	SortListByOrder<StringList, String::LessThan, String::GreaterThan>(*this, sortOrder);
	return *this;
}

//------------------------------------------------------------------------------
// StringReferable
//------------------------------------------------------------------------------

}
