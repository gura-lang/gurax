﻿//==============================================================================
// VType_wxRibbonButtonBar.cpp
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

${help.ComposePropertyHelp(wx.RibbonButtonBar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonButtonBar, `en)}

${help.ComposeMethodHelp(wx.RibbonButtonBar, `en)}
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
// VType_wxRibbonButtonBar
//------------------------------------------------------------------------------
VType_wxRibbonButtonBar VTYPE_wxRibbonButtonBar("RibbonButtonBar");

void VType_wxRibbonButtonBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBar
//------------------------------------------------------------------------------
VType& Value_wxRibbonButtonBar::vtype = VTYPE_wxRibbonButtonBar;

String Value_wxRibbonButtonBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonButtonBar");
}

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
