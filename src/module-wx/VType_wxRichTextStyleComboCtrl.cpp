//==============================================================================
// VType_wxRichTextStyleComboCtrl.cpp
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

${help.ComposePropertyHelp(wx.RichTextStyleComboCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextStyleComboCtrl, `en)}

${help.ComposeMethodHelp(wx.RichTextStyleComboCtrl, `en)}
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
// VType_wxRichTextStyleComboCtrl
//------------------------------------------------------------------------------
VType_wxRichTextStyleComboCtrl VTYPE_wxRichTextStyleComboCtrl("RichTextStyleComboCtrl");

void VType_wxRichTextStyleComboCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxComboCtrl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleComboCtrl
//------------------------------------------------------------------------------
VType& Value_wxRichTextStyleComboCtrl::vtype = VTYPE_wxRichTextStyleComboCtrl;

String Value_wxRichTextStyleComboCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextStyleComboCtrl");
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleComboCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
