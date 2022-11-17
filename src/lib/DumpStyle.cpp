//==============================================================================
// DumpStyle.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DumpStyle
//------------------------------------------------------------------------------
const DumpStyle DumpStyle::Empty;

DumpStyle::DumpStyle(const Argument& argument, size_t addrOffset) :
				_flags(Flag::None), _nDigitsAddrMin(4), _addrOffset(addrOffset)
{
	if (argument.IsSet(Gurax_Symbol(addr))) _flags |= Flag::AddrInfo;
	if (argument.IsSet(Gurax_Symbol(addr8))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 2;
	}
	if (argument.IsSet(Gurax_Symbol(addr16))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 4;
	}
	if (argument.IsSet(Gurax_Symbol(addr24))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 6;
	}
	if (argument.IsSet(Gurax_Symbol(addr32))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 8;
	}
	if (argument.IsSet(Gurax_Symbol(addr40))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 10;
	}
	if (argument.IsSet(Gurax_Symbol(addr48))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 12;
	}
	if (argument.IsSet(Gurax_Symbol(addr56))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 14;
	}
	if (argument.IsSet(Gurax_Symbol(addr64))) {
		_flags |= Flag::AddrInfo;
		_nDigitsAddrMin = 16;
	}
	if (argument.IsSet(Gurax_Symbol(upper))) _flags |= Flag::UpperCase;
}

void DumpStyle::DeclareAttrOpt(Function& func)
{
	func.DeclareAttrOpt(Gurax_Symbol(addr));
	func.DeclareAttrOpt(Gurax_Symbol(addr8));
	func.DeclareAttrOpt(Gurax_Symbol(addr16));
	func.DeclareAttrOpt(Gurax_Symbol(addr24));
	func.DeclareAttrOpt(Gurax_Symbol(addr32));
	func.DeclareAttrOpt(Gurax_Symbol(addr40));
	func.DeclareAttrOpt(Gurax_Symbol(addr48));
	func.DeclareAttrOpt(Gurax_Symbol(addr56));
	func.DeclareAttrOpt(Gurax_Symbol(addr64));
	func.DeclareAttrOpt(Gurax_Symbol(upper));
}

}
