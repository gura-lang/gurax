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
	RefPtr<Directory> pDirectory;
	RewindChild();
	for (;;) {
		pDirectory.reset(NextChild());
		if (!pDirectory || pDirectory->DoesMatch(name)) break;
	}
	return pDirectory.release();
}

Directory* Directory::SearchInTree(const char** pPathName)
{
	RefPtr<Directory> pDirectory(Reference());
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
		pDirectory.reset(pDirectory->SearchByName(field.c_str()));
		if (!pDirectory) return nullptr;
		if (*p == '\0' || !pDirectory->IsFolder()) break;
		field.clear();
	}
	return pDirectory.release();
}

Value_Stat* Directory::DoCreateStatValue()
{
	Error::Issue(ErrorType::PropertyError, "no status value available");
	return nullptr;
}

String Directory::ToString(const StringStyle& ss) const
{
	return GetName();
}

//------------------------------------------------------------------------------
// Directory::WalkFlag
//------------------------------------------------------------------------------
String Directory::WalkFlag::ToString(WalkFlags walkFlags)
{
	String str;
	if (IsAddSep(walkFlags)) str += ":addSep";
	if (IsStat(walkFlags)) str += ":stat";
	if (IsFile(walkFlags)) str += ":file";
	if (IsDir(walkFlags)) str += ":dir";
	if (IsCase(walkFlags)) str += ":case";
	return str;
}

void Directory::WalkFlag::DeclareAttrOpt(Function& func)
{
	func.DeclareAttrOpt(Gurax_Symbol(addSep));
	func.DeclareAttrOpt(Gurax_Symbol(elimSep));
	func.DeclareAttrOpt(Gurax_Symbol(stat));
	func.DeclareAttrOpt(Gurax_Symbol(file));
	func.DeclareAttrOpt(Gurax_Symbol(dir));
	func.DeclareAttrOpt(Gurax_Symbol(case_));
	func.DeclareAttrOpt(Gurax_Symbol(icase));
}

Directory::WalkFlags Directory::WalkFlag::CheckArgument(const Argument& argument, bool addSepFlagDefault, bool caseFlagDefault)
{
	WalkFlags walkFlags = 0;
	if (addSepFlagDefault) walkFlags |= AddSep;
	if (caseFlagDefault) walkFlags |= Case;
	if (argument.IsSet(Gurax_Symbol(addSep))) walkFlags |= AddSep;
	if (argument.IsSet(Gurax_Symbol(elimSep))) walkFlags &= ~AddSep;
	if (argument.IsSet(Gurax_Symbol(stat))) walkFlags |= Stat;
	if (argument.IsSet(Gurax_Symbol(file)) || !argument.IsSet(Gurax_Symbol(dir))) walkFlags |= File;
	if (!argument.IsSet(Gurax_Symbol(file)) || argument.IsSet(Gurax_Symbol(dir))) walkFlags |= Dir;
	if (argument.IsSet(Gurax_Symbol(case_))) walkFlags |= Case;
	if (argument.IsSet(Gurax_Symbol(icase))) walkFlags &= ~Case;
	return walkFlags;
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
	String fieldAccum;
	for ( ; pField + 1 != fields.end() && !(pField + 1)->empty(); pField++) {
		const String& field = *pField;
		if (!fieldAccum.empty()) fieldAccum += pCoreChild->GetSep();
		fieldAccum += field;
		Core* pCore = pCoreParent->GetCoreOwner().FindByName(field.c_str());
		if (!pCore) {
			Core* pCoreNew = new DirectoryDummy::CoreEx(fieldAccum, field, GetSep(), GetCaseFlag());
			pCoreParent->GetCoreOwner().push_back(pCoreNew);
			pCoreParent = pCoreNew;
		} else {
			pCoreParent = pCore;
		}
	}
	const String& field = *pField;
	pCoreChild->SetName(field);
	CoreOwner& coreOwner = pCoreParent->GetCoreOwner();
	auto ppCoreFound = coreOwner.FindIteratorByName(field.c_str());
	if (ppCoreFound == coreOwner.end()) {
		coreOwner.push_back(pCoreChild.release());
	} else {
		pCoreChild->SetCoreOwner((*ppCoreFound)->GetCoreOwner().Reference());
		Core::Delete(*ppCoreFound);
		*ppCoreFound = pCoreChild.release();
	}
	return true;
}

