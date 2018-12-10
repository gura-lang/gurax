//==============================================================================
// String.cpp
//==============================================================================
#include "stdafx.h"
#include <random>

namespace Gurax {

template<int N> struct Table
{
	constexpr Table() : values(), values2() {
		for (auto i = 0; i < N; ++i) {
			values[i][0] = i;
			values[i][1] = i * i * i;
		}
		for (int i = 0; i < N; ++i) {
			values2[i] = i;
		}
    }
    int values[N][2];
	int values2[N];
};

constexpr auto table = Table<256>();

void func()
{
	std::mt19937 rng;

}

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
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

}
