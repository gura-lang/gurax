//==============================================================================
// PathName.h
//==============================================================================
#ifndef GURAX_PATHNAME_H
#define GURAX_PATHNAME_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathName
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PathName {
public:
	static const char SepMSWIN	= '\\';
	static const char SepUNIX	= '/';
	static const char SepPlatform;
	static const bool CaseFlagDefault;
private:
	const char* _pathName;
	char _sep;
	bool _caseFlag;
public:
	// Constructor
	PathName() = delete;
	PathName(const char* pathName) :
		_pathName(pathName), _sep(SepPlatform), _caseFlag(CaseFlagDefault) {}
	PathName(const String& pathName) : PathName(pathName.c_str()) {}
	// Copy constructor/operator
	PathName(const PathName& src) = delete;
	PathName& operator=(const PathName& src) = delete;
	// Move constructor/operator
	PathName(PathName&& src) = delete;
	PathName& operator=(PathName&& src) noexcept = delete;
	// Destructor
	virtual ~PathName() = default;
public:
	PathName& SetSepMSWIN() { _sep = SepMSWIN; return *this; }
	PathName& SetSepUNIX() { _sep = SepUNIX; return *this; }
	PathName& SetCaseFlag(bool caseFlag) { _caseFlag = caseFlag; return *this; }
	PathName& Case() { _caseFlag = true; return *this; }
	PathName& ICase() { _caseFlag = false; return *this; }
	char GetSep() const { return _sep; }
	bool GetCaseFlag() const { return _caseFlag; }
public:
	String Regulate() const;
	String JoinBefore(const char* pathName) const;
	String JoinAfter(const char* pathName) const;
	void SplitFileName(String* pDirName, String* pFileName) const;
	void SplitBottomName(String* pHeadName, String* pBottomName) const;
	void SplitExtName(String* pBaseName, String* pExtName) const;
	bool HasWildCard() const;
	bool HasSeparator() const;
	const char* SeekFileName() const;
	const char* SeekExtName() const;
	const char* SeekTerminator() const { return _pathName + ::strlen(_pathName); }
	template<typename T_CharCmp>
	static bool DoesMatchSub(const char* pattern, const char* pathName);
	bool DoesMatch(const char* pattern) const;
	String MakeAbsPathName() const;
	bool IsAbsPathName() const;
public:
	static bool IsSep(char ch) { return ch == SepMSWIN || ch == SepUNIX; }
	static bool IsSepEx(char ch) { return IsSep(ch) || ch == ':'; }
	static bool IsWildCardChar(char ch) {
		return ch == '*' || ch == '?' || ch == '[' || ch == ']';
	}
};

}

#endif
