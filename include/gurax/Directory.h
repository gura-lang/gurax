//==============================================================================
// Directory.h
//==============================================================================
#ifndef GURAX_DIRECTORY_H
#define GURAX_DIRECTORY_H
#include "PathName.h"
#include "Stream.h"

namespace Gurax {

class Directory_CustomContainer;

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Directory);
public:
	enum class Type { None, Item, Container, Boundary, Root, };
	class SymbolAssoc_Type : public SymbolAssoc<Type, Type::None> {
	public:
		SymbolAssoc_Type() {
			Assoc(Gurax_Symbol(item),		Type::Item);
			Assoc(Gurax_Symbol(container),	Type::Container);
			Assoc(Gurax_Symbol(boundary),	Type::Boundary);
			Assoc(Gurax_Symbol(root),		Type::Root);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Type());
		}
	};
public:
	class Factory;
	class GURAX_DLLDECLARE FactoryList : public std::vector<Factory*> {
	public:
		Factory* FindByName(const char* name) const;
		iterator FindIteratorByName(const char* name);
	};
	class GURAX_DLLDECLARE FactoryOwner : public FactoryList, public Referable {
	public:
		Gurax_DeclareReferable(FactoryOwner);
	protected:
		~FactoryOwner() { Clear(); }
	public:
		void Clear();
	};
	class GURAX_DLLDECLARE Factory : public Referable {
	public:
		Gurax_DeclareReferable(Factory);
	protected:
		String _name;
		RefPtr<FactoryOwner> _pFactoryOwner;
		bool _caseFlag;
	public:
		Factory(FactoryOwner* pFactoryOwner, bool caseFlag) :
			_pFactoryOwner(pFactoryOwner), _caseFlag(caseFlag) {}
		Factory(String name, FactoryOwner* pFactoryOwner, bool caseFlag) :
			_name(name), _pFactoryOwner(pFactoryOwner), _caseFlag(caseFlag) {}
	protected:
		virtual ~Factory() = default;
	public:
		void SetName(String name) { _name = name; }
		void SetFactoryOwner(FactoryOwner* pFactoryOwner) { _pFactoryOwner.reset(pFactoryOwner); }
		FactoryOwner& GetFactoryOwner() { return *_pFactoryOwner; }
		const FactoryOwner& GetFactoryOwner() const { return *_pFactoryOwner; }
		bool GetCaseFlag() const { return _caseFlag; }
		bool AddChildInTree(const char* pathName, RefPtr<Factory> pFactoryChild);
		bool DoesMatch(const char* name) {
			return PathName(_name).SetCaseFlag(_caseFlag).DoesMatch(name);
		}
	public:
		virtual Directory* GenerateDirectory() { return nullptr; }
	};
protected:
	String _name;
	Type _type;
	char _sep;
	bool _caseFlag;
	RefPtr<Directory> _pDirectoryParent;
public:
	// Constructor
	Directory(Type type, char sep, bool caseFlag) : _type(type), _sep(sep), _caseFlag(caseFlag) {}
	Directory(String name, Type type, char sep, bool caseFlag) :
		_name(name), _type(type), _sep(sep), _caseFlag(caseFlag) {}
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
	void SetName(String name) { _name = name; }
	void RewindChild() { return DoRewindChild(); }
	Directory* NextChild() { return DoNextChild(); }
	Stream* OpenStream(Stream::OpenFlags openFlags) { return DoOpenStream(openFlags); }
	Value* CreateStatValue() { return DoCreateStatValue(); }
	const char* GetName() const { return _name.c_str(); }
	char GetSep() const { return _sep; }
	bool IsCaseSensitive() const { return _caseFlag; }
	Type GetType() const { return _type; }
	bool IsItem() const { return _type == Type::Item; }
	bool IsContainer() const { return _type == Type::Container; }
	bool IsBoundary() const { return _type == Type::Boundary; }
	bool IsRoot() const { return _type == Type::Root; }
	bool IsLikeContainer() const {
		return _type == Type::Container || _type == Type::Boundary || _type == Type::Root;
	}
	void SetDirectoryParent(Directory* pDirectoryParent) { _pDirectoryParent.reset(pDirectoryParent); }
	const Directory* GetDirectoryParent() const { return _pDirectoryParent.get(); }
	bool DoesMatch(const char* name) const {
		return PathName(GetName()).SetCaseFlag(_caseFlag).DoesMatchPattern(name);
	}
	bool DoesMatchPattern(const char* pattern) const {
		return PathName(GetName()).SetCaseFlag(_caseFlag).DoesMatchPattern(pattern);
	}
	String MakeFullPathName(bool addSepFlag, const char* pathNameTrail = nullptr) const;
	int CountDepth() const;
	Directory* SearchByName(const char* name);
	Directory* SearchInTree(const char** pPathName);
public:
	virtual Directory_CustomContainer* CreateEmptyCustomContainer(String name) { return nullptr; }
	virtual bool IsCustomContainer() const { return false; }
protected:
	virtual void DoRewindChild() {}
	virtual Directory* DoNextChild() { return nullptr; }
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) { return nullptr; }
	virtual Value* DoCreateStatValue();
public:
	static Type SymbolToType(const Symbol* pSymbol) {
		return SymbolAssoc_Type::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* TypeToSymbol(Type type) {
		return SymbolAssoc_Type::GetInstance().ToSymbol(type);
	}
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
	iterator FindIteratorByName(const char* name);
	const_iterator FindIteratorByName(const char* name) const;
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

#if 0
//------------------------------------------------------------------------------
// Directory_CustomContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_CustomContainer : public Directory {
public:
	RefPtr<DirectoryOwner> _pDirectoryOwner;
	size_t _idxChild;
	RefPtr<WeakPtr> _pwDirectoryParent;
public:
	Directory_CustomContainer(Type type, char sep, bool caseFlag) :
		Directory(type, sep, caseFlag), _pDirectoryOwner(new DirectoryOwner()), _idxChild(0) {}
	Directory_CustomContainer(String name, Type type, char sep, bool caseFlag) :
		Directory(name, type, sep, caseFlag), _pDirectoryOwner(new DirectoryOwner()), _idxChild(0) {}
public:
	DirectoryOwner& GetDirectoryOwner() { return *_pDirectoryOwner; }
	const DirectoryOwner& GetDirectoryOwner() const { return *_pDirectoryOwner; }
	void SetDirectoryOwner(DirectoryOwner* pDirectoryOwner) { _pDirectoryOwner.reset(pDirectoryOwner); }
	bool AddChildInTree(const char* pathName, RefPtr<Directory> pDirectoryChild);
	virtual bool IsCustomContainer() const override { return true; }
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
};
#endif

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
