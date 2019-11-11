//==============================================================================
// Common.h
//==============================================================================
#ifndef GURAX_MODULE_MARKDOWN_COMMON_H
#define GURAX_MODULE_MARKDOWN_COMMON_H
#include <gurax.h>

#define ArraySizeOf(x) (sizeof(x) / sizeof(x[0]))

Gurax_BeginModuleScope(markdown)

//------------------------------------------------------------------------------
// Constant
//------------------------------------------------------------------------------
const int WIDTH_Tab = 4;
const int INDENT_CodeBlock = 4;

//------------------------------------------------------------------------------
// Declaration of symbol
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
enum Align { None, Left, Center, Right };

using AlignList = std::vector<Align>;

//------------------------------------------------------------------------------
// Utilities
//------------------------------------------------------------------------------
bool IsInlineTagName(const char* tagName);
inline bool IsTagNameFirst(char ch) { return String::IsAlpha(ch); }
inline bool IsTagNameFollower(char ch) { return String::IsAlpha(ch) || String::IsDigit(ch) || ch == '.'; }

Gurax_EndModuleScope(markdown)

#endif
