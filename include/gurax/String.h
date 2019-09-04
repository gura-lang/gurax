//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"

namespace Gurax {

class StringList;
class ValueList;

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
public:
	using CTypes = UInt32;
	struct CType {
		static constexpr CTypes Alpha			= 1 << 0;
		static constexpr CTypes Digit			= 1 << 1;
		static constexpr CTypes HexDigit		= 1 << 2;
		static constexpr CTypes OctDigit		= 1 << 3;
		static constexpr CTypes BinDigit		= 1 << 4;
		static constexpr CTypes White			= 1 << 5;
		static constexpr CTypes Space			= 1 << 6;
		static constexpr CTypes SJISFirst		= 1 << 7;
		static constexpr CTypes SJISSecond		= 1 << 8;
		static constexpr CTypes UTF8First		= 1 << 9;
		static constexpr CTypes UTF8Follower	= 1 << 10;
		static constexpr CTypes SymbolExtra		= 1 << 11;
		static constexpr CTypes Lower			= 1 << 12;
		static constexpr CTypes Upper			= 1 << 13;
		static constexpr CTypes URIC			= 1 << 14;
		static constexpr CTypes Print			= 1 << 15;
		static constexpr CTypes SymbolFirst		= Alpha | SymbolExtra | UTF8First;
		static constexpr CTypes SymbolFollower	= SymbolFirst | Digit | UTF8Follower;
	};
public:
	static const String Empty;
private:
	static CTypes _ctypesTbl[256];
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
	static bool CheckPosition(size_t len, Int pos, Int posRaw);
	static bool CheckPosition(size_t len, Int pos) { return CheckPosition(len, pos, pos); }
	static bool CheckPosition(const char* str, Int pos) { return CheckPosition(::strlen(str), pos); }
	bool CheckPosition(Int pos) const { return CheckPosition(size(), pos); }
	static bool FixPosition(size_t len, Int* pPos);
	static bool FixPosition(const char* str, Int* pPos) { return FixPosition(::strlen(str), pPos); }
	bool FixPosition(Int* pPos) const { return FixPosition(size(), pPos); }
public:
	// Character operation
	static CTypes GetCTypes(char ch)		{ return _ctypesTbl[static_cast<UChar>(ch)];		}
	static bool IsAlpha(char ch)			{ return (GetCTypes(ch) & CType::Alpha) != 0;		}
	static bool IsDigit(char ch)			{ return (GetCTypes(ch) & CType::Digit) != 0;		}
	static bool IsHexDigit(char ch)			{ return (GetCTypes(ch) & CType::HexDigit) != 0;	}
	static bool IsOctDigit(char ch)			{ return (GetCTypes(ch) & CType::OctDigit) != 0;	}
	static bool IsBinDigit(char ch)			{ return (GetCTypes(ch) & CType::BinDigit) != 0;	}
	static bool IsWhite(char ch)			{ return (GetCTypes(ch) & CType::White) != 0;		}
	static bool IsSpace(char ch)			{ return (GetCTypes(ch) & CType::Space) != 0;		}
	static bool IsSJISFirst(char ch)		{ return (GetCTypes(ch) & CType::SJISFirst) != 0;	}
	static bool IsSJISSecond(char ch)		{ return (GetCTypes(ch) & CType::SJISSecond) != 0;	}
	static bool IsUTF8First(char ch)		{ return (GetCTypes(ch) & CType::UTF8First) != 0;	}
	static bool IsUTF8Follower(char ch)		{ return (GetCTypes(ch) & CType::UTF8Follower) != 0; }
	static bool IsSymbolExtra(char ch)		{ return (GetCTypes(ch) & CType::SymbolExtra) != 0; }
	static bool IsLower(char ch)			{ return (GetCTypes(ch) & CType::Lower) != 0;		}
	static bool IsUpper(char ch)			{ return (GetCTypes(ch) & CType::Upper) != 0;		}
	static bool IsURIC(char ch)				{ return (GetCTypes(ch) & CType::URIC) != 0;		}
	static bool IsPrint(char ch)			{ return (GetCTypes(ch) & CType::Print) != 0;		}
	static bool IsSymbolFirst(char ch)		{ return (GetCTypes(ch) & CType::SymbolFirst) != 0;	}
	static bool IsSymbolFollower(char ch)	{ return (GetCTypes(ch) & CType::SymbolFollower) != 0; }
	static int ConvBinDigit(char ch)		{ return _convBinDigitTbl[static_cast<UChar>(ch)];	}
	static int ConvOctDigit(char ch)		{ return _convOctDigitTbl[static_cast<UChar>(ch)];	}
	static int ConvHexDigit(char ch)		{ return _convHexDigitTbl[static_cast<UChar>(ch)];	}
	static char ToUpper(char ch)			{ return _toUpperTbl[static_cast<UChar>(ch)];		}
	static char ToLower(char ch)			{ return _toLowerTbl[static_cast<UChar>(ch)];		}
	static char ToEscaped(char ch)			{ return _toEscapedTbl[static_cast<UChar>(ch)];		}
public:
	String PickChar(size_t idx) const;
	static const char* ForwardToTerminal(const char* p) { return p + ::strlen(p); }
	static const char* Forward(const char* p, size_t nChars = 1, size_t *pnCharsActual = nullptr);
	static const char* Backward(const char* p, const char* pHead, size_t nChars = 1, size_t *pnCharsActual = nullptr);
	static const_iterator Forward(const_iterator p, const_iterator pEnd,
								  size_t nChars = 1, size_t *pnCharsActual = nullptr);
	const_iterator Forward(const_iterator p, size_t nChars = 1, size_t *pnCharsActual = nullptr) const {
		return Forward(p, end(), nChars, pnCharsActual);
	}
	const_iterator Forward(size_t nChars = 1, size_t *pnCharsActual = nullptr) const {
		return Forward(begin(), end(), nChars, pnCharsActual);
	}
	static UInt64 NextUTF8(const char** pp);
	UInt64 NextUTF8(const_iterator* pp) const;
	static UInt32 NextUTF32(const char** pp);
	UInt32 NextUTF32(const_iterator* pp) const;
public:
	String& AppendNTimes(const char* str, size_t n);
	String& AppendNChars(const char* str, size_t len);
	String& AppendUTF8(UInt64 codeUTF8);
	String& AppendUTF32(UInt32 codeUTF32);
public:
	String& PrintfV(const char* format, va_list ap);
	String& Printf(const char* format, ...);
	String& PrintFmt(const char* format, const ValueList& valueList);
public:
	static String MakeQuoted(const char* str, bool surroundFlag);
	String MakeQuoted(bool surroundFlag) const { return MakeQuoted(c_str(), surroundFlag); }
public:
	static Double ToNumber(const char* str, bool* pSuccessFlag = nullptr);
	Double ToNumber(bool* pSuccessFlag = nullptr) const { return ToNumber(c_str(), pSuccessFlag); }
public:
	static size_t CalcHash(const char* str);
	static size_t CalcHash(const char* str, size_t len);
	size_t CalcHash() const { return CalcHash(c_str(), size()); }
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
	template<typename T_CharCmp>
	static const char* Find(const char* str, const char* sub, const char** pStrNext);
	template<typename T_CharCmp>
	static const_iterator Find(const_iterator pStr, const_iterator pStrEnd, const char* sub);
	template<typename T_CharCmp>
	const_iterator Find(const_iterator pStr, const char* sub) const {
		return Find<T_CharCmp>(pStr, end(), sub);
	}
	template<typename T_CharCmp>
	const_iterator Find(const char* sub) const {
		return Find<T_CharCmp>(begin(), end(), sub);
	}
public:
	template<typename T_CharCmp>
	static const char* StartsWith(const char* str, const char* sub);
	template<typename T_CharCmp>
	static const_iterator StartsWith(const_iterator pStr, const_iterator pStrEnd, const char* sub);
	template<typename T_CharCmp>
	const_iterator StartsWith(const_iterator pStr, const char* sub) const {
		return StartsWith<T_CharCmp>(pStr, end(), sub);
	}
	template<typename T_CharCmp>
	const_iterator StartsWith(const char* sub) const {
		return StartsWith<T_CharCmp>(begin(), end(), sub);
	}
public:
	template<typename T_CharCmp>
	static const char* EndsWith(const char* str, const char* sub);
	template<typename T_CharCmp>
	static const char* EndsWith(const char* str, size_t posEnd, const char* sub);
public:
	static size_t Length(const char* str);
	size_t Length() const { return Length(c_str()); }
	static size_t CalcPos(const char* str, const char* sub);
	static size_t CalcPos(const_iterator pStr, const_iterator pStrSub);
	size_t CalcPos(const_iterator pStrSub) const { return CalcPos(begin(), pStrSub); }
	static size_t Width(const char* str);
	size_t Width() const { return Width(c_str()); }
public:
	// Alignment/Extraction
	static String Center(const char* str, size_t width, const char* padding);
	String Center(size_t width, const char* padding) const { return Center(c_str(), width, padding); }
	static String LJust(const char* str, size_t width, const char* padding);
	String LJust(size_t width, const char* padding) const { return LJust(c_str(), width, padding); }
	static String RJust(const char* str, size_t width, const char* padding);
	String RJust(size_t width, const char* padding) const { return RJust(c_str(), width, padding); }
	static String Left(const char* str, size_t len);
	String Left(size_t len) const { return Left(c_str(), len); }
	static String Right(const char* str, size_t len);
	String Right(size_t len) const { return Right(c_str(), len); }
	static String Mid(const char* str, int start, size_t len);
	String Mid(int start, size_t len) const { return Mid(c_str(), start, len); }
public:
	// Replacement
	template<typename T_CharCmp>
	static String Replace(const char* str, const char* sub, const char* replace);
	template<typename T_CharCmp>
	static String Replace(const char* str, const char* sub, const char* replace, int nMaxReplace);
	template<typename T_CharCmp>
	String Replace(const char* sub, const char* replace) const {
		return Replace<T_CharCmp>(c_str(), sub, replace);
	}
	template<typename T_CharCmp>
	String Replace(const char* sub, const char* replace, int nMaxReplace) const {
		return Replace<T_CharCmp>(c_str(), sub, replace, nMaxReplace);
	}
public:
	// Multiple Replacement
	template<typename T_CharCmp>
	static String ReplaceM(const char* str, const StringList& map);
	template<typename T_CharCmp>
	static String ReplaceM(const char* str, const StringList& map, int nMaxReplace);
	template<typename T_CharCmp>
	String ReplaceM(const StringList& map) const {
		return ReplaceM<T_CharCmp>(c_str(), map);
	}
	template<typename T_CharCmp>
	String ReplaceM(const StringList& map, int nMaxReplace) const {
		return ReplaceM<T_CharCmp>(c_str(), map, nMaxReplace);
	}
public:
	// Modification
	String Upper() const { return Upper(c_str()); }
	static String Upper(const char* str);
	String Lower() const { return Lower(c_str()); }
	static String Lower(const char* str);
	String Capitalize() const { return Capitalize(c_str()); }
	static String Capitalize(const char* str);
	String Strip(bool stripLeftFlag, bool stripRightFlag) const {
		return Strip(c_str(), stripLeftFlag, stripRightFlag);
	}
	static String Strip(const char* str, bool stripLeftFlag, bool stripRightFlag);
	String Chop(bool eolOnlyFlag) const { return Chop(c_str(), eolOnlyFlag); }
	static String Chop(const char* str, bool eolOnlyFlag);
	void Split(StringList& strs, char sep) const { return Split(strs, c_str(), sep); }
	static void Split(StringList& strs, const char* str, char sep);
public:
	static bool IsCTypes(const char* str, CTypes ctypes);
	static bool IsAlnum(const char* str) { return IsCTypes(str, CType::Alpha | CType::Digit); }
	bool IsAlnum() const { return IsAlnum(c_str()); }
	static bool IsAlpha(const char* str) { return IsCTypes(str, CType::Alpha); }
	bool IsAlpha() const { return IsAlpha(c_str()); }
	static bool IsDigit(const char* str) { return IsCTypes(str, CType::Digit); }
	bool IsDigit() const { return IsDigit(c_str()); }
	static bool IsEmpty(const char* str) { return *str == '\0'; }
	bool IsEmpty() const { return IsEmpty(c_str()); }
	static bool IsSpace(const char* str) { return IsCTypes(str, CType::Space); }
	bool IsSpace() const { return IsSpace(c_str()); }
public:
	static void IssueError_InvalidFormatOfNumber();
	static void IssueError_IndexOutOfRange(size_t len, Int pos);
	static void IssueError_IndexOutOfRange(const char* str, Int pos) {
		return IssueError_IndexOutOfRange(::strlen(str), pos);
	}
	void IssueError_IndexOutOfRange(Int pos) const {
		return IssueError_IndexOutOfRange(size(), pos);
	}
};

