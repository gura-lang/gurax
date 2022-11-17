//==============================================================================
// Hunk.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// Hunk
//------------------------------------------------------------------------------
Hunk::Hunk(Diff* pDiff, size_t iSesElemBegin, size_t iSesElemEnd,
		size_t lineNoOrg, size_t lineNoNew, size_t nLinesOrg, size_t nLinesNew) :
	_pDiff(pDiff), _iSesElemBegin(iSesElemBegin), _iSesElemEnd(iSesElemEnd),
	_lineNoOrg(lineNoOrg), _lineNoNew(lineNoNew), _nLinesOrg(nLinesOrg), _nLinesNew(nLinesNew) {}

String Hunk::MakeRangeString() const
{
	String str;
	str.Format("-%lu", _lineNoOrg);
	if (_nLinesOrg > 1) str.Format(",%lu", _nLinesOrg);
	str.Format(" +%lu", _lineNoNew);
	if (_nLinesNew > 1) str.Format(",%lu", _nLinesNew);
	return str;
}

String Hunk::ToString(const StringStyle& ss) const
{
	return "diff.Hunk";
}

//------------------------------------------------------------------------------
// Hunk::Picker
//------------------------------------------------------------------------------
Hunk::Picker::Picker(Diff* pDiff, size_t nLinesCommon) :
	_pDiff(pDiff), _nLinesCommon(nLinesCommon), _iSesElem(0)
{
}

Hunk* Hunk::Picker::NextHunk()
{
	Diff::SesElemVec& sesElems = _pDiff->GetSesElems();
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemTop = _iSesElem;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type != dtl::SES_COMMON) break;
	}
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemBegin = (_iSesElem > iSesElemTop + _nLinesCommon)? _iSesElem - _nLinesCommon : iSesElemTop;
	size_t nLines = 0;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type == dtl::SES_COMMON) {
			if (_nLinesCommon == 0) break;
			nLines++;
			if (nLines >= _nLinesCommon * 2) {
				_iSesElem = _iSesElem + 1 - _nLinesCommon;
				break;
			}
		} else {
			nLines = 0;
		}
	}
	size_t iSesElemEnd = _iSesElem;
	size_t lineNoOrg = 0, lineNoNew = 0;
	size_t nLinesOrg = 0, nLinesNew = 0;
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.beforeIdx > 0) {
			lineNoOrg = sesElem.second.beforeIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.afterIdx > 0) {
			lineNoNew = sesElem.second.afterIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const Diff::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.type != dtl::SES_ADD) nLinesOrg++;
		if (sesElem.second.type != dtl::SES_DELETE) nLinesNew++;
	}
	return new Hunk(_pDiff->Reference(), iSesElemBegin, iSesElemEnd,
									lineNoOrg, lineNoNew, nLinesOrg, nLinesNew);
}

Gurax_EndModuleScope(diff)
