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
	if (pOpt->GetKeyShort()) _optMapByKeyShort[pOpt->GetKeyShort()] = pOpt;
	return *this;
}

bool CommandLine::Parse(int& argc, const char* argv[])
{
	enum class Stat { Key, Value };
	Stat stat = Stat::Key;
	const Opt* pOpt = nullptr;
	auto SetBool = [this](const char* keyLong) {
		_map[keyLong] = nullptr;
	};
	auto FeedValue = [this](const Opt* pOpt, const char* value, bool longFlag) {
		if (pOpt->IsType(Type::Int)) {
			char* p;
			::strtol(value, &p, 0);
			if (p == value || *p != '\0') {
				_strErr.Printf("option %s expects an integer number", pOpt->MakeKeyArg(longFlag).c_str());
				return false;
			}
		}
		auto iter = _map.find(pOpt->GetKeyLong());
		StringList* pStrList = nullptr;
		if (iter == _map.end()) {
			pStrList = new StringList();
			_map[pOpt->GetKeyLong()] = pStrList;
		} else {
			pStrList = iter->second;
		}
		pStrList->push_back(value);
		return true;
	};
	auto ShiftArg = [](int& argc, const char* argv[], int iArg) {
		argc--;
		for ( ; iArg < argc; iArg++) argv[iArg] = argv[iArg + 1];
	};
	_strErr.clear();
	for (int iArg = 1; iArg < argc; ) {
		const char* arg = argv[iArg];
		if (stat == Stat::Key) {
			if (arg[0] != '-') { // non-option argument
				break;
			} else if (arg[1] == '-') { // long-option 
				String keyLong;
				const char* p = &arg[2];
				const char* value = ::strchr(p, '=');
				if (value) {
					keyLong = String(p, value);
					value++;
				} else {
					keyLong = String(p);
				}
				auto iter = _optMapByKeyLong.find(keyLong);
				pOpt = (iter == _optMapByKeyLong.end())? nullptr : iter->second;
				if (pOpt == nullptr) {
					_strErr.Printf("unknown option --%s", keyLong.c_str());
					return false;
				}
				if (pOpt->IsType(Type::Bool)) {
					SetBool(pOpt->GetKeyLong());
				} else if (pOpt->IsType(Type::String) || pOpt->IsType(Type::Int)) {
					if (!value) {
						_strErr.Printf("option --%s requires a value", keyLong.c_str());;
						return false;
					} else if (!FeedValue(pOpt, value, true)) return false;
				}
			} else { // short-option
				char keyShort = arg[1];
				if (keyShort == '\0') break;
				auto iter = _optMapByKeyShort.find(keyShort);
				pOpt = (iter == _optMapByKeyShort.end())? nullptr : iter->second;
				if (pOpt == nullptr) {
					_strErr.Printf("unknown option -%c", keyShort);
					return false;
				}
				const char* value = &arg[2];
				if (pOpt->IsType(Type::Bool)) {
					if (*value != '\0') {
						_strErr.Printf("unknown option -%c", keyShort);;
						return false;
					}
					SetBool(pOpt->GetKeyLong());
				} else if (pOpt->IsType(Type::String) || pOpt->IsType(Type::Int)) {
					if (*value == '\0') {
						stat = Stat::Value;
					} else if (!FeedValue(pOpt, value, false)) return false;
				}
			}
			ShiftArg(argc, argv, iArg);
		} else if (stat == Stat::Value) {
			if (!FeedValue(pOpt, arg, false)) return false;
			ShiftArg(argc, argv, iArg);
			stat = Stat::Key;
		}
	}
	if (stat == Stat::Value) {
		_strErr.Printf("option -%c requires a value", pOpt->GetKeyShort());
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

//------------------------------------------------------------------------------
// CommandLine::Opt
//------------------------------------------------------------------------------
String CommandLine::Opt::MakeKeyArg(bool longFlag) const
{
	String str;
	if (longFlag) {
		str = "--";
		str += GetKeyLong();
	} else {
		str ="-";
		str += GetKeyShort();
	}
	return str;
}

}
