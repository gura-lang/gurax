//==============================================================================
// Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
Directory* Directory::Open(const char* pathName, Type typeWouldBe)
{
	return PathMgr::OpenDirectory(pathName, typeWouldBe);
}

String Directory::MakeFullPathName(bool addSepFlag, const char* pathNameTrail) const
{
	String pathName(_name);
	const Directory* pDirectory = GetDirectoryParent();
	for ( ; pDirectory; pDirectory = pDirectory->GetDirectoryParent()) {
		// a "boundary container" directory may have an empty name
		if (*pDirectory->GetName() != '\0' || pDirectory->IsRoot()) {
			String str(pDirectory->GetName());
			size_t len = str.size();
			if (len == 0 || !PathName::IsSep(str[len - 1])) {
				str += pDirectory->GetSep();
			}
			str += pathName;
			pathName = str;
		}
	}
	if (pathNameTrail) {
		size_t len = pathName.size();
		if (len == 0 || !PathName::IsSep(pathName[len - 1])) {
			pathName += GetSep();
		}
		for (const char *p = pathNameTrail; *p != '\0'; p++) {
			char ch = PathName::IsSep(*p)? GetSep() : *p;
			pathName += ch;
		}
	} else if (addSepFlag && IsLikeContainer() && !_name.empty()) {
		size_t len = pathName.size();
		if (len > 0 && !PathName::IsSep(pathName[len - 1])) {
			pathName += GetSep();
		}
	}
	return pathName;
}

int Directory::CountDepth() const
{
	int cnt = 0;
	const Directory* pDirectory = GetDirectoryParent();
	for ( ; pDirectory; pDirectory = pDirectory->GetDirectoryParent()) {
		cnt++;
	}
	return cnt;
}

Directory* Directory::SearchByName(const char* name)
{
	RewindChild();
	for (;;) {
		RefPtr<Directory> pDirectory(NextChild());
		if (pDirectory->DoesMatch(name)) return pDirectory.release();
	}
	return nullptr;
}

Directory* Directory::SearchInTree(const char** pPathName)
{
	RefPtr<Directory> pDirectory;
	String field;
	for (const char*& p = *pPathName; ; ) {
		if (*p == '\0') {
			// nothing to do
		} else if (PathName::IsSep(*p)) {
			p++;
		} else {
			field += *p++;
			continue;
		}
		if (field.empty()) return nullptr;
		RefPtr<Directory> pDirectoryChild(SearchByName(field.c_str()));
		if (!pDirectoryChild) return nullptr;
		if (*p == '\0' || !pDirectoryChild->IsContainer()) break;
		field.clear();
		pDirectory.reset(pDirectoryChild.release());
	}
	return pDirectory.release();
}

Value* Directory::DoCreateStatValue()
{
	Error::Issue(ErrorType::PropertyError, "no status value available");
	return Value::nil();
}

String Directory::ToString(const StringStyle& ss) const
{
	return GetName();
}

//------------------------------------------------------------------------------
// Directory::FactoryList
//------------------------------------------------------------------------------
Directory::Factory* Directory::FactoryList::FindByName(const char* name) const
{
	for (Factory* pFactory : *this) {
		if (pFactory->DoesMatch(name)) return pFactory;
	}
	return nullptr;
}

Directory::FactoryList::iterator Directory::FactoryList::FindIteratorByName(const char* name)
{
	for (auto ppFactory = begin(); ppFactory != end(); ppFactory++) {
		Factory* pFactory = *ppFactory;
		if (pFactory->DoesMatch(name)) return ppFactory;
	}
	return end();
}

//------------------------------------------------------------------------------
// Directory::FactoryOwner
//------------------------------------------------------------------------------
void Directory::FactoryOwner::Clear()
{
	for (Factory* pFactory : *this) Factory::Delete(pFactory);
	clear();
}