struct CharCase {
	int operator()(char ch1, char ch2) const {
		return static_cast<int>(ch1) - ch2;
	}
};

struct CharICase {
	int operator()(char ch1, char ch2) const {
		return static_cast<int>(String::ToUpper(ch1)) - String::ToUpper(ch2);
	}
};

inline String operator+(const String& v1, const String& v2) {
	return String(static_cast<std::string>(v1) + static_cast<std::string>(v2));
}

//------------------------------------------------------------------------------
// StringList
//------------------------------------------------------------------------------
class StringList : public std::vector<String> {
public:
	static const StringList Empty;
public:
	StringList& Sort() { std::sort(begin(), end()); return *this; }
	StringList& Sort(SortOrder sortOrder);
	StringList& Unique() { erase(std::unique(begin(), end()), end()); return *this; }
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
	static RefPtr<StringReferable> Empty;
public:
	// Constructor
	StringReferable() {}
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
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags AsSource		= (1 << 0);
		static const Flags AsValue		= (1 << 1);
		static const Flags Cram			= (1 << 2);
		static const Flags MultiLine	= (1 << 3);
		static const Flags UpperCase	= (1 << 4);
		static const Flags Verbose		= (1 << 5);
		static const Flags Digest		= (1 << 6);
		static const Flags AddressInfo	= (1 << 7);
	};
