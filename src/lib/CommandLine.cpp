//==============================================================================
// CommandLine.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
CommandLine& CommandLine::AddOpt(Opt* pOpt)
{
	_optOwner.push_back(pOpt);
	_optMapByKeyLong[pOpt->GetKeyLong()] = pOpt;
	_optMapByKeyShort[pOpt->GetKeyShort()] = pOpt;
	return *this;
}

bool CommandLine::Parse(int& argc, char* argv[])
{
	enum class Stat { Key, Value };
	Stat stat = Stat::Key;
	const Opt* pOpt = nullptr;
	const char* arg = "";
	_strErr.clear();
	for (int iArg = 1; iArg < argc; ) {
		arg = argv[iArg];
		if (stat == Stat::Key) {
			if (arg[0] != '-') {
				iArg++;
				continue;
			} else if (arg[1] == '-') {
				const char* keyLong = &arg[2];
				auto iter = _optMapByKeyLong.find(keyLong);
				pOpt = (iter == _optMapByKeyLong.end())? nullptr : iter->second;
				if (pOpt == nullptr) {
					_strErr = "unknown option ";
					_strErr += arg;
					return false;
				}
				if (pOpt->IsType(Type::Bool)) {
					_map[pOpt->GetKeyLong()] = nullptr;
				} else if (pOpt->IsType(Type::String)) {
					stat = Stat::Value;
				}
			} else {
				char keyShort = arg[1];
				if (keyShort == '\0') break;
				auto iter = _optMapByKeyShort.find(keyShort);
				pOpt = (iter == _optMapByKeyShort.end())? nullptr : iter->second;
				if (pOpt == nullptr) {
					_strErr = "unknown option ";
					_strErr += arg;
					return false;
				}
				const char* value = &arg[2];
				if (pOpt->IsType(Type::Bool)) {
					if (value[0] != '\0') {
						_strErr = "unknown option ";
						_strErr += arg;
						return false;
					}
					_map[pOpt->GetKeyLong()] = nullptr;
				} else if (pOpt->IsType(Type::String)) {
					if (value[0] == '\0') {
						stat = Stat::Value;
					} else {
						auto iter = _map.find(pOpt->GetKeyLong());
						StringList* pStrList = nullptr;
						if (iter == _map.end()) {
							pStrList = new StringList();
							_map[pOpt->GetKeyLong()] = pStrList;
						} else {
							pStrList = iter->second;
						}
						pStrList->push_back(value);
					}
				}
			}
			argc--;
			for (int iArgTmp = iArg; iArgTmp < argc; iArgTmp++) {
				argv[iArgTmp] = argv[iArgTmp + 1];
			}
		} else if (stat == Stat::Value) {
			const char* value = arg;
			auto iter = _map.find(pOpt->GetKeyLong());
			StringList* pStrList = nullptr;
			if (iter == _map.end()) {
				pStrList = new StringList();
				_map[pOpt->GetKeyLong()] = pStrList;
			} else {
				pStrList = iter->second;
			}
			pStrList->push_back(value);
			argc--;
			for (int iArgTmp = iArg; iArgTmp < argc; iArgTmp++) {
				argv[iArgTmp] = argv[iArgTmp + 1];
			}
			stat = Stat::Key;
		}
	}
	if (stat == Stat::Value) {
		_strErr = "option ";
		_strErr += arg;
		_strErr += " requires a value";
		return false;
	}
	return true;
}

bool CommandLine::GetBool(const char* keyLong)
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
