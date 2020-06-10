//==============================================================================
// Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetSymbolQuoted()).c_str());
}

}