//------------------------------------------------------------------------------
// Directory::Factory
//------------------------------------------------------------------------------
bool Directory::Factory::AddChildInTree(const char* pathName, RefPtr<Factory> pFactoryChild)
{
	String driveLetter;
	String prefix;
	StringList fields;
	PathName(pathName).SplitIntoFields(&driveLetter, &prefix, fields);
	Factory* pFactoryParent = this;
	auto pField = fields.begin();
	if (pField == fields.end()) {
		Error::Issue(ErrorType::PathError, "invalid path name");
		return false;
	}
	for ( ; pField + 1 != fields.end() && !(pField + 1)->empty(); pField++) {
		const String& field = *pField;
		Factory* pFactory = pFactoryParent->GetFactoryOwner().FindByName(field.c_str());
		if (!pFactory) {
			Factory* pFactoryNew = new Factory(field, new FactoryOwner(), pFactoryChild->GetCaseFlag());
			pFactoryParent->GetFactoryOwner().push_back(pFactoryNew);
			pFactoryParent = pFactoryNew;
		} else {
			pFactoryParent = pFactory;
		}
	}
	const String& field = *pField;
	pFactoryChild->SetName(field);
	FactoryOwner& factoryOwner = pFactoryParent->GetFactoryOwner();
	auto ppFactoryFound = factoryOwner.FindIteratorByName(field.c_str());
	if (ppFactoryFound == factoryOwner.end()) {
		factoryOwner.push_back(pFactoryChild.release());
	} else {
		pFactoryChild->SetFactoryOwner((*ppFactoryFound)->GetFactoryOwner().Reference());
		Factory::Delete(*ppFactoryFound);
		*ppFactoryFound = pFactoryChild.release();
	}
	return true;
}

//------------------------------------------------------------------------------
// DirectoryList
//------------------------------------------------------------------------------
Directory* DirectoryList::FindByName(const char* name) const
{
	for (Directory* pDirectory : *this) {
		if (::strcmp(pDirectory->GetName(), name) == 0) return pDirectory;
	}
	return nullptr;
}

DirectoryList::iterator DirectoryList::FindIteratorByName(const char* name)
{
	for (auto ppDirectory = begin(); ppDirectory != end(); ppDirectory++) {
		if (::strcmp((*ppDirectory)->GetName(), name) == 0) return ppDirectory;
	}
	return end();
}

DirectoryList::const_iterator DirectoryList::FindIteratorByName(const char* name) const
{
	for (auto ppDirectory = begin(); ppDirectory != end(); ppDirectory++) {
		if (::strcmp((*ppDirectory)->GetName(), name) == 0) return ppDirectory;
	}
	return end();
}

//------------------------------------------------------------------------------
// DirectoryOwner
//------------------------------------------------------------------------------
void DirectoryOwner::Clear()
{
	for (Directory* pDirectory : *this) Directory::Delete(pDirectory);
	clear();
}

//------------------------------------------------------------------------------
// DirectoryDeque
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DirectoryDequeOwner
//------------------------------------------------------------------------------
void DirectoryDequeOwner::Clear()
{
	for (Directory* pDirectory : *this) Directory::Delete(pDirectory);
	clear();
}

#if 0
//------------------------------------------------------------------------------
// Directory_CustomContainer
//------------------------------------------------------------------------------
bool Directory_CustomContainer::AddChildInTree(const char* pathName, RefPtr<Directory> pDirectoryChild)
{
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
	return true;
}

void Directory_CustomContainer::DoRewindChild()
{
	_idxChild = 0;
}

Directory* Directory_CustomContainer::DoNextChild()
{
	if (_idxChild >= _pDirectoryOwner->size()) return nullptr;
	return (*_pDirectoryOwner)[_idxChild++]->Reference();
}
#endif

//-----------------------------------------------------------------------------
// Iterator_DirectoryWalk
//-----------------------------------------------------------------------------
Iterator_DirectoryWalk::Iterator_DirectoryWalk(
	Directory* pDirectory, int depthMax, const StringList& patterns,
	bool addSepFlag, bool statFlag, bool caseFlag, bool fileFlag, bool dirFlag) :
	_pDirectoryCur(pDirectory), _depthMax(depthMax), _patterns(patterns),
	_addSepFlag(addSepFlag), _statFlag(statFlag), _caseFlag(caseFlag),
	_fileFlag(fileFlag), _dirFlag(dirFlag)
{
	_depthMax = (depthMax < 0)? -1 : pDirectory->CountDepth() + depthMax + 1;
	_pDirectoryCur->RewindChild();
}

