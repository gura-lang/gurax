//==============================================================================
// module-markdown.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_H
#define GURAX_MODULE_MARKDOWN_H
#include <gurax.h>
#include "Document.h"
#include "Item.h"
#include "VType_Document.h"
#include "VType_Item.h"

Gurax_BeginModuleHeader(markdown)

#if 0
//------------------------------------------------------------------------------
// Utilities
//------------------------------------------------------------------------------
bool IsInlineTagName(const char *tagName);

//------------------------------------------------------------------------------
// symbols
//------------------------------------------------------------------------------
Gurax_DeclareUserSymbol(root);
Gurax_DeclareUserSymbol(refs);
Gurax_DeclareUserSymbol(type);
Gurax_DeclareUserSymbol(text);
Gurax_DeclareUserSymbol(children);
Gurax_DeclareUserSymbol(url);
Gurax_DeclareUserSymbol(title);
Gurax_DeclareUserSymbol(attrs);
Gurax_DeclareUserSymbol(align);

//------------------------------------------------------------------------------
// Align
//------------------------------------------------------------------------------
enum Align {
	ALIGN_None, ALIGN_Left, ALIGN_Center, ALIGN_Right
};

typedef std::vector<Align> AlignList;
#endif

Gurax_EndModuleHeader(markdown)

#endif
