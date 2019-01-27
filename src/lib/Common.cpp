//==============================================================================
// Common.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// MemberMode
//------------------------------------------------------------------------------
MemberMode SymbolToMemberMode(const Symbol* pSymbol)
{
	if (pSymbol->IsIdentical(Gurax_SymbolMark(Period))) return MemberMode::Normal;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonColon))) return MemberMode::MapToList;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonAsterisk))) return MemberMode::MapToIter;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonAnd))) return MemberMode::MapAlong;
	return MemberMode::None;
}

const Symbol* MemberModeToSymbol(MemberMode memberMode)
{
	switch (memberMode) {
	case MemberMode::Normal:	// foo.bar
		return Gurax_SymbolMark(Period);
	case MemberMode::MapToList:	// foo::bar .. map-to-list
		return Gurax_SymbolMark(ColonColon);
	case MemberMode::MapToIter:	// foo:*bar .. map-to-iterator
		return Gurax_SymbolMark(ColonAsterisk);
	case MemberMode::MapAlong:	// foo:&bar .. map-along
		return Gurax_SymbolMark(ColonAnd);
	default:
		return Gurax_SymbolMark(Empty);
	}
}

//------------------------------------------------------------------------------
// SortOrder
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;

const char* StringStyle::_strsComma[2]		{ ", ", "," };
const char* StringStyle::_strsColon[2]		{ ": ", ":" };
const char* StringStyle::_strsSemicolon[2]	{ "; ", ";" };

//------------------------------------------------------------------------------
// Number types
//------------------------------------------------------------------------------

}
