//==============================================================================
// Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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

void DirectoryDequeOwner::Clear()
{
	for (Directory* pDirectory : *this) Directory::Delete(pDirectory);
	clear();
}

//------------------------------------------------------------------------------
// Iterator_DirectoryWalk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DirectoryWalk : public Iterator {
public:
private:
	bool _addSepFlag;
	bool _statFlag;
	bool _ignoreCaseFlag;
	bool _fileFlag;
	bool _dirFlag;
	RefPtr<Directory> _pDirectory;
	int _depthMax;
	StringList _patterns;
	DirectoryDequeOwner _directoryDeque;
public:
	Iterator_DirectoryWalk(bool addSepFlag, bool statFlag,
						   bool ignoreCaseFlag, bool fileFlag, bool dirFlag,
						   Directory* pDirectory, int depthMax, const StringList& patterns);
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_DirectoryWalk
//-----------------------------------------------------------------------------
Iterator_DirectoryWalk::Iterator_DirectoryWalk(
	bool addSepFlag, bool statFlag,
	bool ignoreCaseFlag, bool fileFlag, bool dirFlag,
	Directory* pDirectory, int depthMax, const StringList& patterns) :
	_addSepFlag(addSepFlag), _statFlag(statFlag), _ignoreCaseFlag(ignoreCaseFlag),
	_fileFlag(fileFlag), _dirFlag(dirFlag), _pDirectory(nullptr), _depthMax(0),
	_patterns(patterns)
{
	_depthMax = (depthMax < 0)? -1 : pDirectory->CountDepth() + depthMax + 1;
	_directoryDeque.push_back(pDirectory);
}

Value* Iterator_DirectoryWalk::DoNextValue()
{
#if 0
	Signal &sig = env.GetSignal();
	for (;;) {
		Directory *pDirectoryChild = nullptr;
		while (_pDirectory.IsNull() ||
				(pDirectoryChild = _pDirectory->Next(env)) == nullptr) {
			if (_directoryQue.empty()) {
				_pDirectory.reset(nullptr);
				return false;
			}
			Directory *pDirectoryNext = _directoryQue.front();
			_directoryQue.pop_front();
			_pDirectory.reset(pDirectoryNext);
		}
		if (sig.IsSignalled()) return false;
		if (pDirectoryChild->IsContainer() &&
					(_depthMax < 0 || pDirectoryChild->CountDepth() < _depthMax)) {
			_directoryQue.push_back(Directory::Reference(pDirectoryChild));
		}
		bool typeMatchFlag =
				(pDirectoryChild->IsContainer() && _dirFlag) ||
				(!pDirectoryChild->IsContainer() && _fileFlag);
		if (typeMatchFlag) {
			bool matchFlag = false;
			foreach_const (StringList, pPattern, _patterns) {
				if (PathMgr::DoesMatchName(pPattern->c_str(),
									pDirectoryChild->GetName(), _ignoreCaseFlag)) {
					matchFlag = true;
					break;
				}
			}
			if (_patterns.empty() || matchFlag) {
				if (_statFlag) {
					Object *pObj = pDirectoryChild->GetStatObj(sig);
					if (sig.IsSignalled()) return false;
					if (pObj != nullptr) value = Value(pObj);
				} else {
					value = Value(pDirectoryChild->MakePathName(_addSepFlag));
				}
				Directory::Delete(pDirectoryChild);
				break;
			}
		}
		Directory::Delete(pDirectoryChild);
	}
	return true;
#endif
	return nullptr;
}

String Iterator_DirectoryWalk::ToString(const StringStyle& ss) const
{
	String str;
	str = "DirectoryWalk";
	str += _statFlag? ":stat" : ":name";
	return str;
}

