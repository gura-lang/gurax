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

void StringStyle::DeclareAttrOpt(Function& func)
{
	//func.DeclareAttrOpt(Gurax_Symbol(asSource));
	//func.DeclareAttrOpt(Gurax_Symbol(asValue));
	//func.DeclareAttrOpt(Gurax_Symbol(cram));
	//func.DeclareAttrOpt(Gurax_Symbol(multiLine));
	//func.DeclareAttrOpt(Gurax_Symbol(upperCase));
	//func.DeclareAttrOpt(Gurax_Symbol(verbose));
	func.DeclareAttrOpt(Gurax_Symbol(formatter));
	//func.DeclareAttrOpt(Gurax_Symbol(addrInfo));
	func.DeclareAttrOpt(Gurax_Symbol(nilVisible));
}

StringStyle::Flags StringStyle::ToFlags(const Argument& argument)
{
	StringStyle::Flags flags = StringStyle::Flag::None;
	if (argument.IsSet(Gurax_Symbol(asSource)))		flags |= StringStyle::Flag::AsSource;
	if (argument.IsSet(Gurax_Symbol(asValue)))		flags |= StringStyle::Flag::AsValue;
	if (argument.IsSet(Gurax_Symbol(cram)))			flags |= StringStyle::Flag::Cram;
	if (argument.IsSet(Gurax_Symbol(multiLine)))	flags |= StringStyle::Flag::MultiLine;
	if (argument.IsSet(Gurax_Symbol(upperCase)))	flags |= StringStyle::Flag::UpperCase;
	if (argument.IsSet(Gurax_Symbol(verbose)))		flags |= StringStyle::Flag::Verbose;
	if (argument.IsSet(Gurax_Symbol(formatter)))	flags |= StringStyle::Flag::Formatter;
	if (argument.IsSet(Gurax_Symbol(addrInfo)))		flags |= StringStyle::Flag::AddrInfo;
	if (argument.IsSet(Gurax_Symbol(nilVisible)))	flags |= StringStyle::Flag::NilVisible;
	return flags;
}

}
