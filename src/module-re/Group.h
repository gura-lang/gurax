//==============================================================================
// Group.h
//==============================================================================
#ifndef GURAX_MODULE_RE_GROUP_H
#define GURAX_MODULE_RE_GROUP_H
#include <gurax.h>

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Group
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Group : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Group);
public:
	// Constructor
	Group() {}
	// Copy constructor/operator
	Group(const Group& src) = delete;
	Group& operator=(const Group& src) = delete;
	// Move constructor/operator
	Group(Group&& src) = delete;
	Group& operator=(Group&& src) noexcept = delete;
protected:
	virtual ~Group() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Group& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const Group& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const Group& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(re)

#endif
