//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_PATHMGR_H
#define GURAX_PATHMGR_H

namespace Gurax {

//------------------------------------------------------------------------------
// PathMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PathMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PathMgr);
public:
	// Constructor
	PathMgr() {}
	// Copy constructor/operator
	PathMgr(const PathMgr& src) = delete;
	PathMgr& operator=(const PathMgr& src) = delete;
	// Move constructor/operator
	PathMgr(PathMgr&& src) = delete;
	PathMgr& operator=(PathMgr&& src) noexcept = delete;
protected:
	~PathMgr() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PathMgr& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const PathMgr& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const PathMgr& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PathMgrList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PathMgrList : public std::vector<PathMgr*> {
public:
	using std::vector<PathMgr*>::vector;
};

//------------------------------------------------------------------------------
// PathMgrOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PathMgrOwner : public PathMgrList {
public:
	~PathMgrOwner() { Clear(); }
	void Clear();
};

}

#endif
