//==============================================================================
// Directory.h
//==============================================================================
#ifndef GURAX_DIRECTORY_H
#define GURAX_DIRECTORY_H
#include "PathName.h"
#include "Stream.h"

namespace Gurax {

class Value_Stat;

//------------------------------------------------------------------------------
// Directory
//
// +-----------+ parent       +-----------+
// | Directory |--------------* Directory |
// +-----------+        child +-----*-----+
//                                  |
//                          +-----------------+ 1   +-----------------+
//                          | Directory::Core *-----| Directory::Core |
//                          +-----------------+   n +-----------------+
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Directory);
public:
	using WalkFlags = UInt32;
	struct GURAX_DLLDECLARE WalkFlag {
		static const WalkFlags AddSep	= (1 << 0);
		static const WalkFlags Stat		= (1 << 1);
		static const WalkFlags Case		= (1 << 2);
		static const WalkFlags File		= (1 << 3);
		static const WalkFlags Dir		= (1 << 4);
		static bool IsAddSep(WalkFlags walkFlags) { return (walkFlags & AddSep)? true : false; }
		static bool IsStat(WalkFlags walkFlags) { return (walkFlags & Stat)? true : false; }
		static bool IsCase(WalkFlags walkFlags) { return (walkFlags & Case)? true : false; }
		static bool IsFile(WalkFlags walkFlags) { return (walkFlags & File)? true : false; }
		static bool IsDir(WalkFlags walkFlags) { return (walkFlags & Dir)? true : false; }
		static String ToString(WalkFlags walkFlags);
		static void DeclareAttrOpt(Function& func);
		static WalkFlags CheckArgument(const Argument& argument, bool addSepFlagDefault, bool caseFlagDefault);
	};
public:
	enum class Type { None, Item, Folder, Boundary, };
	class SymbolAssoc_Type : public SymbolAssoc<Type, Type::None> {
	public:
		SymbolAssoc_Type() {
			Assoc(Gurax_Symbol(item),		Type::Item);
			Assoc(Gurax_Symbol(container),	Type::Folder);
			Assoc(Gurax_Symbol(boundary),	Type::Boundary);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Type());
		}
	};
public:
	class Core;
	class GURAX_DLLDECLARE CoreList : public ListBase<Core*> {
	public:
		Core* FindByName(const char* name) const;
		iterator FindIteratorByName(const char* name);
	};
	class GURAX_DLLDECLARE CoreOwner : public CoreList, public Referable {
	public:
		Gurax_DeclareReferable(CoreOwner);
	public:
		static RefPtr<CoreOwner> Empty;
	protected:
		~CoreOwner() { Clear(); }
	public:
		void Clear();
	};
	class GURAX_DLLDECLARE Core : public Referable {
	public:
		Gurax_DeclareReferable(Core);
	protected:
		Type _type;
		String _name;
		char _sep;
		bool _caseFlag;
		RefPtr<CoreOwner> _pCoreOwner;
	public:
		Core(Type type, char sep, bool caseFlag, CoreOwner* pCoreOwner) :
			_type(type), _sep(sep), _caseFlag(caseFlag), _pCoreOwner(pCoreOwner) {}
		Core(Type type, String name, char sep, bool caseFlag, CoreOwner* pCoreOwner) :
			_type(type), _name(name), _sep(sep), _caseFlag(caseFlag), _pCoreOwner(pCoreOwner) {}
	protected:
		virtual ~Core() = default;
	public:
		Type GetType() const { return _type; }
		void SetName(String name) { _name = name; }
		const char* GetName() const { return _name.c_str(); }
		void SetCoreOwner(CoreOwner* pCoreOwner) { _pCoreOwner.reset(pCoreOwner); }
		CoreOwner& GetCoreOwner() { return *_pCoreOwner; }
		const CoreOwner& GetCoreOwner() const { return *_pCoreOwner; }
		char GetSep() const { return _sep; }
		bool GetCaseFlag() const { return _caseFlag; }
		bool AddChildInTree(const char* pathName, RefPtr<Core> pCoreChild);
		bool DoesMatch(const char* name) {
			return PathName(_name).SetCaseFlag(GetCaseFlag()).DoesMatch(name);
		}
		void Print(Stream& stream, int indentLevel = 0) const;
	public:
		virtual Directory* GenerateDirectory() { return new Directory(Reference()); }
	};
