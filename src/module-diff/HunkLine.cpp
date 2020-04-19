//==============================================================================
// HunkLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// HunkLine
//------------------------------------------------------------------------------
HunkLine::HunkLine(DiffLine* pDiffLine, size_t iSesElemBegin, size_t iSesElemEnd,
		size_t lineNoOrg, size_t lineNoNew, size_t nLinesOrg, size_t nLinesNew) :
	_pDiffLine(pDiffLine), _iSesElemBegin(iSesElemBegin), _iSesElemEnd(iSesElemEnd),
	_lineNoOrg(lineNoOrg), _lineNoNew(lineNoNew), _nLinesOrg(nLinesOrg), _nLinesNew(nLinesNew) {}

String HunkLine::MakeRangeString() const
{
	String str;
	str.Printf("-%lu", _lineNoOrg);
	if (_nLinesOrg > 1) str.Printf(",%lu", _nLinesOrg);
	str.Printf(" +%lu", _lineNoNew);
	if (_nLinesNew > 1) str.Printf(",%lu", _nLinesNew);
	return str;
}

void HunkLine::Print(Stream& stream) const
{
	stream.Printf("@@ %s @@\n", MakeRangeString().c_str());
	const DiffLine::SesElemVec& sesElems = _pDiffLine->GetSesElems();
	for (size_t iSesElem = _iSesElemBegin; iSesElem != _iSesElemEnd; iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[iSesElem];
		stream.Printf("%s%s\n",
			(sesElem.second.type == dtl::SES_ADD)? SES_MARK_ADD :
			(sesElem.second.type == dtl::SES_DELETE)? SES_MARK_DELETE :
			(sesElem.second.type == dtl::SES_COMMON)? SES_MARK_COMMON : " ",
			sesElem.first.c_str());
	}
}

String HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

//------------------------------------------------------------------------------
// HunkLine::Picker
//------------------------------------------------------------------------------
HunkLine::Picker::Picker(DiffLine* pDiffLine, size_t nLinesCommon) :
	_pDiffLine(pDiffLine), _nLinesCommon(nLinesCommon), _iSesElem(0)
{
}

HunkLine* HunkLine::Picker::NextHunkLine()
{
	DiffLine::SesElemVec& sesElems = _pDiffLine->GetSesElems();
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemTop = _iSesElem;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
		if (sesElem.second.type != dtl::SES_COMMON) break;
	}
	if (_iSesElem >= sesElems.size()) return nullptr;
	size_t iSesElemBegin = (_iSesElem > iSesElemTop + _nLinesCommon)? _iSesElem - _nLinesCommon : iSesElemTop;
	size_t nLines = 0;
	for ( ; _iSesElem < sesElems.size(); _iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[_iSesElem];
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
		const DiffLine::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.beforeIdx > 0) {
			lineNoOrg = sesElem.second.beforeIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.afterIdx > 0) {
			lineNoNew = sesElem.second.afterIdx;
			break;
		}
	}
	for (size_t iSesElem = iSesElemBegin; iSesElem < iSesElemEnd; iSesElem++) {
		const DiffLine::SesElem& sesElem = sesElems[iSesElem];
		if (sesElem.second.type != dtl::SES_ADD) nLinesOrg++;
		if (sesElem.second.type != dtl::SES_DELETE) nLinesNew++;
	}
	return new HunkLine(_pDiffLine->Reference(), iSesElemBegin, iSesElemEnd,
									lineNoOrg, lineNoNew, nLinesOrg, nLinesNew);
}

Gurax_EndModuleScope(diff)
