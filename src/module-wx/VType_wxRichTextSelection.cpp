﻿//==============================================================================
// VType_wxRichTextSelection.cpp
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

${help.ComposePropertyHelp(wx.RichTextSelection, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextSelection, `en)}

${help.ComposeMethodHelp(wx.RichTextSelection, `en)}
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
// VType_wxRichTextSelection
//------------------------------------------------------------------------------
VType_wxRichTextSelection VTYPE_wxRichTextSelection("RichTextSelection");

void VType_wxRichTextSelection::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextSelection
//------------------------------------------------------------------------------
VType& Value_wxRichTextSelection::vtype = VTYPE_wxRichTextSelection;

String Value_wxRichTextSelection::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextSelection");
}

Gurax_EndModuleScope(wx)
