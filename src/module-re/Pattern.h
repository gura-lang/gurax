//==============================================================================
// Pattern.h
//==============================================================================
#ifndef GURAX_MODULE_RE_PATTERN_H
#define GURAX_MODULE_RE_PATTERN_H
#include <gurax.h>

Gurax_BeginModuleScope(re)

class Match;

//------------------------------------------------------------------------------
// Pattern
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pattern : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pattern);
private:
	OnigRegex _regex;
public:
	// Constructor
	Pattern();
	// Copy constructor/operator
	Pattern(const Pattern& src) = delete;
	Pattern& operator=(const Pattern& src) = delete;
	// Move constructor/operator
	Pattern(Pattern&& src) = delete;
	Pattern& operator=(Pattern&& src) noexcept = delete;
protected:
	virtual ~Pattern();
public:
	OnigRegex GetRegex() { return _regex; }
	bool Prepare(const char* pattern, bool icaseFlag, bool multiLineFlag);
	Match* CreateMatch(const char* str, int pos = 0, int posEnd = -1);
	String ReplaceByString(const char* str, const char* replace, int cnt, int& nReplaced);
	String ReplaceByFunction(const char* str, Processor& processor, const Function& func, int cnt, int& nReplaced);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pattern& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const Pattern& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const Pattern& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(re)

#endif
