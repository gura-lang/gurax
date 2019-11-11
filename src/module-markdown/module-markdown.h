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
Gurax_DeclareSymbol(root);
Gurax_DeclareSymbol(refs);
Gurax_DeclareSymbol(type);
Gurax_DeclareSymbol(text);
Gurax_DeclareSymbol(children);
Gurax_DeclareSymbol(url);
Gurax_DeclareSymbol(title);
Gurax_DeclareSymbol(attrs);
Gurax_DeclareSymbol(align);

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
