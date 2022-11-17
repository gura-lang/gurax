//==============================================================================
// Document.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Document
//------------------------------------------------------------------------------
Value* Document::Path(const char* path) const
{
	const Element* pElement = &GetElementRoot();
	if (*path == '/') path++;
	if (::strcmp(pElement->GetName(), Node::ExtractField(&path).c_str()) != 0) return nullptr;
	return pElement->Path(path);
}

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
