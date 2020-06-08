//==============================================================================
// StringStyle.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;
const StringStyle StringStyle::AsValue(StringStyle::Flag::AsValue);
const StringStyle StringStyle::Formatter(StringStyle::Flag::Formatter);
const StringStyle StringStyle::Formatter_NilVisible(
				StringStyle::Flag::Formatter | StringStyle::Flag::NilVisible);

const char* StringStyle::_strsComma[2]		{ ", ", "," };
const char* StringStyle::_strsColon[2]		{ ": ", ":" };
const char* StringStyle::_strsSemicolon[2]	{ "; ", ";" };

//------------------------------------------------------------------------------
// StringStyle::SymbolAssoc_Flag
//------------------------------------------------------------------------------
StringStyle::SymbolAssoc_Flag::SymbolAssoc_Flag()
{
	Assoc(Gurax_Symbol(asSource),	Flag::AsSource);
	Assoc(Gurax_Symbol(asValue),	Flag::AsValue);
	Assoc(Gurax_Symbol(cram),		Flag::Cram);
	Assoc(Gurax_Symbol(multiLine),	Flag::MultiLine);
	Assoc(Gurax_Symbol(upperCase),	Flag::UpperCase);
	Assoc(Gurax_Symbol(verbose),	Flag::Verbose);
	Assoc(Gurax_Symbol(formatter),	Flag::Formatter);
	Assoc(Gurax_Symbol(addrInfo),	Flag::AddrInfo);
	Assoc(Gurax_Symbol(nilVisible),	Flag::NilVisible);
}

}
