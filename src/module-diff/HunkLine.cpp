//==============================================================================
// HunkLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// HunkLine
//------------------------------------------------------------------------------
void HunkLine::Print(Stream& stream) const
{
#if 0
	const EditList &edits = GetEditList();
	EditList::const_iterator pEdit = edits.begin() + hunk.idxEditBegin;
	EditList::const_iterator pEditEnd = edits.begin() + hunk.idxEditEnd;
	if (hunk.format == FORMAT_Normal) {
		stream.Printf(sig, "%s\n", hunk.TextizeRange_Normal().c_str());
		for ( ; pEdit != pEditEnd; pEdit++) {
			stream.Println(sig, TextizeEdit_Normal(*pEdit).c_str());
			if (sig.IsSignalled()) return false;
		}
	} else if (hunk.format == FORMAT_Context) {

	} else if (hunk.format == FORMAT_Unified) {
		stream.Printf(sig, "@@ %s @@\n", hunk.TextizeRange_Unified().c_str());
		if (sig.IsSignalled()) return false;
		for ( ; pEdit != pEditEnd; pEdit++) {
			stream.Println(sig, TextizeEdit_Unified(*pEdit).c_str());
			if (sig.IsSignalled()) return false;
		}
	}
	return true;
#endif
}

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