private:
	Flags _flags;
	String _margin;
	String _indentUnit;
	static const char* _strsComma[2];
	static const char* _strsColon[2];
	static const char* _strsSemicolon[2];
public:
	static const StringStyle Empty;
public:
	// Constructor
	explicit StringStyle(const char* indentUnit = "  ") : _flags(Flag::None), _indentUnit(indentUnit) {}
	// Copy constructor/operator
	StringStyle(const StringStyle& src) : _flags(src._flags), _indentUnit(src._indentUnit) {}
	StringStyle& operator=(const StringStyle& src) {
		_flags = src._flags; _indentUnit = src._indentUnit; return *this;
	}
	// Move constructor/operator
	StringStyle(StringStyle&& src) = delete;
	StringStyle& operator=(StringStyle&& src) noexcept = delete;
	// Destructor
	virtual ~StringStyle() = default;
public:	
	StringStyle& SetMargin(const char* margin) { _margin = margin; return *this; }
	StringStyle& SetIndentUnit(const char* indentUnit) { _indentUnit = indentUnit; return *this; }
	StringStyle& AsSource()				{ _flags |= Flag::AsSource; return *this; }
	StringStyle& NoAsSource()			{ _flags &= ~Flag::AsSource; return *this; }
	StringStyle& AsValue()				{ _flags |= Flag::AsValue; return *this; }
	StringStyle& NoAsValue()			{ _flags &= ~Flag::AsValue; return *this; }
	StringStyle& Cram()					{ _flags |= Flag::Cram; return *this; }
	StringStyle& NoCram()				{ _flags &= ~Flag::Cram; return *this; }
	StringStyle& MultiLine()			{ _flags |= Flag::MultiLine; return *this; }
	StringStyle& NoMultiLine()			{ _flags &= ~Flag::MultiLine; return *this; }
	StringStyle& UpperCase()			{ _flags |= Flag::UpperCase; return *this; }
	StringStyle& NoUpperCase()			{ _flags &= ~Flag::UpperCase; return *this; }
	StringStyle& Verbose()				{ _flags |= Flag::Verbose; return *this; }
	StringStyle& NoVerbose()			{ _flags &= ~Flag::Verbose; return *this; }
	StringStyle& Digest()				{ _flags |= Flag::Digest; return *this; }
	StringStyle& NoDigest()				{ _flags &= ~Flag::Digest; return *this; }
	StringStyle& AddressInfo()			{ _flags |= Flag::AddressInfo; return *this; }
	StringStyle& NoAddressInfo()		{ _flags &= ~Flag::AddressInfo; return *this; }
	bool IsAsSource() const				{ return (_flags & Flag::AsSource) != 0; }
	bool IsAsValue() const				{ return (_flags & Flag::AsValue) != 0; }
	bool IsCram() const					{ return (_flags & Flag::Cram) != 0; }
	bool IsMultiLine() const			{ return (_flags & Flag::MultiLine) != 0; }
	bool IsUpperCase() const			{ return (_flags & Flag::UpperCase) != 0; }
	bool IsVerbose() const				{ return (_flags & Flag::Verbose) != 0; }
	bool IsDigest() const				{ return (_flags & Flag::Digest) != 0; }
	bool IsAddressInfo() const			{ return (_flags & Flag::AddressInfo) != 0; }
	const char* GetMargin() const		{ return _margin.c_str(); }
	const char* GetIndentUnit() const	{ return _indentUnit.c_str(); }
	const char* GetComma() const		{ return _strsComma[static_cast<int>(IsCram())]; }
	const char* GetColon() const		{ return _strsColon[static_cast<int>(IsCram())]; }
	const char* GetSemicolon() const	{ return _strsSemicolon[static_cast<int>(IsCram())]; }
};

