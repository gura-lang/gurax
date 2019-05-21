//==============================================================================
// DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DateTime
//------------------------------------------------------------------------------
String DateTime::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("%04d-%02d-%02d %02d:%02d:%02d.%03d",
			   GetYear(), GetMonth(), GetDay(), GetHour(), GetMin(), GetSec(), GetUSec() / 1000);
	return str;
}

}
