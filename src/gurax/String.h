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
	struct CType {
		static constexpr UInt32 Alpha			= 1 << 0;
		static constexpr UInt32 Digit			= 1 << 1;
		static constexpr UInt32 HexDigit		= 1 << 2;
		static constexpr UInt32 OctDigit		= 1 << 3;
		static constexpr UInt32 BinDigit		= 1 << 4;
		static constexpr UInt32 White			= 1 << 5;
		static constexpr UInt32 Space			= 1 << 6;
		static constexpr UInt32 SJISFirst		= 1 << 7;
		static constexpr UInt32 SJISSecond		= 1 << 8;
		static constexpr UInt32 UTF8First		= 1 << 9;
		static constexpr UInt32 UTF8Follower	= 1 << 10;
		static constexpr UInt32 SymbolExtra		= 1 << 11;
		static constexpr UInt32 Lower			= 1 << 12;
		static constexpr UInt32 Upper			= 1 << 13;
		static constexpr UInt32 URIC			= 1 << 14;
		static constexpr UInt32 SymbolFirst		= Alpha | SymbolExtra | UTF8First;
		static constexpr UInt32 SymbolFollower	= SymbolFirst | Digit | UTF8Follower;
	};
	static const UInt32 _ctypeTbl[];
public:
	using std::string::string;	// inherits constructors
public:
	// Character operation
	static UInt32 GetCType(char ch)			{ return _ctypeTbl[static_cast<UChar>(ch)]; }
	static bool IsAlpha(char ch)			{ return (GetCType(ch) & CType::Alpha) != 0; }
	static bool IsDigit(char ch)			{ return (GetCType(ch) & CType::Digit) != 0; }
	static bool IsHexDigit(char ch)			{ return (GetCType(ch) & CType::HexDigit) != 0; }
	static bool IsOctDigit(char ch)			{ return (GetCType(ch) & CType::OctDigit) != 0; }
	static bool IsBinDigit(char ch)			{ return (GetCType(ch) & CType::BinDigit) != 0; }
	static bool IsWhite(char ch)			{ return (GetCType(ch) & CType::White) != 0; }
	static bool IsSpace(char ch)			{ return (GetCType(ch) & CType::Space) != 0; }
	static bool IsSJISFirst(char ch)		{ return (GetCType(ch) & CType::SJISFirst) != 0; }
	static bool IsSJISSecond(char ch)		{ return (GetCType(ch) & CType::SJISSecond) != 0; }
	static bool IsUTF8First(char ch)		{ return (GetCType(ch) & CType::UTF8First) != 0; }
	static bool IsUTF8Follower(char ch)		{ return (GetCType(ch) & CType::UTF8Follower) != 0; }
	static bool IsSymbolExtra(char ch)		{ return (GetCType(ch) & CType::SymbolExtra) != 0; }
	static bool IsLower(char ch)			{ return (GetCType(ch) & CType::Lower) != 0; }
	static bool IsUpper(char ch)			{ return (GetCType(ch) & CType::Upper) != 0; }
	static bool IsURIC(char ch)				{ return (GetCType(ch) & CType::URIC) != 0; }
	static bool IsSymbolFirst(char ch)		{ return (GetCType(ch) & CType::SymbolFirst) != 0; }
	static bool IsSymbolFollower(char ch)	{ return (GetCType(ch) & CType::SymbolFollower) != 0; }
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
public:
	String PickChar(size_t idx) const;
	const_iterator Forward(const_iterator p) const;
	UInt64 NextUTF8(const_iterator* pp) const;
	static UInt64 NextUTF8(const char** pp);
	UInt32 NextUTF32(const_iterator* pp) const;
	static UInt32 NextUTF32(const char** pp);
	void AppendUTF8(UInt64 codeUTF8);
	void AppendUTF32(UInt32 codeUTF32);
};

}

#endif