Value* Iterator_DirectoryWalk::DoNextValue()
{
	RefPtr<Value> pValueRtn;
	for (;;) {
		RefPtr<Directory> pDirectoryChild;
		for (;;) {
			pDirectoryChild.reset(_pDirectoryCur->NextChild());
			if (pDirectoryChild) break;
			if (_directoryDeque.empty()) {
				_pDirectoryCur.reset(nullptr);
				return nullptr;
			}
			_pDirectoryCur.reset(_directoryDeque.front());
			_directoryDeque.pop_front();
		}
		if (!pDirectoryChild) return nullptr;
		if (pDirectoryChild->IsLikeContainer() &&
			(_depthMax < 0 || pDirectoryChild->CountDepth() < _depthMax)) {
			_directoryDeque.push_back(pDirectoryChild->Reference());
		}
		if ((pDirectoryChild->IsLikeContainer() && _dirFlag) || (!pDirectoryChild->IsLikeContainer() && _fileFlag)) {
			bool matchFlag = false;
			for (const String& pattern : _patterns) {
				if (PathName(pDirectoryChild->GetName()).SetCaseFlag(_caseFlag).DoesMatchPattern(pattern.c_str())) {
					matchFlag = true;
					break;
				}
			}
			if (_patterns.empty() || matchFlag) {
				if (_statFlag) {
					pValueRtn.reset(pDirectoryChild->CreateStatValue());
				} else {
					pValueRtn.reset(new Value_String(pDirectoryChild->MakeFullPathName(_addSepFlag)));
				}
				break;
			}
		}
	}
	return pValueRtn.release();
}

String Iterator_DirectoryWalk::ToString(const StringStyle& ss) const
{
	String str;
	str = "DirectoryWalk";
	if (_statFlag) str += ":stat";
	if (_caseFlag) str += ":case";
	if (_fileFlag) str += ":file";
	if (_dirFlag) str += ":dir";
	return str;
}

//-----------------------------------------------------------------------------
// Iterator_DirectoryGlob
//-----------------------------------------------------------------------------
Iterator_DirectoryGlob::Iterator_DirectoryGlob(
	bool addSepFlag, bool statFlag, bool caseFlag, bool fileFlag, bool dirFlag) :
	_addSepFlag(addSepFlag), _statFlag(statFlag), _caseFlag(caseFlag),
	_fileFlag(fileFlag), _dirFlag(dirFlag), _depth(0)
{
}

bool Iterator_DirectoryGlob::Init(const char* pattern)
{
	String pathName, field;
	const char* patternTop = pattern;
	for (const char* p = pattern; ; p++) {
		char ch = *p;
		if (PathName::IsSep(ch) || ch == '\0') {
			patternTop = p;
			pathName += field;
			if (ch == '\0') break;
			patternTop++;
			pathName += ch;
			field.clear();
		} else if (PathName::IsWildCardChar(ch)) {
			break;
		} else {
			field += ch;
		}
	}
	field.clear();
	for (const char* p = patternTop; ; p++) {
		char ch = *p;
		if (PathName::IsSep(ch) || ch == '\0') {
			_patternSegs.push_back(field);
			if (ch == '\0') break;
			field.clear();
		} else {
			field += ch;
		}
	}
	_pDirectoryCur.reset(Directory::Open(pathName.c_str()));
	return !!_pDirectoryCur;
}

Value* Iterator_DirectoryGlob::DoNextValue()
{
	RefPtr<Value> pValueRtn;
	for (;;) {
		RefPtr<Directory> pDirectoryChild;
		for (;;) {
			pDirectoryChild.reset(_pDirectoryCur->NextChild());
			if (pDirectoryChild) break;
			if (_directoryDeque.empty()) {
				_pDirectoryCur.reset(nullptr);
				return nullptr;
			}
			_pDirectoryCur.reset(_directoryDeque.front());
			_depth = _depthDeque.front();
			_directoryDeque.pop_front();
			_depthDeque.pop_front();
		}
		if (!pDirectoryChild) return nullptr;
		if (PathName(pDirectoryChild->GetName()).SetCaseFlag(_caseFlag).DoesMatchPattern(_patternSegs[_depth].c_str())) {
			if (_depth + 1 < _patternSegs.size()) {
				if (pDirectoryChild->IsLikeContainer()) {
					_directoryDeque.push_back(pDirectoryChild->Reference());
					_depthDeque.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if ((pDirectoryChild->IsLikeContainer() && _dirFlag) ||
					   (!pDirectoryChild->IsLikeContainer() && _fileFlag)) {
				if (_statFlag) {
					pValueRtn.reset(pDirectoryChild->CreateStatValue());
				} else {
					pValueRtn.reset(new Value_String(pDirectoryChild->MakeFullPathName(_addSepFlag)));
				}
				break;
			}
		}
	}
	return pValueRtn.release();
}

String Iterator_DirectoryGlob::ToString(const StringStyle& ss) const
{
	String str;
	str = "DirectoryGlob";
	if (_statFlag) str += ":stat";
	if (_caseFlag) str += ":case";
	if (_fileFlag) str += ":file";
	if (_dirFlag) str += ":dir";
	return str;
}

}