//------------------------------------------------------------------------------
// Templates of String
//------------------------------------------------------------------------------
template<typename T_CharCmp>
const char* String::Find(const char* str, const char* sub, const char** pStrNext)
{
	for ( ; *str != '\0'; str++) {
		const char* p1 = str;
		const char* p2 = sub;
		for ( ; *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) break;
		if (*p2 == '\0') {
			*pStrNext = p1;
			return str;
		}
	}
	*pStrNext = str;
	return str;
}

template<typename T_CharCmp>
String::const_iterator String::Find(const_iterator pStr, const_iterator pStrEnd, const char* sub)
{
	for ( ; pStr != pStrEnd; pStr++) {
		String::const_iterator p1 = pStr;
		const char* p2 = sub;
		for ( ; *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) break;
		if (*p2 == '\0') return pStr;
	}
	return pStrEnd;
}

template<typename T_CharCmp>
const char* String::StartsWith(const char* str, const char* sub)
{
	const char* p1 = str;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) return nullptr;
	return p1;
}

template<typename T_CharCmp>
String::const_iterator String::StartsWith(const_iterator pStr, const_iterator pStrEnd, const char* sub)
{
	const_iterator p1 = pStr;
	const char* p2 = sub;
	for ( ; p1 != pStrEnd && *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) return pStrEnd;
	return p1;
}

