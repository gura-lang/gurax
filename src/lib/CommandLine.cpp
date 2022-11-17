//==============================================================================
// CommandLine.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
CommandLine::CommandLine() : argc(0), argv(nullptr)
{
}

CommandLine::~CommandLine()
{
	delete[] argv;
}

CommandLine& CommandLine::AddOpt(Opt* pOpt)
{
	_optOwner.push_back(pOpt);
	_optMapByKeyLong[pOpt->GetKeyLong()] = pOpt;
	if (pOpt->GetKeyShort()) _optMapByKeyShort[pOpt->GetKeyShort()] = pOpt;
	return *this;
}

bool CommandLine::Parse(int _argc, const char* _argv[])
{
	enum class Stat { Key, Value };
	Stat stat = Stat::Key;
	const Opt* pOpt = nullptr;
	auto SetBool = [this](const char* keyLong) {
		_map[keyLong] = nullptr;
	};
	auto FeedValue = [this](const Opt* pOpt, const char* value, bool longFlag) {
		if (pOpt->IsTypeInt()) {
			char* p;
			::strtol(value, &p, 0);
			if (p == value || *p != '\0') {
				_strErr.Format("option %s expects an integer number", pOpt->MakeKeyArg(longFlag).c_str());
				return false;
			}
		}
		auto iter = _map.find(pOpt->GetKeyLong());
		StringList* pStrList = nullptr;
		if (iter == _map.end()) {
			pStrList = new StringList();
			_map[pOpt->GetKeyLong()] = pStrList;
		} else if (pOpt->IsMulti()) {
			pStrList = iter->second;
		} else {
			_strErr.Format("option %s cannot accept multiple values", pOpt->MakeKeyArg(longFlag).c_str());
			return false;
		}
		pStrList->push_back(value);
		return true;
	};
	auto ShiftArg = [](int& argc, const char* argv[], int iArg) {
		argc--;
		for ( ; iArg < argc; iArg++) argv[iArg] = argv[iArg + 1];
	};
	this->argc = _argc;
	this->argv = new const char*[this->argc];
	for (int iArg = 0; iArg < this->argc; iArg++) this->argv[iArg] = _argv[iArg];
	_strErr.clear();
	for (int iArg = 1; iArg < this->argc; ) {
		const char* arg = this->argv[iArg];
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
					_strErr.Format("unknown option --%s", keyLong.c_str());
					return false;
				}
				if (pOpt->IsTypeBool()) {
					SetBool(pOpt->GetKeyLong());
				} else if (pOpt->IsTypeString() || pOpt->IsTypeInt()) {
					if (!value) {
						_strErr.Format("option --%s requires a value", keyLong.c_str());;
						return false;
					} else if (!FeedValue(pOpt, value, true)) return false;
				}
			} else { // short-option
				char keyShort = arg[1];
				if (keyShort == '\0') break;
				auto iter = _optMapByKeyShort.find(keyShort);
				pOpt = (iter == _optMapByKeyShort.end())? nullptr : iter->second;
				if (pOpt == nullptr) {
					_strErr.Format("unknown option -%c", keyShort);
					return false;
				}
				const char* value = &arg[2];
				if (pOpt->IsTypeBool()) {
					if (*value != '\0') {
						_strErr.Format("unknown option -%c", keyShort);;
						return false;
					}
					SetBool(pOpt->GetKeyLong());
				} else if (pOpt->IsTypeString() || pOpt->IsTypeInt()) {
					if (*value == '\0') {
						stat = Stat::Value;
					} else if (!FeedValue(pOpt, value, false)) return false;
				}
			}
			ShiftArg(this->argc, this->argv, iArg);
		} else if (stat == Stat::Value) {
			if (!FeedValue(pOpt, arg, false)) return false;
			ShiftArg(this->argc, this->argv, iArg);
			stat = Stat::Key;
		}
	}
	if (stat == Stat::Value) {
		_strErr.Format("option -%c requires a value", pOpt->GetKeyShort());
		return false;
	}
	return true;
}

bool CommandLine::IsSpecified(const char* keyLong) const
{
	return _map.find(keyLong) != _map.end();
}

bool CommandLine::GetBool(const char* keyLong) const
{
	return IsSpecified(keyLong);
}

const char* CommandLine::GetString(const char* keyLong, const char* defValue) const
{
	const char* str = _GetString(keyLong);
	return (str == nullptr)? defValue : str;
}

const StringList& CommandLine::GetStringList(const char* keyLong) const
{
	auto iter = _map.find(keyLong);
	if (iter == _map.end()) return StringList::Empty;
	return* iter->second;
}

Int CommandLine::GetInt(const char* keyLong, Int defValue) const
{
	const char* str = _GetString(keyLong);
	return (str == nullptr)? defValue : static_cast<int>(::strtol(str, nullptr, 0));
}

#if 0
IntList CommandLine::GetIntList(const char* keyLong) const
{
	IntList intList;
	const StringList& strList = GetStringList(keyLong);
	intList.reserve(strList.size());
	for (const String& str : strList) {
		intList.push_back(static_cast<int>(::strtol(str.c_str(), nullptr, 0)));
	}
	return intList;
}
#endif

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
	} else if (GetKeyShort()) {
		str ="-";
		str += GetKeyShort();
	}
	return str;
}

}
