//==============================================================================
// CommandLine.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
CommandLine::~CommandLine()
{
	for (auto iter : _map) {
		delete iter.second;
	}
}

CommandLine& CommandLine::AddInfo(const Info* infoTbl, int cntInfo)
{
	const Info* pInfo = infoTbl;
	for (int i = 0; i < cntInfo; i++, pInfo++) {
		_infoMapByKeyLong[pInfo->keyLong] = *pInfo;
		_infoMapByKeyShort[pInfo->keyShort] = *pInfo;
	}
	return *this;
}

bool CommandLine::Parse(int& argc, const char* argv[], String& strErr)
{
	enum { STAT_Key, STAT_Value } stat = STAT_Key;
	const Info* pInfo = nullptr;
	const char* arg = "";
	for (int iArg = 1; iArg < argc; ) {
		arg = argv[iArg];
		if (stat == STAT_Key) {
			if (arg[0] != '-') {
				iArg++;
				continue;
			} else if (arg[1] == '-') {
				const char* keyLong = &arg[2];
				InfoMapByKeyLong::iterator iter = _infoMapByKeyLong.find(keyLong);
				pInfo = (iter == _infoMapByKeyLong.end())? nullptr : &iter->second;
				if (pInfo == nullptr) {
					strErr = "unknown option ";
					strErr += arg;
					return false;
				}
				if (pInfo->type == TYPE_Value) {
					stat = STAT_Value;
				} else {
					_map[pInfo->keyLong] = nullptr;
				}
			} else {
				char keyShort = arg[1];
				if (keyShort == '\0') break;
				InfoMapByKeyShort::iterator iter = _infoMapByKeyShort.find(keyShort);
				pInfo = (iter == _infoMapByKeyShort.end())? nullptr : &iter->second;
				if (pInfo == nullptr) {
					strErr = "unknown option ";
					strErr += arg;
					return false;
				}
				const char* value = &arg[2];
				if (pInfo->type == TYPE_Value) {
					if (value[0] == '\0') {
						stat = STAT_Value;
					} else {
						Map::iterator iter = _map.find(pInfo->keyLong);
						StringList* pStrList = nullptr;
						if (iter == _map.end()) {
							pStrList = new StringList();
							_map[pInfo->keyLong] = pStrList;
						} else {
							pStrList = iter->second;
						}
						pStrList->push_back(value);
					}
				} else {
					if (value[0] != '\0') {
						strErr = "unknown option ";
						strErr += arg;
						return false;
					}
					_map[pInfo->keyLong] = nullptr;
				}
			}
			argc--;
			for (int iArgTmp = iArg; iArgTmp < argc; iArgTmp++) {
				argv[iArgTmp] = argv[iArgTmp + 1];
			}
		} else if (stat == STAT_Value) {
			const char* value = arg;
			Map::iterator iter = _map.find(pInfo->keyLong);
			StringList* pStrList = nullptr;
			if (iter == _map.end()) {
				pStrList = new StringList();
				_map[pInfo->keyLong] = pStrList;
			} else {
				pStrList = iter->second;
			}
			pStrList->push_back(value);
			argc--;
			for (int iArgTmp = iArg; iArgTmp < argc; iArgTmp++) {
				argv[iArgTmp] = argv[iArgTmp + 1];
			}
			stat = STAT_Key;
		}
	}
	if (stat == STAT_Value) {
		strErr = "option ";
		strErr += arg;
		strErr += " requires a value";
		return false;
	}
	return true;
}

bool CommandLine::IsSet(const char* key)
{
	return _map.find(key) != _map.end();
}

const char* CommandLine::GetString(const char* key, const char* defValue) const
{
	const char* valStr = _GetString(key);
	return (valStr == nullptr)? defValue : valStr;
}

const StringList& CommandLine::GetStringList(const char* key) const
{
	Map::const_iterator iter = _map.find(key);
	if (iter == _map.end()) return StringList::Empty;
	return* iter->second;
}

Int CommandLine::GetInt(const char* key, Int defValue) const
{
	const char* valStr = _GetString(key);
	return (valStr == nullptr)? defValue : static_cast<int>(::strtol(valStr, nullptr, 0));
}

const char* CommandLine::_GetString(const char* key) const
{
	Map::const_iterator iter = _map.find(key);
	return (iter == _map.end())? nullptr : iter->second->front().c_str();
}

}
