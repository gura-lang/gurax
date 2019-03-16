//==============================================================================
// Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += GetSymbol()->GetName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
