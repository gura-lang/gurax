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
	const char* str = _str.c_str();
	if (_doneFlag) return nullptr;
	if (_cnt == 0) {
		RefPtr<Value> pValue(new Value_String(str + _idx));
		_idx = _len;
		return pValue.release();
	} else if (_idx >= _len) {
		_doneFlag = true;
		return new Value_String(String::Empty);
	}
	int rtn = ::onig_search(_pPattern->GetRegex(),
							reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(str + _len),
							reinterpret_cast<const OnigUChar*>(str + _idx),
							reinterpret_cast<const OnigUChar*>(str + _len),
							_region.get(), ONIG_OPTION_NONE);
	RefPtr<Value> pValue;
	if (rtn >= 0) {
		if (rtn < _idx || _region->num_regs == 0 || _region->end[0] < _idx) {
			IssueError_Onigmo();
			return nullptr;
		}
		if (_region->end[0] == _idx) {
			pValue.reset(new Value_String(str + _idx));
			_doneFlag = true;
		} else {
			pValue.reset(new Value_String(String(str + _idx, rtn - _idx)));
			_idx = _region->end[0];
		}
	} else if (rtn == ONIG_MISMATCH) {
		pValue.reset(new Value_String(str + _idx));
		_idx = _len;
		_doneFlag = true;
	} else { // error
		IssueError_Onigmo(rtn);
		return nullptr;
	}
	if (_cnt > 0) _cnt--;
	return pValue.release();
}

String Iterator_Split::ToString(const StringStyle& ss) const
{
	return "re.Split";
}

//-----------------------------------------------------------------------------
// Iterator_Scan
//-----------------------------------------------------------------------------
Iterator_Scan::Iterator_Scan(Pattern* pPattern, StringReferable* pStr, int pos, int posEnd) :
	_pPattern(pPattern), _pStr(pStr), _len(static_cast<int>(pStr->GetStringSTL().size()))
{
	const String& str = GetStringSTL();
	_idx = static_cast<int>(str.CalcCharOffset(pos));
	_idxEnd = (posEnd < 0)? _len : static_cast<int>(str.CalcCharOffset(posEnd));
}

Value* Iterator_Scan::DoNextValue()
{
	if (_idx >= _idxEnd) return nullptr;
	const char* str = GetString();
	OnigRegion_Ptr region(::onig_region_new());
	int rtn = ::onig_search(_pPattern->GetRegex(),
							reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(str + _len),
							reinterpret_cast<const OnigUChar*>(str + _idx),
							reinterpret_cast<const OnigUChar*>(str + _idxEnd),
							region.get(), ONIG_OPTION_NONE);
	if (rtn >= 0) {
		if (rtn < _idx || region->num_regs == 0 || region->end[0] < _idx) {
			IssueError_Onigmo();
			return nullptr;
		}
		if (region->end[0] == _idx) return nullptr;
		_idx = region->end[0];
		return new Value_Match(new Match(_pPattern->Reference(), region.release(), GetStringReferable().Reference()));
	} else if (rtn == ONIG_MISMATCH) {
		_idx = _idxEnd;
		return nullptr;
	} else { // error
		IssueError_Onigmo(rtn);
		return nullptr;
	}
}

String Iterator_Scan::ToString(const StringStyle& ss) const
{
	return "re.Scan";
}

//-----------------------------------------------------------------------------
// Iterator_Grep
//-----------------------------------------------------------------------------
Iterator_Grep::Iterator_Grep(Iterator* pIteratorSrc, Pattern* pPattern) :
	_pIteratorSrc(pIteratorSrc), _pPattern(pPattern)
{
}

Value* Iterator_Grep::DoNextValue()
{
	for (;;) {
		RefPtr<Value> pValue(_pIteratorSrc->NextValue());
		if (!pValue) break;
		RefPtr<Match> pMatch;
		if (pValue->IsType(VTYPE_String)) {
			pMatch.reset(_pPattern->CreateMatch(dynamic_cast<Value_String&>(*pValue).GetString()));
		} else {
			pMatch.reset(_pPattern->CreateMatch(pValue->ToString().c_str()));
		}
		if (pMatch) return new Value_Match(pMatch.release());
	}
	return nullptr;
}

String Iterator_Grep::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += "re.Grep:";
	rtn += _pIteratorSrc->ToString();
	return rtn;
}

//-----------------------------------------------------------------------------
// Iterator_Group
//-----------------------------------------------------------------------------
Iterator_Group::Iterator_Group(Match* pMatch) : _pMatch(pMatch), _iGroup(1)
{
}

Value* Iterator_Group::DoNextValue()
{
	if (_iGroup < _pMatch->CountGroups()) {
		RefPtr<Value> pValue(new Value_Group(_pMatch->CreateGroup(_iGroup)));
		_iGroup++;
		return pValue.release();
	}
	return nullptr;
}

String Iterator_Group::ToString(const StringStyle& ss) const
{
	return "re.Group:";
}

Gurax_EndModuleScope(re)
