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
	enum class Type { None, Item, Container, BoundaryContainer, RootContainer, };
protected:
	RefPtr<WeakPtr> _pwDirectoryParent;
	String _pathName;
	Type _type;
	char _sep;
	bool _caseFlag;
public:
	// Constructor
	Directory(Directory* pDirectoryParent, String pathName, Type type, char sep, bool caseFlag) :
		_pwDirectoryParent(pDirectoryParent? pDirectoryParent->GetWeakPtr() : nullptr), _pathName(pathName),
		_type(type), _sep(sep), _caseFlag(caseFlag) {}
	// Copy constructor/operator
	Directory(const Directory& src) = delete;
	Directory& operator=(const Directory& src) = delete;
	// Move constructor/operator
	Directory(Directory&& src) = delete;
	Directory& operator=(Directory&& src) noexcept = delete;
protected:
	virtual ~Directory() = default;
public:
	static Directory* Open(const char* pathName, Type typeWouldBe = Type::None);
public:
	Directory* NextChild() { return DoNextChild(); }
	Directory* FindChild(const char* pathName) { return DoFindChild(pathName); }
	Stream* OpenStream(Stream::OpenFlags openFlags) { return DoOpenStream(openFlags); }
	Value* GetStatValue() { return DoGetStatValue(); }
	const char* GetPathName() const { return _pathName.c_str(); }
	Directory* LockDirectoryParent() const { return _pwDirectoryParent? _pwDirectoryParent->Lock() : nullptr; }
	char GetSep() const { return _sep; }
	bool IsCaseSensitive() const { return _caseFlag; }
	bool IsItem() const { return _type == Type::Item; }
	bool IsContainer() const {
		return _type == Type::Container || _type == Type::BoundaryContainer || _type == Type::RootContainer;
	}
	bool IsBoundaryContainer() const { return _type == Type::BoundaryContainer; }
	bool IsRootContainer() const { return _type == Type::RootContainer; }
	bool DoesMatch(const char* pathName) const {
		return PathName(GetPathName()).SetCaseFlag(_caseFlag).DoesMatchPattern(pathName);
	}
	bool DoesMatchPattern(const char* pattern) const {
		return PathName(GetPathName()).SetCaseFlag(_caseFlag).DoesMatchPattern(pattern);
	}
	String MakeFullPathName(bool addSepFlag, const char* pathNameTrail = nullptr) const;
	int CountDepth() const;
protected:
	virtual Directory* DoNextChild() = 0;
	virtual Directory* DoFindChild(const char* name) = 0;
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
public:
	Directory* FindByName(const char* name) const;
};

//------------------------------------------------------------------------------
// DirectoryOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DirectoryOwner : public DirectoryList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DirectoryOwner);
public:
	DirectoryOwner() {}
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
class GURAX_DLLDECLARE DirectoryDequeOwner : public DirectoryDeque, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DirectoryDequeOwner);
public:
	DirectoryDequeOwner() {}
	~DirectoryDequeOwner() { Clear(); }
	void Clear();
};

//------------------------------------------------------------------------------
// Directory_Container
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_Container : public Directory {
public:
	RefPtr<DirectoryOwner> _pDirectoryOwner;
	size_t _idx;
public:
	Directory_Container(Directory* pDirectoryParent, String pathName,
						Type type, char sep, bool caseFlag, DirectoryOwner* pDirectoryOwner) :
		Directory(pDirectoryParent, pathName, type, sep, caseFlag),
		_pDirectoryOwner(pDirectoryOwner), _idx(0) {}
	Directory_Container(Directory* pDirectoryParent, String pathName,
						Type type, char sep, bool caseFlag) :
		Directory_Container(pDirectoryParent, pathName, type, sep, caseFlag, new DirectoryOwner()) {}
public:
	DirectoryOwner& GetDirectoryOwner() { return *_pDirectoryOwner; }
protected:
	virtual Directory* DoNextChild() override;
	virtual Directory* DoFindChild(const char* name) override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
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

//------------------------------------------------------------------------------
// Iterator_DirectoryGlob
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DirectoryGlob : public Iterator {
private:
	DirectoryDequeOwner _directoryDeque;
	RefPtr<Directory> _pDirectoryCur;
	StringList _patternSegs;
	bool _addSepFlag;
	bool _statFlag;
	bool _caseFlag;
	bool _fileFlag;
	bool _dirFlag;
	size_t _depth;
	NumDeque<size_t> _depthDeque;
public:
	Iterator_DirectoryGlob(bool addSepFlag, bool statFlag,
						   bool caseFlag, bool fileFlag, bool dirFlag);
public:
	bool Init(const char* pattern);
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
