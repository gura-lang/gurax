//==============================================================================
// Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
String Reader::ToString(const StringStyle& ss) const
{
	return String().Format("csv.Reader");
}

Gurax_EndModuleScope(csv)
