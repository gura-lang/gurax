//==============================================================================
// StringStyle.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;
const StringStyle StringStyle::StringUnquoted(StringStyle::Flag::StringUnquoted);
const StringStyle StringStyle::SymbolQuoted(StringStyle::Flag::SymbolQuoted);
const StringStyle StringStyle::SymbolQuoted_NilVisible(
				StringStyle::Flag::SymbolQuoted | StringStyle::Flag::NilVisible);

const char* StringStyle::_strsComma[2]		{ ", ", "," };
const char* StringStyle::_strsColon[2]		{ ": ", ":" };
const char* StringStyle::_strsSemicolon[2]	{ "; ", ";" };

void StringStyle::DeclareAttrOpt(Function& func)
{
	func.DeclareAttrOpt(Gurax_Symbol(stringUnquoted));
	func.DeclareAttrOpt(Gurax_Symbol(symbolQuoted));
	func.DeclareAttrOpt(Gurax_Symbol(nilVisible));
	//func.DeclareAttrOpt(Gurax_Symbol(cram));
	//func.DeclareAttrOpt(Gurax_Symbol(multiLine));
	//func.DeclareAttrOpt(Gurax_Symbol(upperCase));
	//func.DeclareAttrOpt(Gurax_Symbol(verbose));
	//func.DeclareAttrOpt(Gurax_Symbol(addrInfo));
}

StringStyle::Flags StringStyle::ToFlags(const Argument& argument)
{
	StringStyle::Flags flags = StringStyle::Flag::None;
	if (argument.IsSet(Gurax_Symbol(stringUnquoted)))	flags |= StringStyle::Flag::StringUnquoted;
	if (argument.IsSet(Gurax_Symbol(symbolQuoted)))		flags |= StringStyle::Flag::SymbolQuoted;
	if (argument.IsSet(Gurax_Symbol(nilVisible)))		flags |= StringStyle::Flag::NilVisible;
	if (argument.IsSet(Gurax_Symbol(cram)))				flags |= StringStyle::Flag::Cram;
	if (argument.IsSet(Gurax_Symbol(multiLine)))		flags |= StringStyle::Flag::MultiLine;
	if (argument.IsSet(Gurax_Symbol(upperCase)))		flags |= StringStyle::Flag::UpperCase;
	if (argument.IsSet(Gurax_Symbol(verbose)))			flags |= StringStyle::Flag::Verbose;
	if (argument.IsSet(Gurax_Symbol(addrInfo)))			flags |= StringStyle::Flag::AddrInfo;
	return flags;
}

}
