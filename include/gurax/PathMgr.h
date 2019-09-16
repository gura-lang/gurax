//==============================================================================
// PathMgr.h
//==============================================================================
#ifndef GURAX_PATHMGR_H
#define GURAX_PATHMGR_H
#include "Directory.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PathMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PathMgr);
public:
	enum NotFoundMode { Signal, NoSignal, Wouldbe, };
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
	virtual ~PathMgr() = default;
public:
	static PathMgr* FindResponsible(const char* pathName);
	Directory* OpenDirectory(const char* pathName) {
		return DoOpenDirectory(nullptr, &pathName, NotFoundMode::Signal);
	}
	virtual bool IsResponsible(Directory* pDirectoryParent, const char* pathName) = 0;
protected:
	virtual Directory* DoOpenDirectory(Directory* pDirectoryParent,
									   const char** pPathName, NotFoundMode notFoundMode) = 0;
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
public:
	PathMgr* FindResponsible(Directory* pDirectoryParent, const char* pathName) const;
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
