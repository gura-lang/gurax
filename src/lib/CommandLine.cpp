//==============================================================================
// CommandLine.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
void CommandLine::AddInfo(Info* pInfo)
{
	_infoOwner.push_back(pInfo);
	_infoMapByKeyLong[pInfo->GetKeyLong()] = pInfo;
	_infoMapByKeyShort[pInfo->GetKeyShort()] = pInfo;
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
				auto iter = _infoMapByKeyLong.find(keyLong);
				pInfo = (iter == _infoMapByKeyLong.end())? nullptr : iter->second;
				if (pInfo == nullptr) {
					strErr = "unknown option ";
					strErr += arg;
					return false;
				}
				if (pInfo->GetType() == Type::Value) {
					stat = STAT_Value;
				} else {
					_map[pInfo->GetKeyLong()] = nullptr;
				}
			} else {
				char keyShort = arg[1];
				if (keyShort == '\0') break;
				auto iter = _infoMapByKeyShort.find(keyShort);
				pInfo = (iter == _infoMapByKeyShort.end())? nullptr : iter->second;
				if (pInfo == nullptr) {
					strErr = "unknown option ";
					strErr += arg;
					return false;
				}
				const char* value = &arg[2];
				if (pInfo->GetType() == Type::Value) {
					if (value[0] == '\0') {
						stat = STAT_Value;
					} else {
						auto iter = _map.find(pInfo->GetKeyLong());
						StringList* pStrList = nullptr;
						if (iter == _map.end()) {
							pStrList = new StringList();
							_map[pInfo->GetKeyLong()] = pStrList;
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
					_map[pInfo->GetKeyLong()] = nullptr;
				}
			}
			argc--;
			for (int iArgTmp = iArg; iArgTmp < argc; iArgTmp++) {
				argv[iArgTmp] = argv[iArgTmp + 1];
			}
		} else if (stat == STAT_Value) {
			const char* value = arg;
			auto iter = _map.find(pInfo->GetKeyLong());
			StringList* pStrList = nullptr;
			if (iter == _map.end()) {
				pStrList = new StringList();
				_map[pInfo->GetKeyLong()] = pStrList;
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

bool CommandLine::IsSet(const char* keyLong)
{
	return _map.find(keyLong) != _map.end();
}

const char* CommandLine::GetString(const char* keyLong, const char* defValue) const
{
	const char* valStr = _GetString(keyLong);
	return (valStr == nullptr)? defValue : valStr;
}

const StringList& CommandLine::GetStringList(const char* keyLong) const
{
	auto iter = _map.find(keyLong);
	if (iter == _map.end()) return StringList::Empty;
	return* iter->second;
}

Int CommandLine::GetInt(const char* keyLong, Int defValue) const
{
	const char* valStr = _GetString(keyLong);
	return (valStr == nullptr)? defValue : static_cast<int>(::strtol(valStr, nullptr, 0));
}

const char* CommandLine::_GetString(const char* keyLong) const
{
	auto iter = _map.find(keyLong);
	return (iter == _map.end())? nullptr : iter->second->front().c_str();
}

}
