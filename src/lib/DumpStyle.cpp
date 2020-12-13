//==============================================================================
// DumpStyle.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DumpStyle
//------------------------------------------------------------------------------
const DumpStyle DumpStyle::Empty;

void DumpStyle::DeclareAttrOpt(Function& func)
{
	func.DeclareAttrOpt(Gurax_Symbol(addr));
	func.DeclareAttrOpt(Gurax_Symbol(upper));
}

DumpStyle::Flags DumpStyle::ToFlags(const Argument& argument)
{
	Flags flags = Flag::None;
	if (argument.IsSet(Gurax_Symbol(addr))) flags |= Flag::AddrInfo;
	if (argument.IsSet(Gurax_Symbol(upper))) flags |= Flag::UpperCase;
	return flags;
}

}