template<typename T_CharCmp>
const char* String::EndsWith(const char* str, const char* sub)
{
	size_t len = ::strlen(sub);
	const char* p = str + ::strlen(str);
	if (str + len > p) return nullptr;
	p -= len;
	const char* p1 = p;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) return nullptr;
	return p;
}

template<typename T_CharCmp>
const char* String::EndsWith(const char* str, size_t posEnd, const char* sub)
{
	size_t len = ::strlen(sub);
	const char* p = String::Forward(str, posEnd);
	if (str + len > p) return nullptr;
	p -= len;
	const char* p1 = p;
	const char* p2 = sub;
	for ( ; *p2 != '\0'; p1++, p2++) if (T_CharCmp()(*p1, *p2) != 0) return nullptr;
	return p;
}

template<typename T_CharCmp>
String String::Replace(const char* str, const char* sub, const char* replace)
{
	String strRtn;
	if (*sub == '\0') {
		strRtn += replace;
		const char* p = str;
		for ( ; *p != '\0'; p = Forward(p)) {
			strRtn += *p;
			strRtn += replace;
		}
		//strRtn += p;
	} else {
		const char* pLeft = str;
		for (;;) {
			const char* pLeftNext;
			const char* pRight = Find<T_CharCmp>(pLeft, sub, &pLeftNext);
			if (!*pRight) break;
			strRtn.append(pLeft, pRight - pLeft);
			strRtn += replace;
			pLeft = pLeftNext;
		}
		strRtn += pLeft;
	}
	return strRtn;
}

