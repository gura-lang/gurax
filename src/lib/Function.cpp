//==============================================================================
// Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
String Function::MakeFullName() const
{
	return GetName();
}

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
