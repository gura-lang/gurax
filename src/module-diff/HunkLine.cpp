//==============================================================================
// HunkLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// HunkLine
//------------------------------------------------------------------------------
String HunkLine::TextizeRange_Normal() const
{
	String str;
	str.Printf("%lu", _lineNoOrg);
	if (_nLinesOrg > 1) str.Printf(",%lu", _lineNoOrg + _nLinesOrg - 1);
	str += IsAdd()? "a" : IsDelete()? "d" : IsChange()? "c" : "?";
	str.Printf("%lu", _lineNoNew);
	if (_nLinesNew > 1) str.Printf(",%lu", _lineNoNew + _nLinesNew - 1);
	return str;
}

String HunkLine::TextizeRange_Context() const
{
	String str;
	return str;
}

String HunkLine::TextizeRange_Unified() const
{
	String str;
	str.Printf("-%lu", _lineNoOrg);
	if (_nLinesOrg != 1) str.Printf(",%lu", _nLinesOrg);
	str.Printf(" +%lu", _lineNoNew);
	if (_nLinesNew != 1) str.Printf(",%lu", _nLinesNew);
	return str;
}

String HunkLine::ToString(const StringStyle& ss) const
{
	return "diff.HunkLine";
}

Gurax_EndModuleScope(diff)
