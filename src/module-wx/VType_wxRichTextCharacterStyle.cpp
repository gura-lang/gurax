//==============================================================================
// VType_wxRichTextCharacterStyle.cpp
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

${help.ComposePropertyHelp(wx.RichTextCharacterStyle, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextCharacterStyle, `en)}

${help.ComposeMethodHelp(wx.RichTextCharacterStyle, `en)}
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
// VType_wxRichTextCharacterStyle
//------------------------------------------------------------------------------
VType_wxRichTextCharacterStyle VTYPE_wxRichTextCharacterStyle("RichTextCharacterStyle");

void VType_wxRichTextCharacterStyle::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextCharacterStyle
//------------------------------------------------------------------------------
VType& Value_wxRichTextCharacterStyle::vtype = VTYPE_wxRichTextCharacterStyle;

String Value_wxRichTextCharacterStyle::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextCharacterStyle");
}

Gurax_EndModuleScope(wx)
