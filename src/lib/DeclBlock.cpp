//==============================================================================
// DeclBlock.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclBlock
//------------------------------------------------------------------------------
DeclBlock::DeclBlock() : _pSymbol(Symbol::Empty), _pOccur(&Occur::Zero), _flags(Flag::None)
{
}

String DeclBlock::FlagsToString(UInt32 flags)
{
	String rtn;
	for (UInt32 flag = 1; flags; flag <<= 1, flags >>= 1) {
		if (flags & 1) {
			rtn += ':';
			rtn += FlagToSymbol(flag)->GetName();
		}
	}
	return rtn;
}

String DeclBlock::ToString(const StringStyle& ss) const
{
	String rtn;
	if (GetFlags() & Flag::Quote) rtn += '`';
	rtn += GetSymbol()->GetName();
	rtn += GetOccur().GetMarker();
	return rtn;
}

//------------------------------------------------------------------------------
// DeclBlock::Occur
//------------------------------------------------------------------------------
const DeclBlock::Occur DeclBlock::Occur::Invalid	("");
const DeclBlock::Occur DeclBlock::Occur::Zero		("");
const DeclBlock::Occur DeclBlock::Occur::Once		("");
const DeclBlock::Occur DeclBlock::Occur::ZeroOrOnce	("?");

}
