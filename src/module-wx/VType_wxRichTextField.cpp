﻿//==============================================================================
// VType_wxRichTextField.cpp
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

${help.ComposePropertyHelp(wx.RichTextField, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextField, `en)}

${help.ComposeMethodHelp(wx.RichTextField, `en)}
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
// VType_wxRichTextField
//------------------------------------------------------------------------------
VType_wxRichTextField VTYPE_wxRichTextField("RichTextField");

void VType_wxRichTextField::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextParagraphLayoutBox, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextField
//------------------------------------------------------------------------------
VType& Value_wxRichTextField::vtype = VTYPE_wxRichTextField;

String Value_wxRichTextField::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextField");
}

Gurax_EndModuleScope(wx)
