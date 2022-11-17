//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

StringSet g_inlineTagNames;

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
void InitInlineTagNames()
{
	const char* inlineTagNames[] = {
		"a",
		"abbr",
		"acronym",
		"b",
		"bdo",
		"big",
		"br",
		"button",
		"cite",
		"code",
		"dfn",
		"em",
		"i",
		"img",
		"input",
		"kbd",
		"label",
		"map",
		"object",
		"q",
		"samp",
		"script",
		"select",
		"small",
		"span",
		"strong",
		"sub",
		"sup",
		"textarea",
		"time",
		"tt",
		"var",
	};
	// initialize constant table
	for (size_t i = 0; i < Gurax_ArraySizeOf(inlineTagNames); i++) {
		g_inlineTagNames.GetSet().insert(inlineTagNames[i]);
	}
}

bool IsInlineTagName(const char* tagName)
{
	if (tagName == nullptr) return false;
	String tagNameLower = String::Lower(tagName);
	return g_inlineTagNames.GetSet().find(tagNameLower) != g_inlineTagNames.GetSet().end();
}

Gurax_EndModuleScope(markdown)
