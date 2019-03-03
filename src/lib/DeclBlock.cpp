//==============================================================================
// DeclBlock.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclBlock
//------------------------------------------------------------------------------
DeclBlock::DeclBlock(const Symbol* pSymbol, const Occur& occur, UInt32 flags) :
	_pSymbol(pSymbol), _occur(occur), _flags(flags)
{
}

String DeclBlock::FlagsToString(UInt32 flags)
{
	String rtn;
	return rtn;
}

String DeclBlock::ToString(const StringStyle& ss) const
{
	String rtn;
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
