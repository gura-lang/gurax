//==============================================================================
// VType_wxRichTextParagraphLayoutBox.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.RichTextParagraphLayoutBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextParagraphLayoutBox, `en)}

${help.ComposeMethodHelp(wx.RichTextParagraphLayoutBox, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRichTextParagraphLayoutBox
//------------------------------------------------------------------------------
VType_wxRichTextParagraphLayoutBox VTYPE_wxRichTextParagraphLayoutBox("RichTextParagraphLayoutBox");

void VType_wxRichTextParagraphLayoutBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextCompositeObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextParagraphLayoutBox
//------------------------------------------------------------------------------
VType& Value_wxRichTextParagraphLayoutBox::vtype = VTYPE_wxRichTextParagraphLayoutBox;

String Value_wxRichTextParagraphLayoutBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextParagraphLayoutBox");
}

Gurax_EndModuleScope(wx)
