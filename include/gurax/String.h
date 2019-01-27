//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"

namespace Gurax {

class StringList;
class ObjectList;

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
class String : public std::string {
public:
	// Algorithm operators
	struct EqualTo {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsEqualTo(str2);
		}
	};
	struct EqualToICase {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsEqualToICase(str2);
		}
	};
	struct LessThan {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsLessThan(str2);
		}
	};
	struct LessThanICase {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsLessThanICase(str2);
		}
	};
	struct GreaterThan {
		bool operator()(const String& str1, const String& str2) const {
			return str2.IsLessThan(str1);
		}
	};
	struct GreaterThanICase {
		bool operator()(const String& str1, const String& str2) const {
			return str2.IsLessThanICase(str1);
		}
	};
	struct Hash {
		bool operator()(const String& str) const {
			return str.CalcHash();
		}
	};
	struct CmpChar {
		int operator()(char ch1, char ch2) const {
			return static_cast<int>(ch1) - ch2;
		}
	};
	struct CmpCharICase {
		int operator()(char ch1, char ch2) const {
			return static_cast<int>(ToUpper(ch1)) - ToUpper(ch2);
		}
	};
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
	static int    _convBinDigitTbl[256];
	static int    _convOctDigitTbl[256];
	static int    _convHexDigitTbl[256];
	static char   _toUpperTbl[256];
	static char   _toLowerTbl[256];
	static char   _toEscapedTbl[256];
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
	const_iterator Forward(const_iterator p, size_t nChars = 1, size_t *pnCharsActual = nullptr) const;
	static const char* Forward(const char* p, size_t nChars = 1, size_t *pnCharsActual = nullptr);
	UInt64 NextUTF8(const_iterator* pp) const;
	static UInt64 NextUTF8(const char** pp);
	UInt32 NextUTF32(const_iterator* pp) const;
	static UInt32 NextUTF32(const char** pp);
public:
	void AppendUTF8(UInt64 codeUTF8);
	void AppendUTF32(UInt32 codeUTF32);
	String& PrintfV(const char* format, va_list ap);
	String& Printf(const char* format, ...);
	String& PrintFmt(const char* format, const ObjectList& objectList);
public:
	String MakeQuoted(bool surroundFlag = false) const { return MakeQuoted(c_str(), surroundFlag); }
	static String MakeQuoted(const char* str, bool surroundFlag = true);
public:
	Double ToNumber(bool* pSuccessFlag = nullptr) const { return ToNumber(c_str(), pSuccessFlag); }
	static Double ToNumber(const char* str, bool* pSuccessFlag = nullptr);
public:
	size_t CalcHash() const { return CalcHash(c_str(), size()); }
	static size_t CalcHash(const char* str);
	static size_t CalcHash(const char* str, size_t len);
	static bool IsEqualTo(const char* str1, const char* str2)		{ return ::strcmp(str1, str2) == 0; }
	bool IsEqualTo(const char* str) const							{ return IsEqualTo(c_str(), str); }
	bool IsEqualTo(const String& str) const							{ return IsEqualTo(c_str(), str.c_str()); }
	static bool IsEqualToICase(const char* str1, const char* str2)	{ return ::strcasecmp(str1, str2) == 0; }
	bool IsEqualToICase(const char* str) const						{ return IsEqualToICase(c_str(), str); }
	bool IsEqualToICase(const String& str) const					{ return IsEqualToICase(c_str(), str.c_str()); }
	static bool IsLessThan(const char* str1, const char* str2)		{ return ::strcmp(str1, str2) < 0; }
	bool IsLessThan(const char* str) const							{ return IsLessThan(c_str(), str); }
	bool IsLessThan(const String& str) const						{ return IsLessThan(c_str(), str.c_str()); }
	static bool IsLessThanICase(const char* str1, const char* str2)	{ return ::strcasecmp(str1, str2) < 0; }
	bool IsLessThanICase(const char* str) const						{ return IsLessThanICase(c_str(), str); }
	bool IsLessThanICase(const String& str) const					{ return IsLessThanICase(c_str(), str.c_str()); }
