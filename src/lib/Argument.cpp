//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(const Argument& src) : _pAttr(src._pAttr->Reference())
{
}

Argument* Argument::Clone() const
{
	return new Argument(*this);
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

}
