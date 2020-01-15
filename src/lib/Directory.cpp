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
	RefPtr<Directory> pDirectory(LockDirectoryParent());
	for ( ; pDirectory; pDirectory.reset(pDirectory->LockDirectoryParent())) {
		// a "boundary container" directory may have an empty name
		if (*pDirectory->GetName() != '\0' || pDirectory->IsRootContainer()) {
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
	} else if (addSepFlag && IsContainer() && !_name.empty()) {
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
	RefPtr<Directory> pDirectory(LockDirectoryParent());
	for ( ; pDirectory; pDirectory.reset(pDirectory->LockDirectoryParent())) {
		cnt++;
	}
	return cnt;
}

Value* Directory::DoCreateStatValue()
{
	Error::Issue(ErrorType::PropertyError, "no status value available");
	return Value::nil();
}

String Directory::ToString(const StringStyle& ss) const
{
	return "";
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

//------------------------------------------------------------------------------
// Directory_CustomContainer
//------------------------------------------------------------------------------
bool Directory_CustomContainer::AddChildInTree(const char* pathName, RefPtr<Directory> pDirectoryChild)
{
	const char* p = pathName;
	if (PathName::IsSep(*p)) p++;
	String field;
	Directory_CustomContainer* pDirectoryParent = this;
	for ( ; ; p++) {
		char ch = *p;
		if (!PathName::IsSep(ch) && ch != '\0') {
			field += ch;
			continue;
		}
		DirectoryOwner& directoryOwner = pDirectoryParent->GetDirectoryOwner();
		if (field.empty()) {
			Error::Issue(ErrorType::PathError, "invalid path name");
			return false;
		} else if (ch == '\0' || *(p + 1) == '\0') {
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
			break;
		}
		Directory* pDirectory = directoryOwner.FindByName(field.c_str());
		if (!pDirectory) {
			auto pDirectoryNew = new Directory_CustomContainer(
					pDirectoryParent, field.c_str(), Type::Container,
					pDirectoryParent->GetSep(), pDirectoryParent->IsCaseSensitive());
			directoryOwner.push_back(pDirectory);
			field.clear();
			pDirectoryParent = pDirectoryNew;
		} else if (!pDirectory->IsCustomContainer()) {
			Error::Issue(ErrorType::PathError, "invalid path name");
			return false;
		} else {
			field.clear();
			pDirectoryParent = dynamic_cast<Directory_CustomContainer*>(pDirectory);
		}
	}
	return true;
}

Directory* Directory_CustomContainer::DoNextChild()
{
	if (_idx >= _pDirectoryOwner->size()) return nullptr;
	return (*_pDirectoryOwner)[_idx++]->Reference();
}

Stream* Directory_CustomContainer::DoOpenStream(Stream::OpenFlags openFlags)
{
	return nullptr;
}

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
	//_directoryDeque.push_back(pDirectory);
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
		if (pDirectoryChild->IsContainer() &&
			(_depthMax < 0 || pDirectoryChild->CountDepth() < _depthMax)) {
			_directoryDeque.push_back(pDirectoryChild->Reference());
		}
		if ((pDirectoryChild->IsContainer() && _dirFlag) || (!pDirectoryChild->IsContainer() && _fileFlag)) {
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
				if (pDirectoryChild->IsContainer()) {
					_directoryDeque.push_back(pDirectoryChild->Reference());
					_depthDeque.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if ((pDirectoryChild->IsContainer() && _dirFlag) ||
					   (!pDirectoryChild->IsContainer() && _fileFlag)) {
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
