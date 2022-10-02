//==============================================================================
// Document.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
bool Document::Compose(Stream& stream) const
{
	return
		(!HasXmlDecl() || GetXmlDecl().Compose(stream)) &&
		(!HasElementRoot() || GetElementRoot().Compose(stream));
}

String Document::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Document");
}

Gurax_EndModuleScope(xml)
