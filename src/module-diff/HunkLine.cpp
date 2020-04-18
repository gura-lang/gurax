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

String HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
