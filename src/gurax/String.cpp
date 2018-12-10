//==============================================================================
// String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
UInt32 String::_ctypeTbl[256];
int String::_convBinDigitTbl[256];
int String::_convOctDigitTbl[256];
int String::_convHexDigitTbl[256];
char String::_toUpperTbl[256];
char String::_toLowerTbl[256];

void String::Bootup()
{
	for (auto ch = 0; ch < 256; ++ch) {
		UInt32 num = 0;
		if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
			num |= String::CType::Alpha;
		}
		if ('0' <= ch && ch <= '9') {
			num |= String::CType::Digit;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F') || ('a' <= ch && ch <= 'f')) {
			num |= String::CType::HexDigit;
		}
		if ('0' <= ch && ch <= '7') {
			num |= String::CType::OctDigit;
		}
		if ('0' <= ch && ch <= '1') {
			num |= String::CType::BinDigit;
		}
		if (ch == ' ' || ch == '\t') {
			num |= String::CType::White;
		}
		if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
			num |= String::CType::Space;
		}
		if ((0x81 <= ch && ch <= 0x9f) || (0xe0 <= ch && ch <= 0xef) || (0xfa <= ch && ch <= 0xfc)) {
			num |= String::CType::SJISFirst;
		}
		if ((0x40 <= ch && ch <= 0x7e) || (0x80 <= ch && ch <= 0xfc)) {
			num |= String::CType::SJISSecond;
		}
		if ((ch & 0xc0) == 0xc0) {
			num |= String::CType::UTF8First;
		}
		if ((ch & 0xc0) == 0x80) {
			num |= String::CType::UTF8Follower;
		}
		if (ch == '_' || ch == '$' || ch == '@') {
			num |= String::CType::SymbolExtra;
		}
		if ('a' <= ch && ch <= 'z') {
			num |= String::CType::Lower;
		}
		if ('A' <= ch && ch <= 'Z') {
			num |= String::CType::Upper;
		}
		if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') ||
			ch == ';' || ch ==  '/' || ch == '?' || ch == ':' || ch == '@' ||
			ch == '&' || ch ==  '=' || ch == '+' || ch == '$' || ch == ',' ||
			ch == '-' || ch == '_' || ch == '.' || ch == '!' || ch == '~' ||
			ch == '*' || ch == '\'' || ch == '(' || ch == ')') {
			num |= String::CType::URIC;
		}
		_ctypeTbl[ch] = num;
		_convBinDigitTbl[ch] = ('0' <= ch && ch <= '1')? ch - '0' : 0;
		_convOctDigitTbl[ch] = ('0' <= ch && ch <= '7')? ch - '0' : 0;
		_convHexDigitTbl[ch] =
			('0' <= ch && ch <= '9')? ch - '0' :
			('A' <= ch && ch <= 'F')? ch - 'A' + 10 : ('a' <= ch && ch <= 'f')? ch - 'a' + 10 : 0;
		_toUpperTbl[ch] = ('a' <= ch && ch <= 'z')? ch - 'a' + 'A' : ch;
		_toLowerTbl[ch] = ('A' <= ch && ch <= 'Z')? ch - 'A' + 'a' : ch;
	}
#if 0
	for (auto ch = 0; ch < 256; ++ch) {
		if (ch % 4 == 0) ::printf("\t");
		::printf("0x%08x,", _ctypeTbl[ch]);
		if ((ch + 1) % 4 == 0) {
			::printf("\n");
		} else {
			::printf(" ");
		}
	}
#endif
}

String String::PickChar(size_t idx) const
{
	const_iterator p = begin();
	for ( ; p != end() && idx > 0; p = Forward(p), idx--) ;
	String::const_iterator pEnd = Forward(p);
	String rtn;
	for ( ; p != pEnd; p++) rtn.push_back(*p);
	return rtn;
}

String::const_iterator String::Forward(const_iterator p) const
{
	if (p != end()) {
		char ch = *p;
		p++;
		if (IsUTF8First(ch)) {
			while (p != end() && IsUTF8Follower(*p)) p++;
		}
	}
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
	const char* p = *pp;
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
				 (static_cast<UChar>(*p) & 0xc0) == 0x80; i++, p++) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return codeUTF32;
}

UInt32 String::NextUTF32(const char** pp)
{
	const char* p = *pp;
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
				 		(static_cast<UChar>(*p) & 0xc0) == 0x80; i++, p++) {
			codeUTF32 = (codeUTF32 << 6) | (static_cast<UChar>(*p) & 0x3f);
		}
	}
	return codeUTF32;
}

void String::AppendUTF8(UInt64 codeUTF8)
{
	if (codeUTF8 == 0) {
		push_back('\0');
		return;
	}
	size_t i = 0;
	char buff[8];
	for ( ; codeUTF8 != 0 && i < 8; codeUTF8 >>= 8, i++) {
		buff[i] = static_cast<char>(codeUTF8 & 0xff);
	}
	while (i > 0) push_back(buff[--i]);
}

void String::AppendUTF32(UInt32 codeUTF32)
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
}

#if 0
const UInt32 String::_ctypeTbl[] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000060, 0x00000040, 0x00000000,
	0x00000000, 0x00000040, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000060, 0x00004000, 0x00000000, 0x00000000,
	0x00004800, 0x00000000, 0x00004000, 0x00004000,
	0x00004000, 0x00004000, 0x00004000, 0x00004000,
	0x00004000, 0x00004000, 0x00004000, 0x00004000,
	0x0000401e, 0x0000401e, 0x0000400e, 0x0000400e,
	0x0000400e, 0x0000400e, 0x0000400e, 0x0000400e,
	0x00004006, 0x00004006, 0x00004000, 0x00004000,
	0x00000000, 0x00004000, 0x00000000, 0x00004000,
	0x00004900, 0x00006105, 0x00006105, 0x00006105,
	0x00006105, 0x00006105, 0x00006105, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00006101,
	0x00006101, 0x00006101, 0x00006101, 0x00000100,
	0x00000100, 0x00000100, 0x00000100, 0x00004900,
	0x00000100, 0x00005105, 0x00005105, 0x00005105,
	0x00005105, 0x00005105, 0x00005105, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00005101,
	0x00005101, 0x00005101, 0x00005101, 0x00000100,
	0x00000100, 0x00000100, 0x00004100, 0x00000000,
	0x00000500, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000580, 0x00000580, 0x00000580, 0x00000580,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000500, 0x00000500, 0x00000500, 0x00000500,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000380, 0x00000380, 0x00000380, 0x00000380,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000300, 0x00000300,
	0x00000300, 0x00000300, 0x00000380, 0x00000380,
	0x00000380, 0x00000200, 0x00000200, 0x00000200,
};
#endif

}
