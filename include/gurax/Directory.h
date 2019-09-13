//==============================================================================
// Directory.h
//==============================================================================
#ifndef GURAX_DIRECTORY_H
#define GURAX_DIRECTORY_H

namespace Gurax {

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Directory);
public:
	// Constructor
	Directory() {}
	// Copy constructor/operator
	Directory(const Directory& src) = delete;
	Directory& operator=(const Directory& src) = delete;
	// Move constructor/operator
	Directory(Directory&& src) = delete;
	Directory& operator=(Directory&& src) noexcept = delete;
protected:
	virtual ~Directory() = default;
public:
	Directory* NextChild() { return DoNextChild(); }
	Stream* OpenStream() { return DoOpenStream(); }
	Value* GetStatValue() { return DoGetStatValue(); }
protected:
	virtual Directory* DoNextChild() = 0;
	virtual Stream* DoOpenStream() = 0;
	virtual Value* DoGetStatValue();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Directory& pathMgr) const { return this == &pathMgr; }
	bool IsEqualTo(const Directory& pathMgr) const { return IsIdentical(pathMgr); }
	bool IsLessThan(const Directory& pathMgr) const { return this < &pathMgr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// DirectoryList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirectoryList : public std::vector<Directory*> {
public:
	using std::vector<Directory*>::vector;
};

//------------------------------------------------------------------------------
// DirectoryOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirectoryOwner : public DirectoryList {
public:
	~DirectoryOwner() { Clear(); }
	void Clear();
};

}

#endif
