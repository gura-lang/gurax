//==============================================================================
// CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
String CData::TextizeStart() const
{
	return "<![CDATA[";
}

String CData::TextizeEnd() const
{
	return "]]>";
}

void CData::Compose(Stream& stream) const
{
}

Value* CData::CreateValue() const
{
	return new Value_CData(Reference());
}

String CData::ToString(const StringStyle& ss) const
{
	return String().Format("xml.CData");
}

Gurax_EndModuleScope(xml)
