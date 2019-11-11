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
//-----------------------------------------------------------------------------
// Utilities
//-----------------------------------------------------------------------------
bool IsInlineTagName(const char *tagName);

//-----------------------------------------------------------------------------
// symbols
//-----------------------------------------------------------------------------
Gura_DeclareUserSymbol(root);
Gura_DeclareUserSymbol(refs);
Gura_DeclareUserSymbol(type);
Gura_DeclareUserSymbol(text);
Gura_DeclareUserSymbol(children);
Gura_DeclareUserSymbol(url);
Gura_DeclareUserSymbol(title);
Gura_DeclareUserSymbol(attrs);
Gura_DeclareUserSymbol(align);

//-----------------------------------------------------------------------------
// Align
//-----------------------------------------------------------------------------
enum Align {
	ALIGN_None, ALIGN_Left, ALIGN_Center, ALIGN_Right
};

typedef std::vector<Align> AlignList;
#endif

Gurax_EndModuleHeader(markdown)

#endif
