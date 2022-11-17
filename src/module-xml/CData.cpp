//==============================================================================
// CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
String CData::Textize() const
{
	String str;
	str += "<![CDATA[";
	str += _text;
	str += "]]>";
	return str;
}

bool CData::Compose(Stream& stream) const
{
	stream.Print("<![CDATA[");
	stream.Print(_text.c_str());
	stream.Print("]]>");
	return !Error::IsIssued();
}

Value* CData::CreateValue() const
{
	return new Value_CData(Reference());
}

String CData::ToString(const StringStyle& ss) const
{
	return String().Format("xml.CData:%s", String::Enquote(GetText(), '\'').c_str());
}

Gurax_EndModuleScope(xml)
