//==============================================================================
// StringStyle.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;
const StringStyle StringStyle::Bracket(StringStyle::Flag::Bracket);
const StringStyle StringStyle::Unbracket(StringStyle::Flag::Unbracket);
const StringStyle StringStyle::QuoteString(StringStyle::Flag::QuoteString);
const StringStyle StringStyle::QuoteSymbol(StringStyle::Flag::QuoteSymbol);
const StringStyle StringStyle::Quote_NilVisible(
	StringStyle::Flag::QuoteString | StringStyle::Flag::QuoteSymbol |
	StringStyle::Flag::NilVisible);
const StringStyle StringStyle::Quote_InvalidVisible(
	StringStyle::Flag::QuoteString | StringStyle::Flag::QuoteSymbol |
	StringStyle::Flag::NilVisible | StringStyle::Flag::UndefVisible);
const StringStyle StringStyle::Cram(StringStyle::Flag::Cram);

const char* StringStyle::_strsComma[2]		{ ", ", "," };
const char* StringStyle::_strsColon[2]		{ ": ", ":" };
const char* StringStyle::_strsSemicolon[2]	{ "; ", ";" };

void StringStyle::DeclareAttrOpt(Function& func)
{
	func.DeclareAttrOpt(Gurax_Symbol(bracket));
	func.DeclareAttrOpt(Gurax_Symbol(unbracket));
	func.DeclareAttrOpt(Gurax_Symbol(quote));
	func.DeclareAttrOpt(Gurax_Symbol(quoteString));
	func.DeclareAttrOpt(Gurax_Symbol(quoteSymbol));
	func.DeclareAttrOpt(Gurax_Symbol(nilVisible));
	func.DeclareAttrOpt(Gurax_Symbol(cram));
	func.DeclareAttrOpt(Gurax_Symbol(multiLine));
	func.DeclareAttrOpt(Gurax_Symbol(verbose));
}

StringStyle::Flags StringStyle::ToFlags(const Argument& argument)
{
	StringStyle::Flags flags = StringStyle::Flag::None;
	if (argument.IsSet(Gurax_Symbol(bracket)))		flags |= StringStyle::Flag::Bracket;
	if (argument.IsSet(Gurax_Symbol(unbracket)))	flags |= StringStyle::Flag::Unbracket;
	if (argument.IsSet(Gurax_Symbol(quote))) {
		flags |= StringStyle::Flag::QuoteString | StringStyle::Flag::QuoteSymbol;
	}
	if (argument.IsSet(Gurax_Symbol(quoteString)))	flags |= StringStyle::Flag::QuoteString;
	if (argument.IsSet(Gurax_Symbol(quoteSymbol)))	flags |= StringStyle::Flag::QuoteSymbol;
	if (argument.IsSet(Gurax_Symbol(nilVisible)))	flags |= StringStyle::Flag::NilVisible;
	if (argument.IsSet(Gurax_Symbol(cram)))			flags |= StringStyle::Flag::Cram;
	if (argument.IsSet(Gurax_Symbol(multiLine)))	flags |= StringStyle::Flag::MultiLine;
	if (argument.IsSet(Gurax_Symbol(verbose)))		flags |= StringStyle::Flag::Verbose;
	return flags;
}

}
