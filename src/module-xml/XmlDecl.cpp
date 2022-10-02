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
	return String().Format("<?xml version=\"%s\" encoding=\"%s\" standalone=\"%s\"?>",
		_version.c_str(), _encoding.c_str(), _standalone? "yes" : "no");
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
