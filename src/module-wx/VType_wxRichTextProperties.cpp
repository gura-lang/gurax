//==============================================================================
// VType_wxRichTextProperties.cpp
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

${help.ComposePropertyHelp(wx.RichTextProperties, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextProperties, `en)}

${help.ComposeMethodHelp(wx.RichTextProperties, `en)}
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
// VType_wxRichTextProperties
//------------------------------------------------------------------------------
VType_wxRichTextProperties VTYPE_wxRichTextProperties("RichTextProperties");

void VType_wxRichTextProperties::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextProperties
//------------------------------------------------------------------------------
VType& Value_wxRichTextProperties::vtype = VTYPE_wxRichTextProperties;

String Value_wxRichTextProperties::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextProperties");
}

Gurax_EndModuleScope(wx)