template<typename T_CharCmp>
String String::Replace(const char* str, const char* sub, const char* replace, int nMaxReplace)
{
	String strRtn;
	if (*sub == '\0') {
		if (nMaxReplace != 0) {
			strRtn += replace;
			nMaxReplace--;
		}
		const char* p = str;
		for ( ; *p != '\0' && nMaxReplace != 0; p = Forward(p), nMaxReplace--) {
			strRtn += *p;
			strRtn += replace;
		}
		strRtn += p;
	} else {
		const char* pLeft = str;
		for ( ; nMaxReplace != 0; nMaxReplace--) {
			const char* pLeftNext;
			const char* pRight = Find<T_CharCmp>(pLeft, sub, &pLeftNext);
			if (!*pRight) break;
			strRtn.append(pLeft, pRight - pLeft);
			strRtn += replace;
			pLeft = pLeftNext;
		}
		strRtn += pLeft;
	}
	return strRtn;
}

template<typename T_CharCmp>
String String::ReplaceM(const char* str, const StringList& map)
{
	String strRtn;
	for (const char *p = str; *p; ) {
		const char* pNext = nullptr;
		for (auto pItem = map.begin(); pItem != map.end(); ) {
			const String& sub = *pItem++;
			if (pItem == map.end()) break;
			const String& replace = *pItem++;
			pNext = StartsWith<T_CharCmp>(p, sub.c_str());
			if (pNext) {
				strRtn += replace;
				break;
			}
		}
		if (pNext) {
			p = pNext;
		} else {
			strRtn += *p;
			p++;
		}
	}
	return strRtn;
}

template<typename T_CharCmp>
String String::ReplaceM(const char* str, const StringList& map, int nMaxReplace)
{
	if (nMaxReplace == 0) return str;
	String strRtn;
	for (const char *p = str; *p; ) {
		const char* pNext = nullptr;
		for (auto pItem = map.begin(); pItem != map.end(); ) {
			const String& sub = *pItem++;
			if (pItem == map.end()) break;
			const String& replace = *pItem++;
			pNext = StartsWith<T_CharCmp>(p, sub.c_str());
			if (pNext) {
				strRtn += replace;
				break;
			}
		}
		if (pNext) {
			p = pNext;
			nMaxReplace--;
			if (nMaxReplace == 0) {
				strRtn += p;
				break;
			}
		} else {
			strRtn += *p;
			p++;
		}
	}
	return strRtn;
}

}

#endif
