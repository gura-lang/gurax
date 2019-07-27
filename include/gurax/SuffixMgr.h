//==============================================================================
// SuffixMgr.h
//==============================================================================
#ifndef GURAX_SUFFIXMGR_H
#define GURAX_SUFFIXMGR_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// SuffixMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgr : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(SuffixMgr);
public:
	// Constructor
	SuffixMgr() {}
	// Copy constructor/operator
	SuffixMgr(const SuffixMgr& src) = delete;
	SuffixMgr& operator=(const SuffixMgr& src) = delete;
	// Move constructor/operator
	SuffixMgr(SuffixMgr&& src) = delete;
	SuffixMgr& operator=(SuffixMgr&& src) noexcept = delete;
protected:
	~SuffixMgr() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const SuffixMgr& suffixMgr) const { return this == &suffixMgr; }
	bool IsEqualTo(const SuffixMgr& suffixMgr) const { return IsIdentical(suffixMgr); }
	bool IsLessThan(const SuffixMgr& suffixMgr) const { return this < &suffixMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// SuffixMgrList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgrList : public std::vector<SuffixMgr*> {
public:
	using std::vector<SuffixMgr*>::vector;
};

//------------------------------------------------------------------------------
// SuffixMgrOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SuffixMgrOwner : public SuffixMgrList {
public:
	~SuffixMgrOwner() { Clear(); }
	void Clear();
};

}

#endif
