//==============================================================================
// CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
const char* CData::TextizeStart() const
{
	return "<![CDATA[";
}

const char* CData::TextizeEnd() const
{
	return "]]>";
}

bool CData::Compose(Stream& stream) const
{
	stream.Print(TextizeStart());
	if (!GetText().Compose(stream)) return false;
	stream.Print(TextizeEnd());
	return !Error::IsIssued();
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