protected:
	RefPtr<Core> _pCore;
	RefPtr<Directory> _pDirectoryParent;
public:
	static void Bootup();
public:
	// Constructor
	Directory(Core* pCore) : _pCore(pCore) {}
	Directory(Type type, char sep, bool caseFlag) :
		Directory(new Core(type, sep, caseFlag, CoreOwner::Empty->Reference())) {}
	Directory(Type type, String name, char sep, bool caseFlag) :
		Directory(new Core(type, name, sep, caseFlag, CoreOwner::Empty->Reference())) {}
	// Copy constructor/operator
	Directory(const Directory& src) = delete;
	Directory& operator=(const Directory& src) = delete;
	// Move constructor/operator
	Directory(Directory&& src) = delete;
	Directory& operator=(Directory&& src) noexcept = delete;
protected:
	virtual ~Directory() = default;
public:
	void SetName(String name) { _pCore->SetName(name); }
	void RewindChild() { return DoRewindChild(); }
	Directory* NextChild() { return DoNextChild(); }
	Stream* OpenStream(Stream::OpenFlags openFlags) { return DoOpenStream(openFlags); }
	Value_Stat* CreateStatValue() { return DoCreateStatValue(); }
	const char* GetName() const { return _pCore->GetName(); }
	char GetSep() const { return _pCore->GetSep(); }
	bool GetCaseFlag() const { return _pCore->GetCaseFlag(); }
	Type GetType() const { return _pCore->GetType(); }
	bool IsItem() const { return GetType() == Type::Item; }
	bool IsFolder() const { return GetType() == Type::Folder; }
	bool IsBoundary() const { return GetType() == Type::Boundary; }
	bool IsLikeFolder() const {
		return GetType() == Type::Folder || GetType() == Type::Boundary;
	}
	void SetDirectoryParent(Directory* pDirectoryParent) { _pDirectoryParent.reset(pDirectoryParent); }
	const Directory* GetDirectoryParent() const { return _pDirectoryParent.get(); }
	bool DoesMatch(const char* name) const {
		return PathName(GetName()).SetCaseFlag(GetCaseFlag()).DoesMatchPattern(name);
	}
	bool DoesMatchPattern(const char* pattern) const {
		return PathName(GetName()).SetCaseFlag(GetCaseFlag()).DoesMatchPattern(pattern);
	}
	String MakeFullPathName(bool addSepFlag, const char* pathNameTrail = nullptr) const;
	int CountDepth() const;
	Directory* SearchByName(const char* name);
	Directory* SearchInTree(const char** pPathName);
protected:
	virtual void DoRewindChild() {}
	virtual Directory* DoNextChild() { return nullptr; }
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) { return nullptr; }
	virtual Value_Stat* DoCreateStatValue();
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
class GURAX_DLLDECLARE DirectoryList : public ListBase<Directory*> {
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

//------------------------------------------------------------------------------
// Iterator_DirectoryWalk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DirectoryWalk : public Iterator {
private:
	DirectoryDequeOwner _directoryDeque;
	RefPtr<Directory> _pDirectoryCur;
	int _depthMax;
	StringList _patterns;
	Directory::WalkFlags _walkFlags;
	//bool _addSepFlag;
	//bool _statFlag;
	//bool _caseFlag;
	//bool _fileFlag;
	//bool _dirFlag;
public:
	Iterator_DirectoryWalk(Directory* pDirectory, int depthMax, const StringList& patterns, Directory::WalkFlags walkFlags);
	//	bool addSepFlag, bool statFlag, bool caseFlag, bool fileFlag, bool dirFlag);
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
	Directory::WalkFlags _walkFlags;
	size_t _depth;
	NumDeque<size_t> _depthDeque;
public:
	Iterator_DirectoryGlob();
public:
	bool Initialize(const char* pattern);
	Directory& GetDirectoryCur() { return *_pDirectoryCur; }
	void SetWalkFlags(Directory::WalkFlags walkFlags) { _walkFlags = walkFlags; }
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
	// Virtual functions of Iterator_DirectoryGlob
	virtual Directory* OpenDirectory(const char* pathName);
};

}

#endif
