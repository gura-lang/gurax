//==============================================================================
// Iterators.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator_Const
//------------------------------------------------------------------------------
String Iterator_Const::ToString(const StringStyle& ss) const
{
	String str;
	str += "Const:";
	str += _pValue->ToString();
	return str;
}

//------------------------------------------------------------------------------
// Iterator_ConstN
//------------------------------------------------------------------------------
String Iterator_ConstN::ToString(const StringStyle& ss) const
{
	String str;
	str += "ConstN:";
	str += _pValue->ToString();
	str += ":n=";
	str += std::to_string(_num);
	return str;
}

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
String Iterator_Each::ToString(const StringStyle& ss) const
{
	String str;
	str += "Each:n=";
	str += std::to_string(GetValueOwner().size());
	return str;
}

}
