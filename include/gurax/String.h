//==============================================================================
// String.h
//==============================================================================
#ifndef GURAX_STRING_H
#define GURAX_STRING_H
#include "Referable.h"
#include "ListBase.h"

namespace Gurax {

class StringList;
class Value;
class ValueList;

//------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE String : public std::string {
public:
	// Algorithm operators
	struct GURAX_DLLDECLARE EqualTo {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsEqualTo(str2);
		}
	};
	struct GURAX_DLLDECLARE EqualToICase {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsEqualToICase(str2);
		}
	};
	struct GURAX_DLLDECLARE LessThan {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsLessThan(str2);
		}
	};
	struct GURAX_DLLDECLARE LessThanICase {
		bool operator()(const String& str1, const String& str2) const {
			return str1.IsLessThanICase(str2);
		}
	};
	struct GURAX_DLLDECLARE GreaterThan {
		bool operator()(const String& str1, const String& str2) const {
			return str2.IsLessThan(str1);
		}
	};
	struct GURAX_DLLDECLARE GreaterThanICase {
		bool operator()(const String& str1, const String& str2) const {
			return str2.IsLessThanICase(str1);
		}
	};
	struct GURAX_DLLDECLARE Hash {
		size_t operator()(const String& str) const {
			return str.CalcHash();
		}
	};
	class GURAX_DLLDECLARE CharSeq : public Gurax::CharSeq {
	private:
		const char* _p;
	public:
		CharSeq(const char* str) : _p(str) {}
		CharSeq(const String& str) : _p(str.c_str()) {}
	public:
		virtual char GetChar() override { return *_p? *_p++ : '\0'; }
	};
public:
	using CTypes = UInt32;
	struct GURAX_DLLDECLARE CType {
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
	String() {}
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
	static size_t CalcCharOffset(const char* str, size_t pos) { return Forward(str, pos) - str; }
	size_t CalcCharOffset(size_t pos) const { return CalcCharOffset(c_str(), pos); }
public:
	String& AppendNTimes(const char* str, size_t n);
	String& AppendNChars(const char* str, size_t len);
	String& AppendUTF8(UInt64 codeUTF8);
	String& AppendUTF32(UInt32 codeUTF32);
	static void UTF32ToUTF8(UInt32 codeUTF32, char buff[], size_t *pCnt);
	static void UTF32ToUTF8_Unsorted(UInt32 codeUTF32, char buff[], size_t *pCnt);
public:
	String& FormatV(const char* format, va_list ap);
	String& Format(const char* format, ...);
	String& FormatValue(const char* format, const Value& value);
	String& FormatValueList(const char* format, const ValueList& valueList);
public:
	static char DetermineQuote(const char* str);
	char DetermineQuote() const { return DetermineQuote(c_str()); }
	static String Enquote(const char* str, char chQuote = '\'');
	String Enquote(char chQuote = '\'') const { return Enquote(c_str(), chQuote); }
	static String EnquoteAuto(const char* str) { return Enquote(str, DetermineQuote(str)); }
	String EnquoteAuto() const { return EnquoteAuto(c_str()); }
public:
	static String EncodeURI(const char* str);
	String EncodeURI() const { return EncodeURI(c_str()); }
	static String DecodeURI(const char* str);
	String DecodeURI() const { return DecodeURI(c_str()); }
public:
	static String EscapeHTML(const char* str, bool quoteFlag);
	String EscapeHTML(bool quoteFlag) const { return EscapeHTML(c_str(), quoteFlag); }
	static String UnescapeHTML(const char* str);
	String UnescapeHTML() const { return UnescapeHTML(c_str()); }
public:
	static Double ToDouble(const char* str, bool* pSuccessFlag = nullptr);
	Double ToDouble(bool* pSuccessFlag = nullptr) const { return ToDouble(c_str(), pSuccessFlag); }
	static Int64 ToInt64(const char* str, bool* pSuccessFlag = nullptr);
	Double ToInt64(bool* pSuccessFlag = nullptr) const { return ToInt64(c_str(), pSuccessFlag); }
public:
	static size_t CalcHash(const char* str);
	static size_t CalcHash(const char* str, size_t len);
	size_t CalcHash() const { return CalcHash(c_str(), size()); }
	static int Compare(const char* str1, const char* str2)				{ return ::strcmp(str1, str2); }
	int Compare(const char* str) const									{ return Compare(c_str(), str); }
	int Compare(const String& str) const								{ return Compare(c_str(), str.c_str()); }
	static int CompareICase(const char* str1, const char* str2)			{ return ::strcasecmp(str1, str2); }
	int CompareICase(const char* str) const								{ return CompareICase(c_str(), str); }
	int CompareICase(const String& str) const							{ return CompareICase(c_str(), str.c_str()); }
	static bool IsEqualTo(const char* str1, const char* str2)			{ return Compare(str1, str2) == 0; }
	bool IsEqualTo(const char* str) const								{ return IsEqualTo(c_str(), str); }
	bool IsEqualTo(const String& str) const								{ return IsEqualTo(c_str(), str.c_str()); }
	static bool IsEqualToICase(const char* str1, const char* str2)		{ return CompareICase(str1, str2) == 0; }
	bool IsEqualToICase(const char* str) const							{ return IsEqualToICase(c_str(), str); }
	bool IsEqualToICase(const String& str) const						{ return IsEqualToICase(c_str(), str.c_str()); }
	static bool IsLessThan(const char* str1, const char* str2)			{ return Compare(str1, str2) < 0; }
	bool IsLessThan(const char* str) const								{ return IsLessThan(c_str(), str); }
	bool IsLessThan(const String& str) const							{ return IsLessThan(c_str(), str.c_str()); }
	static bool IsLessThanICase(const char* str1, const char* str2)		{ return CompareICase(str1, str2) < 0; }
	bool IsLessThanICase(const char* str) const							{ return IsLessThanICase(c_str(), str); }
	bool IsLessThanICase(const String& str) const						{ return IsLessThanICase(c_str(), str.c_str()); }
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
	static bool EndsWith(const char* str, char ch);
	bool EndsWith(char ch) const;
	static bool EndsWithPathSep(const char* str);
	bool EndsWithPathSep() const;
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
	String Repeat(size_t n) const { return Repeat(c_str(), n); }
	static String Repeat(const char* str, size_t n);
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

struct GURAX_DLLDECLARE CharCase {
	int operator()(char ch1, char ch2) const {
		return static_cast<int>(ch1) - ch2;
	}
};

struct GURAX_DLLDECLARE CharICase {
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
class GURAX_DLLDECLARE StringList : public ListBase<String> {
public:
	static const StringList Empty;
public:
	StringList& Sort() { std::sort(begin(), end()); return *this; }
	StringList& Sort(SortOrder sortOrder);
	StringList& Unique() { erase(std::unique(begin(), end()), end()); return *this; }
};

//------------------------------------------------------------------------------
// StringSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringSet {
public:
	using SetType = std::unordered_set<String, String::Hash, String::EqualTo>;
private:
	SetType _set;
public:
	static const StringSet Empty;
	SetType& GetSet() { return _set; }
};

//------------------------------------------------------------------------------
// StringReferable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringReferable : public Referable {
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
	const char* GetString() const { return _str.c_str(); }
	String& GetStringSTL() { return _str; }
	const String& GetStringSTL() const { return _str; }
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
