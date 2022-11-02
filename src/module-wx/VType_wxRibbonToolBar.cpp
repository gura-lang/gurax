//==============================================================================
// VType_wxRibbonToolBar.cpp
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

${help.ComposePropertyHelp(wxRibbonToolBar)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRibbonToolBar)}

${help.ComposeMethodHelp(wxRibbonToolBar)}
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
// VType_wxRibbonToolBar
//------------------------------------------------------------------------------
VType_wxRibbonToolBar VTYPE_wxRibbonToolBar("RibbonToolBar");

void VType_wxRibbonToolBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRibbonToolBar
//------------------------------------------------------------------------------
VType& Value_wxRibbonToolBar::vtype = VTYPE_wxRibbonToolBar;

String Value_wxRibbonToolBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonToolBar");
}

//------------------------------------------------------------------------------
// Value_wxRibbonToolBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
