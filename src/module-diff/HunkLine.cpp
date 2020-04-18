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

String HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
