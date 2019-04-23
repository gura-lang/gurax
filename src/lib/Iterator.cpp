//==============================================================================
// Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
bool Iterator::MustBeFinite() const
{
	if (IsFinite()) return true;
	Error::Issue(ErrorType::IteratorError, "infinite iterator is unacceptable");
	return false;
}

Iterator* Iterator::Clone() const
{
	//*********************
	return Reference();
}

String Iterator::ToString(const StringStyle& ss) const
{
	String str;
	return str;
}

}
