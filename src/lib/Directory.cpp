//==============================================================================
// Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
		} else {
			field += ch;
		}
	}
	_pDirectoryCur.reset(Directory::Open(pathName.c_str()));
	//_pDirectoryCur.reset(Directory::Open(pathName.c_str(), PathMgr::NotFoundMode::Signal));
	if (!_pDirectoryCur) return false;
	//_depthQue.push_back(0);
	return true;
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
		if (PathName(pDirectoryChild->GetName()).SetCaseFlag(_caseFlag).DoesMatch(_patternSegs[_depth].c_str())) {
			bool typeMatchFlag =
				(pDirectoryChild->IsContainer() && _dirFlag) ||
				(!pDirectoryChild->IsContainer() && _fileFlag);
			if (_depth + 1 < _patternSegs.size()) {
				if (pDirectoryChild->IsContainer()) {
					_directoryDeque.push_back(pDirectoryChild->Reference());
					_depthDeque.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if (typeMatchFlag) {
				break;
			}
		}
	}
#if 0
	if (_statFlag) {
		Object *pObj = pDirectoryChild->GetStatObj(sig);
		if (sig.IsSignalled()) return false;
		if (pObj != nullptr) value = Value(pObj);
	} else {
		value = Value(pDirectoryChild->MakePathName(_addSepFlag));
	}
	return true;
#endif
	return nullptr;
}

String Iterator_DirectoryGlob::ToString(const StringStyle& ss) const
{
	return "DirectoryGlob";
}

//------------------------------------------------------------------------------
// Directory
//------------------------------------------------------------------------------
Directory* Directory::Open(const char* pathName)
{
	PathMgr* pPathMgr = PathMgr::FindResponsible(pathName);
	if (!pPathMgr) return nullptr;
	return pPathMgr->OpenDirectory(pathName);
}

String Directory::MakePathName(bool addSepFlag, const char* pathNameTrail) const
{
	String pathName(_name);
	for (Directory* pDirectory = GetDirectoryParent(); pDirectory; pDirectory = pDirectory->GetDirectoryParent()) {
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
	for (const Directory* pDirectory = GetDirectoryParent(); pDirectory;
		 pDirectory = pDirectory->GetDirectoryParent()) {
		cnt++;
	}
	return cnt;
}

Value* Directory::DoGetStatValue()
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
	bool addSepFlag, bool statFlag,
	bool caseFlag, bool fileFlag, bool dirFlag) :
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
				if (PathName(pDirectoryChild->GetName()).SetCaseFlag(_caseFlag).DoesMatch(pattern.c_str())) {
					matchFlag = true;
					break;
				}
			}
			if (_patterns.empty() || matchFlag) {
				if (_statFlag) {
					pValueRtn.reset(pDirectoryChild->GetStatValue());
				} else {
					pValueRtn.reset(new Value_String(pDirectoryChild->MakePathName(_addSepFlag)));
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
	str += _statFlag? ":stat" : ":name";
	return str;
}

}
