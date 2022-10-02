//==============================================================================
// XmlDecl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// XmlDecl
//------------------------------------------------------------------------------
bool XmlDecl::Compose(Stream& stream) const
{
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
