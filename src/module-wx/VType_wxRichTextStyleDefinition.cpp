﻿//==============================================================================
// VType_wxRichTextStyleDefinition.cpp
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

${help.ComposePropertyHelp(wx.RichTextStyleDefinition, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextStyleDefinition, `en)}

${help.ComposeMethodHelp(wx.RichTextStyleDefinition, `en)}
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
// VType_wxRichTextStyleDefinition
//------------------------------------------------------------------------------
VType_wxRichTextStyleDefinition VTYPE_wxRichTextStyleDefinition("RichTextStyleDefinition");

void VType_wxRichTextStyleDefinition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleDefinition
//------------------------------------------------------------------------------
VType& Value_wxRichTextStyleDefinition::vtype = VTYPE_wxRichTextStyleDefinition;

String Value_wxRichTextStyleDefinition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextStyleDefinition");
}

Gurax_EndModuleScope(wx)
