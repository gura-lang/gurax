//==============================================================================
// Common.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Realization of symbol
//------------------------------------------------------------------------------
Gurax_RealizeSymbol(root);
Gurax_RealizeSymbol(refs);
Gurax_RealizeSymbol(type);
Gurax_RealizeSymbol(text);
Gurax_RealizeSymbol(children);
Gurax_RealizeSymbol(url);
Gurax_RealizeSymbol(title);
Gurax_RealizeSymbol(attrs);
Gurax_RealizeSymbol(align);

//------------------------------------------------------------------------------
// utilities
//------------------------------------------------------------------------------
bool IsInlineTagName(const char* tagName)
{
	if (tagName == nullptr) return false;
	//String tagNameLower = Lower(tagName);
	//return g_inlineTagNames.find(tagNameLower) != g_inlineTagNames.end();
	return false;
}

Gurax_EndModuleScope(markdown)
