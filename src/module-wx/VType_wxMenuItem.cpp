﻿//==============================================================================
// VType_wxMenuItem.cpp
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

${help.ComposePropertyHelp(wx.MenuItem, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MenuItem, `en)}

${help.ComposeMethodHelp(wx.MenuItem, `en)}
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
// VType_wxMenuItem
//------------------------------------------------------------------------------
VType_wxMenuItem VTYPE_wxMenuItem("MenuItem");

void VType_wxMenuItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMenuItem
//------------------------------------------------------------------------------
VType& Value_wxMenuItem::vtype = VTYPE_wxMenuItem;

String Value_wxMenuItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuItem");
}

Gurax_EndModuleScope(wx)
