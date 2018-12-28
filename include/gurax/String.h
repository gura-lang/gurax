//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"

namespace Gurax {

class StringList;
	
//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
class String : public std::string {
public:
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
public:
	static const String Empty;
private:
	static UInt32 _ctypeTbl[256];
	static int _convBinDigitTbl[256];
	static int _convOctDigitTbl[256];
	static int _convHexDigitTbl[256];
	static char _toUpperTbl[256];
	static char _toLowerTbl[256];
	static char _toEscapedTbl[256];
public:
	String(const std::string& src) : std::string(src) {}
	String(std::string&& src) : std::string(std::move(src)) {}
	// Inherits constructors
	using std::string::string;
public:
	static void Bootup();
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
	static int ConvBinDigit(char ch)		{ return _convBinDigitTbl[static_cast<UChar>(ch)]; }
	static int ConvOctDigit(char ch)		{ return _convOctDigitTbl[static_cast<UChar>(ch)]; }
	static int ConvHexDigit(char ch)		{ return _convHexDigitTbl[static_cast<UChar>(ch)]; }
	static char ToUpper(char ch)			{ return _toUpperTbl[static_cast<UChar>(ch)]; }
	static char ToLower(char ch)			{ return _toLowerTbl[static_cast<UChar>(ch)]; }
	static char ToEscaped(char ch)			{ return _toEscapedTbl[static_cast<UChar>(ch)]; }
public:
	String PickChar(size_t idx) const;
	const_iterator Forward(const_iterator p) const;
	UInt64 NextUTF8(const_iterator* pp) const;
	static UInt64 NextUTF8(const char** pp);
	UInt32 NextUTF32(const_iterator* pp) const;
	static UInt32 NextUTF32(const char** pp);
	void AppendUTF8(UInt64 codeUTF8);
	void AppendUTF32(UInt32 codeUTF32);
public:
	String MakeQuoted(bool surroundFlag = false) { return MakeQuoted(c_str(), surroundFlag); }
	static String MakeQuoted(const char* str, bool surroundFlag = true);
public:
	size_t CalcHash() const { return CalcHash(c_str(), size()); }
	static size_t CalcHash(const char* str);
	static size_t CalcHash(const char* str, size_t len);
};

inline String operator+(const String& v1, const String& v2) {
	return String(static_cast<std::string>(v1) + static_cast<std::string>(v2));
}

//------------------------------------------------------------------------------
// StringList
//------------------------------------------------------------------------------
class StringList : public std::vector<String> {
public:
	// Inherits constructors
	using std::vector<String>::vector;
};

//------------------------------------------------------------------------------
// StringReferable
//------------------------------------------------------------------------------
class StringReferable : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(StringReferable);
private:
	String _str;
public:
	// Constructor
	StringReferable() = delete;
	explicit StringReferable(String str) : _str(std::move(str)) {}
	// Copy constructor/operator
	StringReferable(const StringReferable& src) = delete;
	StringReferable& operator=(const StringReferable& src) = delete;
	// Move constructor/operator
	StringReferable(StringReferable&& src) = delete;
	StringReferable& operator=(StringReferable&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~StringReferable() = default;
public:
	const char* GetString() { return _str.c_str(); }
	String& GetStringSTL() { return _str; }
	const String& GetStringSTL() const { return _str; }
};

}

#endif
