//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(DeclCaller* pDeclCaller, Attribute* pAttr) :
	_pDeclCaller(pDeclCaller), _pAttr(pAttr)
{
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	return rtn;
}

}