//------------------------------------------------------------------------------
// Iterator_DirectoryGlob
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DirectoryGlob : public Iterator {
public:
	typedef std::deque<size_t> DepthDeque;
private:
	bool _addSepFlag;
	bool _statFlag;
	bool _ignoreCaseFlag;
	bool _fileFlag;
	bool _dirFlag;
	RefPtr<Directory> _pDirectory;
	size_t _depth;
	DepthDeque _depthDeque;
	StringList _patternSegs;
	DirectoryDequeOwner _directoryDeque;
public:
	Iterator_DirectoryGlob(bool addSepFlag, bool statFlag,
						   bool ignoreCaseFlag, bool fileFlag, bool dirFlag);
	bool Init(const char* pattern);
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_DirectoryGlob
//-----------------------------------------------------------------------------
Iterator_DirectoryGlob::Iterator_DirectoryGlob(
	bool addSepFlag, bool statFlag, bool ignoreCaseFlag, bool fileFlag, bool dirFlag) :
	_addSepFlag(addSepFlag), _statFlag(statFlag), _ignoreCaseFlag(ignoreCaseFlag),
	_fileFlag(fileFlag), _dirFlag(dirFlag), _pDirectory(nullptr), _depth(0)
{
}

bool Iterator_DirectoryGlob::Init(const char* pattern)
{
#if 0
	Signal &sig = env.GetSignal();
	String pathName, field;
	const char *patternTop = pattern;
	for (const char *p = pattern; ; p++) {
		char ch = *p;
		if (IsFileSeparator(ch) || ch == '\0') {
			patternTop = p;
			pathName += field;
			if (ch == '\0') break;
			patternTop++;
			pathName += ch;
			field.clear();
		} else if (PathMgr::IsWildCardChar(ch)) {
			break;
		} else {
			field += ch;
		}
	}
	field.clear();
	for (const char *p = patternTop; ; p++) {
		char ch = *p;
		if (IsFileSeparator(ch) || ch == '\0') {
			_patternSegs.push_back(field);
			if (ch == '\0') break;
		} else {
			field += ch;
		}
	}
	AutoPtr<Directory> pDirectory(Directory::Open(env,
									pathName.c_str(), PathMgr::NF_Signal));
	if (sig.IsSignalled()) return false;
	_directoryQue.push_back(pDirectory.release());
	_depthQue.push_back(0);
#endif
	return true;
}

Value* Iterator_DirectoryGlob::DoNextValue()
{
#if 0
	Signal &sig = env.GetSignal();
	Directory *pDirectoryChild = nullptr;
	for (;;) {
		while (_pDirectory.IsNull() ||
				(pDirectoryChild = _pDirectory->Next(env)) == nullptr) {
			if (_directoryQue.empty()) {
				_pDirectory.reset(nullptr);
				return false;
			}
			Directory *pDirectoryNext = _directoryQue.front();
			_depth = _depthQue.front();
			_directoryQue.pop_front();
			_depthQue.pop_front();
			if (pDirectoryNext->IsContainer()) {
				_pDirectory.reset(pDirectoryNext);
			} else {
				_pDirectory.reset(nullptr);
				pDirectoryChild = pDirectoryNext;
				goto found;
			}
		}
		if (sig.IsSignalled()) return false;
		if (PathMgr::DoesMatchName(_patternSegs[_depth].c_str(),
								pDirectoryChild->GetName(), _ignoreCaseFlag)) {
			bool typeMatchFlag =
					(pDirectoryChild->IsContainer() && _dirFlag) ||
					(!pDirectoryChild->IsContainer() && _fileFlag);
			if (_depth + 1 < _patternSegs.size()) {
				if (pDirectoryChild->IsContainer()) {
					_directoryQue.push_back(Directory::Reference(pDirectoryChild));
					_depthQue.push_back(static_cast<UInt>(_depth + 1));
				}
			} else if (typeMatchFlag) {
				break;
			}
		}
		Directory::Delete(pDirectoryChild);
	}
found:
	if (_statFlag) {
		Object *pObj = pDirectoryChild->GetStatObj(sig);
		if (sig.IsSignalled()) return false;
		if (pObj != nullptr) value = Value(pObj);
	} else {
		value = Value(pDirectoryChild->MakePathName(_addSepFlag));
	}
	Directory::Delete(pDirectoryChild);
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

}
