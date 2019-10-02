//==============================================================================
// Match.h
//==============================================================================
#ifndef GURAX_MODULE_RE_MATCH_H
#define GURAX_MODULE_RE_MATCH_H
#include <gurax.h>

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Match
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Match : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Match);
public:
	// Constructor
	Match() {}
	// Copy constructor/operator
	Match(const Match& src) = delete;
	Match& operator=(const Match& src) = delete;
	// Move constructor/operator
	Match(Match&& src) = delete;
	Match& operator=(Match&& src) noexcept = delete;
protected:
	virtual ~Match() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Match& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const Match& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const Match& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(re)

#endif
