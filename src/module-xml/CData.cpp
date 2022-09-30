//==============================================================================
// CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
Value* CData::CreateValue() const
{
	return new Value_CData(Reference());
}

String CData::ToString(const StringStyle& ss) const
{
	return String().Format("xml.CData");
}

Gurax_EndModuleScope(xml)
