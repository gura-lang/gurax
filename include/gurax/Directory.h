//==============================================================================
// Directory.h
//==============================================================================
#ifndef GURAX_DIRECTORY_H
#define GURAX_DIRECTORY_H
#include "PathName.h"
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Directory);
public:
	enum class OpenMode { Signal, NoSignal, WouldBe, };
	enum class Type { None, Item, Container, BoundaryContainer, RootContainer, };
protected:
	RefPtr<Directory> _pDirectoryParent;
	String _name;
	Type _type;
	char _sep;
	bool _caseFlag;
public:
	// Constructor
	Directory(Directory* pDirectoryParent, String name, Type type, char sep, bool caseFlag) :
		_pDirectoryParent(pDirectoryParent), _name(name), _type(type), _sep(sep), _caseFlag(caseFlag) {}
	// Copy constructor/operator
	Directory(const Directory& src) = delete;
	Directory& operator=(const Directory& src) = delete;
	// Move constructor/operator
	Directory(Directory&& src) = delete;
	Directory& operator=(Directory&& src) noexcept = delete;
protected:
	virtual ~Directory() = default;
public:
	static Directory* Open(const char* pathName, OpenMode openMode);
public:
	Directory* NextChild() { return DoNextChild(); }
	Stream* OpenStream(Stream::OpenFlags openFlags) { return DoOpenStream(openFlags); }
	Value* GetStatValue() { return DoGetStatValue(); }
	const char *GetName() const { return _name.c_str(); }
	Directory* GetDirectoryParent() const { return _pDirectoryParent.get(); }
	char GetSep() const { return _sep; }
	bool IsCaseSensitive() const { return _caseFlag; }
	bool IsItem() const { return _type == Type::Item; }
	bool IsContainer() const {
		return _type == Type::Container || _type == Type::BoundaryContainer || _type == Type::RootContainer;
	}
	bool IsBoundaryContainer() const { return _type == Type::BoundaryContainer; }
	bool IsRootContainer() const { return _type == Type::BoundaryContainer; }
	bool DoesMatch(const char* pattern, bool caseFlag) const {
		return PathName(GetName()).SetCaseFlag(caseFlag).DoesMatch(pattern);
	}
	String MakePathName(bool addSepFlag, const char* pathNameTrail = nullptr) const;
	int CountDepth() const;
protected:
	virtual Directory* DoNextChild() = 0;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) = 0;
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

//-----------------------------------------------------------------------------
// DirectoryDeque
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE DirectoryDeque : public std::deque<Directory*> {
};

//-----------------------------------------------------------------------------
// DirectoryDequeOwner
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE DirectoryDequeOwner : public DirectoryDeque {
public:
	~DirectoryDequeOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Iterator_DirectoryWalk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DirectoryWalk : public Iterator {
private:
	DirectoryDequeOwner _directoryDeque;
	RefPtr<Directory> _pDirectoryCur;
	int _depthMax;
	StringList _patterns;
	bool _addSepFlag;
	bool _statFlag;
	bool _caseFlag;
	bool _fileFlag;
	bool _dirFlag;
public:
	Iterator_DirectoryWalk(
		Directory* pDirectory, int depthMax, const StringList& patterns,
		bool addSepFlag, bool statFlag, bool caseFlag, bool fileFlag, bool dirFlag);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
