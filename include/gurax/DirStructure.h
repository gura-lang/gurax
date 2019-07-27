//==============================================================================
// DirStructure.h
//==============================================================================
#ifndef GURAX_DIRSTRUCTURE_H
#define GURAX_DIRSTRUCTURE_H

namespace Gurax {

//------------------------------------------------------------------------------
// DirStructure
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirStructure : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DirStructure);
public:
	// Constructor
	DirStructure() {}
	// Copy constructor/operator
	DirStructure(const DirStructure& src) = delete;
	DirStructure& operator=(const DirStructure& src) = delete;
	// Move constructor/operator
	DirStructure(DirStructure&& src) = delete;
	DirStructure& operator=(DirStructure&& src) noexcept = delete;
protected:
	~DirStructure() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DirStructure& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const DirStructure& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const DirStructure& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DirStructureList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirStructureList : public std::vector<DirStructure*> {
public:
	using std::vector<DirStructure*>::vector;
};

//------------------------------------------------------------------------------
// DirStructureOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirStructureOwner : public DirStructureList {
public:
	~DirStructureOwner() { Clear(); }
	void Clear();
};

}

#endif
