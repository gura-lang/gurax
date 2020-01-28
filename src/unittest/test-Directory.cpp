//==============================================================================
// test-Directory.cpp
//==============================================================================
#include "stdafx.h"

#define ArraySizeOf(x) (sizeof(x) / sizeof(x[0]))

namespace Gurax {

//------------------------------------------------------------------------------
// Directory_CustomContainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_CustomContainer : public Directory {
public:
	class Factory : public Referable {
	public:
		Gurax_DeclareReferable(Factory);
	protected:
		String _name;
	public:
		Factory(String name) : _name(name) {}
	protected:
		virtual ~Factory() = default;
	public:
		virtual Directory* CreateDirectory() const = 0;
	};
	class FactoryList : public std::vector<Factory*> {};
	class FactoryOwner : public FactoryList {
	public:
		~FactoryOwner() { Clear(); }
		void Clear() {
			for (Factory* pFactory : *this) Factory::Delete(pFactory);
			clear();
		}
	};
public:
	FactoryOwner _factoryOwner;
	size_t _idxChild;
public:
	Directory_CustomContainer(Type type, char sep, bool caseFlag) :
		Directory(type, sep, caseFlag), _idxChild(0) {}
	Directory_CustomContainer(String name, Type type, char sep, bool caseFlag) :
		Directory(name, type, sep, caseFlag), _idxChild(0) {}
public:
	bool AddChildInTree(const char* pathName, RefPtr<Factory> pFactoryChild);
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
};

//------------------------------------------------------------------------------
// Directory_CustomContainer
//------------------------------------------------------------------------------
bool Directory_CustomContainer::AddChildInTree(const char* pathName, RefPtr<Factory> pDirectoryChild)
{
#if 0
	String driveLetter;
	String prefix;
	StringList fields;
	PathName(pathName).SplitIntoFields(&driveLetter, &prefix, fields);
	Directory_CustomContainer* pDirectoryParent = this;
	auto pField = fields.begin();
	if (pField == fields.end()) {
		Error::Issue(ErrorType::PathError, "invalid path name");
		return false;
	}
	for ( ; pField + 1 != fields.end() && !(pField + 1)->empty(); pField++) {
		const String& field = *pField;
		DirectoryOwner& directoryOwner = pDirectoryParent->GetDirectoryOwner();
		Directory* pDirectory = directoryOwner.FindByName(field.c_str());
		if (!pDirectory) {
			auto pDirectoryNew = new Directory_CustomContainer(
				field, Type::Container, pDirectoryParent->GetSep(), pDirectoryParent->IsCaseSensitive());
			pDirectoryNew->SetDirectoryParent(*pDirectoryParent);
			directoryOwner.push_back(pDirectoryNew);
			pDirectoryParent = pDirectoryNew;
		} else if (!pDirectory->IsCustomContainer()) {
			Error::Issue(ErrorType::PathError, "invalid path name");
			return false;
		} else {
			pDirectoryParent = dynamic_cast<Directory_CustomContainer*>(pDirectory);
		}
	}
	const String& field = *pField;
	DirectoryOwner& directoryOwner = pDirectoryParent->GetDirectoryOwner();
	pDirectoryChild->SetDirectoryParent(*pDirectoryParent);
	pDirectoryChild->SetName(field);
	auto ppDirectoryFound = directoryOwner.FindIteratorByName(field.c_str());
	if (ppDirectoryFound == directoryOwner.end()) {
		directoryOwner.push_back(pDirectoryChild.release());
	} else {
		if (pDirectoryChild->IsCustomContainer() && (*ppDirectoryFound)->IsCustomContainer()) {
			dynamic_cast<Directory_CustomContainer&>(*pDirectoryChild).SetDirectoryOwner(
				dynamic_cast<Directory_CustomContainer*>(*ppDirectoryFound)->GetDirectoryOwner().Reference());
		}
		Directory::Delete(*ppDirectoryFound);
		*ppDirectoryFound = pDirectoryChild.release();
	}
#endif
	return true;
}

void Directory_CustomContainer::DoRewindChild()
{
	_idxChild = 0;
}

Directory* Directory_CustomContainer::DoNextChild()
{
	//if (_idxChild >= _pDirectoryOwner->size()) return nullptr;
	//return (*_pDirectoryOwner)[_idxChild++]->Reference();
	return nullptr;
}

void PrintDirectory(Directory& directory, int indentLevel)
{
	::printf("%*s%s\n", indentLevel * 2, "", directory.GetName());
	directory.RewindChild();
	Directory* pDirectoryChild;
	while ((pDirectoryChild = directory.NextChild())) {
		PrintDirectory(*pDirectoryChild, indentLevel + 1);
	}
}

Gurax_TesterEntry(Directory)
{
#if 0
	char sep = '/';
	bool caseFlag = false;
	RefPtr<Directory_CustomContainer> pDirectory(new Directory_CustomContainer("foo", Directory::Type::Root, sep, caseFlag));
	pDirectory->AddChildInTree("dir1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir1/dir1-3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir2", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir3", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir4/dir4-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir5/dir5-1/dir5-1-1/dir5-1-1-1", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir6/", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	pDirectory->AddChildInTree("dir4", new Directory_CustomContainer(Directory::Type::Container, sep, caseFlag));
	PrintDirectory(*pDirectory, 0);
	do {
		const char* pathNames[] = {
			"dir1",
			"dir1/",
			"dirx",
			"dir1/dir1-1",
			"dir1/dir1-1/",
			"dir1/dir1-x",
			"dir5/dir5-1/dir5-1-1/dir5-1-1-1",
			"dir5/dir5-1/dir5-1-1/dir5-1-1-1/",
		};
		for (int i = 0; i < ArraySizeOf(pathNames); i++) {
			const char* pathName = pathNames[i];
			const char* p = pathName;
			Directory* pDirectoryFound = pDirectory->SearchInTree(&p);
			::printf("\"%s\": %s, \"%s\"\n", pathName, pDirectoryFound? "found" : "not found", p);
		}
	} while (0);
#endif
}

}