public:
	static const char* Find(const char* str, const char* sub) {
		return Find_Tmpl<CmpChar>(str, sub);
	}
	static const_iterator Find(const_iterator pStr, const_iterator pStrEnd, const char* sub) {
		return Find_Tmpl<CmpChar>(pStr, pStrEnd, sub);
	}
	const_iterator Find(const_iterator pStr, const char* sub) const {
		return Find_Tmpl<CmpChar>(pStr, end(), sub);
	}
	const_iterator Find(const char* sub) const {
		return Find_Tmpl<CmpChar>(begin(), end(), sub);
	}
	static const char* FindICase(const char* str, const char* sub) {
		return Find_Tmpl<CmpCharICase>(str, sub);
	}
	static const_iterator FindICase(const_iterator pStr, const_iterator pStrEnd, const char* sub) {
		return Find_Tmpl<CmpCharICase>(pStr, pStrEnd, sub);
	}
	const_iterator FindICase(const_iterator pStr, const char* sub) const {
		return Find_Tmpl<CmpCharICase>(pStr, end(), sub);
	}
	const_iterator FindICase(const char* sub) const {
		return Find_Tmpl<CmpCharICase>(begin(), end(), sub);
	}
	static const char* StartsWith(const char* str, const char* sub) {
		return StartsWith_Tmpl<CmpChar>(str, sub);
	}
	const_iterator StartsWith(const_iterator pStr, const char* sub) const {
		return StartsWith_Tmpl<CmpChar>(pStr, end(), sub);
	}
	static const char* StartsWithICase(const char* str, const char* sub) {
		return StartsWith_Tmpl<CmpCharICase>(str, sub);
	}
	const_iterator StartsWithICase(const_iterator pStr, const char* sub) const {
		return StartsWith_Tmpl<CmpCharICase>(pStr, end(), sub);
	}
	static const char* EndsWith(const char* str, const char* sub) {
		return EndsWith_Tmpl<CmpChar>(str, sub);
	}
	static const char* EndsWith(const char* str, size_t posEnd, const char* sub) {
		return EndsWith_Tmpl<CmpChar>(str, posEnd, sub);
	}
	static const char* EndsWithICase(const char* str, const char* sub) {
		return EndsWith_Tmpl<CmpCharICase>(str, sub);
	}
	static const char* EndsWithICase(const char* str, size_t posEnd, const char* sub) {
		return EndsWith_Tmpl<CmpCharICase>(str, posEnd, sub);
	}
private:
	template<typename CmpChar>
	static const char* Find_Tmpl(const char* str, const char* sub);
	template<typename CmpChar>
	static const_iterator Find_Tmpl(const_iterator pStr, const_iterator pStrEnd, const char* sub);
	template<typename CmpChar>
	static const char* StartsWith_Tmpl(const char* str, const char* sub);
	template<typename CmpChar>
	static const_iterator StartsWith_Tmpl(const_iterator pStr, const_iterator pStrEnd, const char* sub);
	template<typename CmpChar>
	static const char* EndsWith_Tmpl(const char* str, const char* sub);
	template<typename CmpChar>
	static const char* EndsWith_Tmpl(const char* str, size_t posEnd, const char* sub);
public:
	static size_t Length(const char* str);
	size_t Length() const { return Length(c_str()); }
	static size_t Width(const char* str);
	size_t Width() const { return Width(c_str()); }
};

inline String operator+(const String& v1, const String& v2) {
	return String(static_cast<std::string>(v1) + static_cast<std::string>(v2));
}

