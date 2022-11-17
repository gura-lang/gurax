//==============================================================================
// Match.h
//==============================================================================
#ifndef GURAX_MODULE_RE_MATCH_H
#define GURAX_MODULE_RE_MATCH_H
#include <gurax.h>
#include "Pattern.h"

Gurax_BeginModuleScope(re)

class Group;

//------------------------------------------------------------------------------
// Match
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Match : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Match);
private:
	RefPtr<Pattern> _pPattern;
	OnigRegion* _region;
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	Match(Pattern* pPattern, OnigRegion* region, StringReferable* pStr);
	Match(Pattern* pPattern, OnigRegion* region, String str);
	// Copy constructor/operator
	Match(const Match& src) = delete;
	Match& operator=(const Match& src) = delete;
	// Move constructor/operator
	Match(Match&& src) = delete;
	Match& operator=(Match&& src) noexcept = delete;
protected:
	virtual ~Match();
public:
	Pattern& GetPattern() { return *_pPattern; }
	const StringReferable& GetSourceStringReferable() const { return *_pStr; }
	const String& GetSourceStringSTL() const { return _pStr->GetStringSTL(); }
	const char* GetSourceString() const { return _pStr->GetString(); }
	int CountGroups() const { return _region->num_regs; }
	Group* CreateGroup(int iGroup) const;
	int LookupGroupNum(const char* name) const;
	int GetPosBegin() const { return _region->beg[0]; }
	int GetPosEnd() const { return _region->end[0]; }
	String GetString() const;
	String GetGroupString(int iGroup) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Match& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const Match& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const Match& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(re)

#endif
