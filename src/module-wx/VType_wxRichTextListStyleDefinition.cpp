//==============================================================================
// VType_wxRichTextListStyleDefinition.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
// VType_wxRichTextListStyleDefinition
//------------------------------------------------------------------------------
VType_wxRichTextListStyleDefinition VTYPE_wxRichTextListStyleDefinition("RichTextListStyleDefinition");

void VType_wxRichTextListStyleDefinition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextParagraphStyleDefinition, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextListStyleDefinition
//------------------------------------------------------------------------------
VType& Value_wxRichTextListStyleDefinition::vtype = VTYPE_wxRichTextListStyleDefinition;

String Value_wxRichTextListStyleDefinition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextListStyleDefinition");
}

Gurax_EndModuleScope(wx)