template<typename CmpChar>
const char* String::Find_Tmpl(const char* str, const char* sub)
{
	for ( ; *str != '\0'; str++) {
		const char* p1 = str;
		const char* p2 = sub;
		for ( ; *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) break;
		if (*p2 == '\0') return str;
	}
	return nullptr;
}

template<typename CmpChar>
String::const_iterator String::Find_Tmpl(const_iterator pStr, const_iterator pStrEnd, const char* sub)
{
	for ( ; pStr != pStrEnd; pStr++) {
		String::const_iterator p1 = pStr;
		const char* p2 = sub;
		for ( ; *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) break;
		if (*p2 == '\0') return pStr;
	}
	return pStrEnd;
}

template<typename CmpChar>
const char* String::StartsWith_Tmpl(const char* str, const char* sub)
{
	const char* p1 = str;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) return nullptr;
	return p1;
}

template<typename CmpChar>
String::const_iterator String::StartsWith_Tmpl(const_iterator pStr, const_iterator pStrEnd, const char* sub)
{
	const_iterator p1 = pStr;
	const char* p2 = sub;
	for ( ; p1 != pStrEnd && *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) return pStrEnd;
	return p1;
}

template<typename CmpChar>
const char* String::EndsWith_Tmpl(const char* str, const char* sub)
{
	size_t len = ::strlen(sub);
	const char* p = str + ::strlen(str);
	if (str + len > p) return nullptr;
	p -= len;
	const char* p1 = p;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) return nullptr;
	return p;
}

template<typename CmpChar>
const char* String::EndsWith_Tmpl(const char* str, size_t posEnd, const char* sub)
{
	size_t len = ::strlen(sub);
	const char* p = String::Forward(str, posEnd);
	if (str + len > p) return nullptr;
	p -= len;
	const char* p1 = p;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (CmpChar()(*p1, *p2) != 0) return nullptr;
	return p;
}

//------------------------------------------------------------------------------
// StringList
//------------------------------------------------------------------------------
class StringList : public std::vector<String> {
public:
	StringList& Sort(SortOrder sortOrder = SortOrder::Ascend);
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

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringStyle {
public:
	struct Flag {
		static const UInt32 AsSource	= (1 << 0);
		static const UInt32 Cram		= (1 << 1);
		static const UInt32 MultiLine	= (1 << 2);
		static const UInt32 UpperCase	= (1 << 3);
	};
private:
	UInt32 _flags;
	static const char* _strsComma[2];
	static const char* _strsColon[2];
	static const char* _strsSemicolon[2];
public:
	static const StringStyle Empty;
public:
	// Constructor
	StringStyle() : _flags(0) {}
	// Copy constructor/operator
	StringStyle(const StringStyle& src) : _flags(src._flags) {}
	StringStyle& operator=(const StringStyle& src) { _flags = src._flags; return *this; }
	// Move constructor/operator
	StringStyle(StringStyle&& src) = delete;
	StringStyle& operator=(StringStyle&& src) noexcept = delete;
	// Destructor
	virtual ~StringStyle() = default;
public:	
	StringStyle& AsSource()		{ _flags |= Flag::AsSource; return *this; }
	StringStyle& Cram()			{ _flags |= Flag::Cram; return *this; }
	StringStyle& MultiLine()	{ _flags |= Flag::MultiLine; return *this; }
	StringStyle& UpperCase()	{ _flags |= Flag::UpperCase; return *this; }
	bool IsAsSource() const		{ return (_flags & Flag::AsSource) != 0; }
	bool IsCram() const			{ return (_flags & Flag::Cram) != 0; }
	bool IsMultiLine() const	{ return (_flags & Flag::MultiLine) != 0; }
	bool IsUpperCase() const	{ return (_flags & Flag::UpperCase) != 0; }
	const char* GetComma() const { return _strsComma[IsCram()]; }
	const char* GetColon() const { return _strsColon[IsCram()]; }
	const char* GetSemicolon() const	{ return _strsSemicolon[IsCram()]; }
};

}

#endif
