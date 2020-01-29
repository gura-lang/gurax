//==============================================================================
// Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
void Directory::Bootup()
{
	Directory::CoreOwner::Empty.reset(new CoreOwner());
}

Directory* Directory::Open(const char* pathName, Type typeWouldBe)
{
	return PathMgr::OpenDirectory(pathName, typeWouldBe);
}

String Directory::MakeFullPathName(bool addSepFlag, const char* pathNameTrail) const
{
	String pathName(GetName());
	const Directory* pDirectory = GetDirectoryParent();
	for ( ; pDirectory; pDirectory = pDirectory->GetDirectoryParent()) {
		// a "boundary container" directory may have an empty name
		if (*pDirectory->GetName() != '\0') {
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
	} else if (addSepFlag && IsLikeFolder() && *GetName() != '\0') {
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
		if (*p == '\0' || !pDirectoryChild->IsFolder()) break;
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
// Directory::CoreList
//------------------------------------------------------------------------------
Directory::Core* Directory::CoreList::FindByName(const char* name) const
{
	for (Core* pCore : *this) {
		if (pCore->DoesMatch(name)) return pCore;
	}
	return nullptr;
}

Directory::CoreList::iterator Directory::CoreList::FindIteratorByName(const char* name)
{
	for (auto ppCore = begin(); ppCore != end(); ppCore++) {
		Core* pCore = *ppCore;
		if (pCore->DoesMatch(name)) return ppCore;
	}
	return end();
}

//------------------------------------------------------------------------------
// Directory::CoreOwner
//------------------------------------------------------------------------------
RefPtr<Directory::CoreOwner> Directory::CoreOwner::Empty;

void Directory::CoreOwner::Clear()
{
	for (Core* pCore : *this) Core::Delete(pCore);
	clear();
}

//------------------------------------------------------------------------------
// Directory::Core
//------------------------------------------------------------------------------
bool Directory::Core::AddChildInTree(const char* pathName, RefPtr<Core> pCoreChild)
{
	String driveLetter;
	String prefix;
	StringList fields;
	PathName(pathName).SplitIntoFields(&driveLetter, &prefix, fields);
	Core* pCoreParent = this;
	auto pField = fields.begin();
	if (pField == fields.end()) {
		Error::Issue(ErrorType::PathError, "invalid path name");
		return false;
	}
	for ( ; pField + 1 != fields.end() && !(pField + 1)->empty(); pField++) {
		const String& field = *pField;
		Core* pCore = pCoreParent->GetCoreOwner().FindByName(field.c_str());
		if (!pCore) {
			Core* pCoreNew = new Core(Type::Folder, field, GetSep(), GetCaseFlag(), new CoreOwner());
			pCoreParent->GetCoreOwner().push_back(pCoreNew);
			pCoreParent = pCoreNew;
		} else {
			pCoreParent = pCore;
		}
	}
	const String& field = *pField;
	pCoreChild->SetName(field);
	CoreOwner& factoryOwner = pCoreParent->GetCoreOwner();
	auto ppCoreFound = factoryOwner.FindIteratorByName(field.c_str());
	if (ppCoreFound == factoryOwner.end()) {
		factoryOwner.push_back(pCoreChild.release());
	} else {
		pCoreChild->SetCoreOwner((*ppCoreFound)->GetCoreOwner().Reference());
		Core::Delete(*ppCoreFound);
		*ppCoreFound = pCoreChild.release();
	}
	return true;
}

void Directory::Core::Print(Stream& stream, int indentLevel) const
{
	stream.Printf("");
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
		if (pDirectoryChild->IsLikeFolder() &&
			(_depthMax < 0 || pDirectoryChild->CountDepth() < _depthMax)) {
			_directoryDeque.push_back(pDirectoryChild->Reference());
		}
		if ((pDirectoryChild->IsLikeFolder() && _dirFlag) || (!pDirectoryChild->IsLikeFolder() && _fileFlag)) {
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
				if (pDirectoryChild->IsLikeFolder()) {
					_directoryDeque.push_back(pDirectoryChild->Reference());
					_depthDeque.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if ((pDirectoryChild->IsLikeFolder() && _dirFlag) ||
					   (!pDirectoryChild->IsLikeFolder() && _fileFlag)) {
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
