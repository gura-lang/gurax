//==============================================================================
// VType_wxRibbonPanel.cpp
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

${help.ComposePropertyHelp(wxRibbonPanel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRibbonPanel, `en)}

${help.ComposeMethodHelp(wxRibbonPanel, `en)}
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
// VType_wxRibbonPanel
//------------------------------------------------------------------------------
VType_wxRibbonPanel VTYPE_wxRibbonPanel("RibbonPanel");

void VType_wxRibbonPanel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRibbonPanel
//------------------------------------------------------------------------------
VType& Value_wxRibbonPanel::vtype = VTYPE_wxRibbonPanel;

String Value_wxRibbonPanel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonPanel");
}

//------------------------------------------------------------------------------
// Value_wxRibbonPanel::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
