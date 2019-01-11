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
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonColon))) return MemberMode::MapAlong;
	return MemberMode::None;
}

//------------------------------------------------------------------------------
// SortOrder
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;

//------------------------------------------------------------------------------
// Number types
//------------------------------------------------------------------------------

}
