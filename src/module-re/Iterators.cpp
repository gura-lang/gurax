//==============================================================================
// Iterators.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//-----------------------------------------------------------------------------
// Iterator_Split
//-----------------------------------------------------------------------------
Iterator_Split::Iterator_Split(Pattern* pPattern, const String& str, int cntMax) :
	_pPattern(pPattern), _str(str), _cnt(cntMax), _idx(0),
	_len(static_cast<int>(str.size())), _doneFlag(false), _region(::onig_region_new())
{
}

Value* Iterator_Split::DoNextValue()
{
#if 0
	Signal& sig = env.GetSignal();
	const char* str = _str.c_str();
	if (_doneFlag) return false;
	if (_cnt == 0) {
		value = Value(str + _idx);
		_idx = _len;
		return true;
	} else if (_idx >= _len) {
		value = Value("");
		_doneFlag = true;
		return true;
	}
	int rtn = ::onig_search(_pPattern->GetRegex(),
							reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(str + _len),
							reinterpret_cast<const OnigUChar*>(str + _idx),
							reinterpret_cast<const OnigUChar*>(str + _len),
							_region.get(), ONIG_OPTION_NONE);
	if (rtn >= 0) {
		if (rtn < _idx || _region->num_regs == 0 || _region->end[0] < _idx) {
			SetError_FailInOniguruma(sig);
			return false;
		}
		if (_region->end[0] == _idx) {
			value = Value(str + _idx);
			_doneFlag = true;
			return true;
		}
		value = Value(String(str + _idx, rtn - _idx));
		_idx = _region->end[0];
	} else if (rtn == ONIG_MISMATCH) {
		value = Value(str + _idx);
		_idx = _len;
		_doneFlag = true;
	} else { // error
		SetError_OnigurumaError(sig, rtn);
		return false;
	}
	if (_cnt > 0) _cnt--;
	return true;
#endif
	return Value::nil();
}

String Iterator_Split::ToString(const StringStyle& ss) const
{
	return String("<iterator:re.split>");
}

#if 0
//-----------------------------------------------------------------------------
// Iterator_Scan
//-----------------------------------------------------------------------------
Iterator_Scan::Iterator_Scan(Pattern* pPattern, const String& str, int pos, int posEnd) :
		_pPattern(pPattern), _str(str),
		_len(static_cast<int>(str.size())), _region(::onig_region_new())
{
	_idx = static_cast<int>(CalcCharOffset(str.c_str(), pos));
	_idxEnd = (posEnd < 0)? _len : static_cast<int>(CalcCharOffset(str.c_str(), posEnd));
}

Value* Iterator_Split::DoNextValue()
{
	Signal& sig = env.GetSignal();
	if (_idx >= _idxEnd) return false;
	const char* str = _str.c_str();
	int rtn = ::onig_search(_pPattern->GetRegex(),
							reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(str + _len),
							reinterpret_cast<const OnigUChar*>(str + _idx),
							reinterpret_cast<const OnigUChar*>(str + _idxEnd),
							_region.get(), ONIG_OPTION_NONE);
	if (rtn >= 0) {
		if (rtn < _idx || _region->num_regs == 0 || _region->end[0] < _idx) {
			SetError_FailInOniguruma(sig);
			return false;
		}
		if (_region->end[0] == _idx) {
			return false;
		}
		Object_match* pObj = new Object_match();
		if (!pObj->SetMatchInfo(str, _pPattern->GetRegex(), _region.get(), 0)) {
			SetError_FailInOniguruma(sig);
			delete pObj;
			return false;
		}
		value = Value(pObj);
		_idx = _region->end[0];
	} else if (rtn == ONIG_MISMATCH) {
		value = Value(str + _idx);
		_idx = _idxEnd;
		return false;
	} else { // error
		SetError_OnigurumaError(sig, rtn);
		return false;
	}
	return true;
}

String Iterator_Scan::ToString(const StringStyle& ss) const
{
	return String("<iterator:re.scan>");
}

//-----------------------------------------------------------------------------
// Iterator_Grep
//-----------------------------------------------------------------------------
Iterator_Grep::Iterator_Grep(Iterator* pIteratorSrc, Pattern* pPattern) :
		_pIteratorSrc(pIteratorSrc), _pPattern(pPattern)
{
}

Value* Iterator_Split::DoNextValue()
{
	Signal& sig = env.GetSignal();
	const int pos = 0, posEnd = -1;
	while (_pIteratorSrc->Next(env, value)) {
		String str = value.ToString(false);
		if (Error::IsIssued()) return false;
		value = DoMatch(env, sig,
					_pPattern->GetRegex(), str.c_str(), pos, posEnd);
		if (Error::IsIssued()) return false;
		if (value.IsValid()) return true;
	}
	return false;
}

String Iterator_Grep::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "<iterator:re.grep:";
	rtn += _pIteratorSrc->ToString();
	rtn += ">";
	return rtn;
}

//-----------------------------------------------------------------------------
// Iterator_Group
//-----------------------------------------------------------------------------
Iterator_Group::Iterator_Group(Match* pMatch) : _pMatch(pMatch), _iGroup(1)
{
}

Value* Iterator_Split::DoNextValue()
{
	const GroupList& groupList = _pMatch->GetGroupList();
	if (_iGroup < groupList.size()) {
		value = Value(new Object_group(groupList[_iGroup]));
		_iGroup++;
		return true;
	}
	return false;
}

String Iterator_Group::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "<iterator:re.group:";
	rtn += ">";
	return rtn;
}
#endif

Gurax_EndModuleScope(re)
