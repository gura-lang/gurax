//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
class String : public std::string {
private:
	enum {
		CTYPE_Alpha				= (1 << 0),
		CTYPE_Digit				= (1 << 1),
		CTYPE_HexDigit			= (1 << 2),
		CTYPE_OctDigit			= (1 << 3),
		CTYPE_BinDigit			= (1 << 4),
		CTYPE_White				= (1 << 5),
		CTYPE_Space				= (1 << 6),
		CTYPE_SJISFirst			= (1 << 7),
		CTYPE_SJISSecond		= (1 << 8),
		CTYPE_UTF8First			= (1 << 9),
		CTYPE_UTF8Follower		= (1 << 10),
		CTYPE_SymbolExtra		= (1 << 11),
		CTYPE_Lower				= (1 << 12),
		CTYPE_Upper				= (1 << 13),
		CTYPE_URIC				= (1 << 14),
		CTYPE_SymbolFirst		= (CTYPE_Alpha | CTYPE_SymbolExtra | CTYPE_UTF8First),
		CTYPE_SymbolFollower	= (CTYPE_SymbolFirst | CTYPE_Digit | CTYPE_UTF8Follower),
	};
	static const UInt32 _ctypeTbl[];
public:
	using std::string::string;	// inherits constructors
public:
	// Character operation
	static UInt32 GetCType(char ch)			{ return _ctypeTbl[static_cast<UChar>(ch)]; }
	static bool IsAlpha(char ch)			{ return (GetCType(ch) & CTYPE_Alpha) != 0; }
	static bool IsDigit(char ch)			{ return (GetCType(ch) & CTYPE_Digit) != 0; }
	static bool IsHexDigit(char ch)			{ return (GetCType(ch) & CTYPE_HexDigit) != 0; }
	static bool IsOctDigit(char ch)			{ return (GetCType(ch) & CTYPE_OctDigit) != 0; }
	static bool IsBinDigit(char ch)			{ return (GetCType(ch) & CTYPE_BinDigit) != 0; }
	static bool IsWhite(char ch)			{ return (GetCType(ch) & CTYPE_White) != 0; }
	static bool IsSpace(char ch)			{ return (GetCType(ch) & CTYPE_Space) != 0; }
	static bool IsSJISFirst(char ch)		{ return (GetCType(ch) & CTYPE_SJISFirst) != 0; }
	static bool IsSJISSecond(char ch)		{ return (GetCType(ch) & CTYPE_SJISSecond) != 0; }
	static bool IsUTF8First(char ch)		{ return (GetCType(ch) & CTYPE_UTF8First) != 0; }
	static bool IsUTF8Follower(char ch)		{ return (GetCType(ch) & CTYPE_UTF8Follower) != 0; }
	static bool IsSymbolExtra(char ch)		{ return (GetCType(ch) & CTYPE_SymbolExtra) != 0; }
	static bool IsLower(char ch)			{ return (GetCType(ch) & CTYPE_Lower) != 0; }
	static bool IsUpper(char ch)			{ return (GetCType(ch) & CTYPE_Upper) != 0; }
	static bool IsURIC(char ch)				{ return (GetCType(ch) & CTYPE_URIC) != 0; }
	static bool IsSymbolFirst(char ch)		{ return (GetCType(ch) & CTYPE_SymbolFirst) != 0; }
	static bool IsSymbolFollower(char ch)	{ return (GetCType(ch) & CTYPE_SymbolFollower) != 0; }
	static char ConvHexDigit(char ch) {
		return
			('0' <= ch && ch <= '9')? ch - '0' :
			('A' <= ch && ch <= 'F')? ch - 'A' + 10 :
			('a' <= ch && ch <= 'f')? ch - 'a' + 10 : 0;
	}
	static char ConvOctDigit(char ch) { return ('0' <= ch && ch <= '7')? ch - '0' : 0; }
	static char ConvBinDigit(char ch) { return ('0' <= ch && ch <= '1')? ch - '0' : 0; }
	static char ToUpper(char ch) { return ('a' <= ch && ch <= 'z')? ch - 'a' + 'A' : ch; }
	static char ToLower(char ch) { return ('A' <= ch && ch <= 'Z')? ch - 'A' + 'a' : ch; }
};

}

#endif
