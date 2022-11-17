//==============================================================================
// XmlDecl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// XmlDecl
//------------------------------------------------------------------------------
String XmlDecl::Textize() const
{
	String str;
	str = "<?xml";
	if (_pVersion) str.Format(" version=\"%s\"", _pVersion->c_str());
	if (_pEncoding) str.Format(" encoding=\"%s\"", _pEncoding->c_str());
	if (_standalone >= 0) str.Format(" standalone=\"%s\"", _standalone? "yes" : "no");
	str += "?>";
	return str;
}

bool XmlDecl::Compose(Stream& stream) const
{
	stream.Print(Textize().c_str());
	stream.Print("\n");
	return !Error::IsIssued();
}

Value* XmlDecl::CreateValue() const
{
	return new Value_XmlDecl(Reference());
}

String XmlDecl::ToString(const StringStyle& ss) const
{
	return String().Format("xml.XmlDecl");
}

Gurax_EndModuleScope(xml)