void Directory::Core::Print(Stream& stream, int indentLevel) const
{
	stream.Printf("%*s%s%s\n", indentLevel * 2, "", GetName(),
					(_type == Type::Folder)? "/" : (_type == Type::Boundary)? "%" : "");
	for (const Core* pCore : GetCoreOwner()) {
		pCore->Print(stream, indentLevel + 1);
	}
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
	Directory* pDirectory, int depthMax, const StringList& patterns, Directory::WalkFlags walkFlags) :
	_pDirectoryCur(pDirectory), _depthMax(depthMax), _patterns(patterns), _walkFlags(walkFlags)
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
		if ((pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsDir(_walkFlags)) ||
			(!pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsFile(_walkFlags))) {
			bool matchFlag = false;
			for (const String& pattern : _patterns) {
				if (PathName(pDirectoryChild->GetName()).SetCaseFlag(Directory::WalkFlag::IsCase(_walkFlags)).DoesMatchPattern(pattern.c_str())) {
					matchFlag = true;
					break;
				}
			}
			if (_patterns.empty() || matchFlag) {
				if (Directory::WalkFlag::IsStat(_walkFlags)) {
					pValueRtn.reset(pDirectoryChild->CreateStatValue());
				} else {
					pValueRtn.reset(new Value_String(pDirectoryChild->MakeFullPathName(Directory::WalkFlag::IsAddSep(_walkFlags))));
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
	str += Directory::WalkFlag::ToString(_walkFlags);
	return str;
}

//-----------------------------------------------------------------------------
// Iterator_DirectoryGlob
//-----------------------------------------------------------------------------
Iterator_DirectoryGlob::Iterator_DirectoryGlob() : _walkFlags(0), _depth(0)
{
}

bool Iterator_DirectoryGlob::Initialize(const char* pattern)
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
	if (*patternTop) {
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
	}
	_pDirectoryCur.reset(OpenDirectory(pathName.c_str()));
	return !!_pDirectoryCur;
}

Value* Iterator_DirectoryGlob::DoNextValue()
{
	if (!_pDirectoryCur) return nullptr;
	RefPtr<Value> pValueRtn;
	if (_patternSegs.empty()) {
		RefPtr<Directory> pDirectoryChild(_pDirectoryCur.release());
		if ((pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsDir(_walkFlags)) ||
			(!pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsFile(_walkFlags))) {
			if (Directory::WalkFlag::IsStat(_walkFlags)) {
				pValueRtn.reset(pDirectoryChild->CreateStatValue());
			} else {
				pValueRtn.reset(new Value_String(pDirectoryChild->MakeFullPathName(Directory::WalkFlag::IsAddSep(_walkFlags))));
			}
			return pValueRtn.release();
		} else {
			return nullptr;
		}
	}
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
			_depth = _depthDeque.d.front();
			_directoryDeque.pop_front();
			_depthDeque.d.pop_front();
		}
		if (!pDirectoryChild) return nullptr;
		if (PathName(pDirectoryChild->GetName()).SetCaseFlag(Directory::WalkFlag::IsCase(_walkFlags)).DoesMatchPattern(_patternSegs[_depth].c_str())) {
			if (_depth + 1 < _patternSegs.size()) {
				if (pDirectoryChild->IsLikeFolder()) {
					_directoryDeque.push_back(pDirectoryChild->Reference());
					_depthDeque.d.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if ((pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsDir(_walkFlags)) ||
						(!pDirectoryChild->IsLikeFolder() && Directory::WalkFlag::IsFile(_walkFlags))) {
				if (Directory::WalkFlag::IsStat(_walkFlags)) {
					pValueRtn.reset(pDirectoryChild->CreateStatValue());
				} else {
					pValueRtn.reset(new Value_String(pDirectoryChild->MakeFullPathName(Directory::WalkFlag::IsAddSep(_walkFlags))));
				}
				break;
			}
		}
	}
	return pValueRtn.release();
}

Directory* Iterator_DirectoryGlob::OpenDirectory(const char* pathName)
{
	return PathMgr::OpenDirectory(pathName);
}

String Iterator_DirectoryGlob::ToString(const StringStyle& ss) const
{
	String str;
	str = "DirectoryGlob";
	str += Directory::WalkFlag::ToString(_walkFlags);
	return str;
}

}
