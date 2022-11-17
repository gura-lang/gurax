//==============================================================================
// DeclBlock.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclBlock
//------------------------------------------------------------------------------
DeclBlock::DeclBlock() : _pSymbol(Gurax_Symbol(block)), _pOccur(&Occur::Zero), _flags(Flag::None)
{
}

String DeclBlock::FlagsToString(Flags flags)
{
	String str;
	for (Flags flag = 1; flags; flag <<= 1, flags >>= 1) {
		if (flags & 1) {
			str += ':';
			str += FlagToSymbol(flag)->GetName();
		}
	}
	return str;
}

String DeclBlock::ToString(const StringStyle& ss) const
{
	String str;
	if (GetFlags() & Flag::Quote) str += '`';
	str += GetSymbol()->GetName();
	str += GetOccur().GetMarker();
	return str;
}

//------------------------------------------------------------------------------
// DeclBlock::Occur
//------------------------------------------------------------------------------
const DeclBlock::Occur DeclBlock::Occur::Invalid	("");
const DeclBlock::Occur DeclBlock::Occur::Zero		("");
const DeclBlock::Occur DeclBlock::Occur::Once		("");
const DeclBlock::Occur DeclBlock::Occur::ZeroOrOnce	("?");

}
