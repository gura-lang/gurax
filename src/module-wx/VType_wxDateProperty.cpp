﻿//==============================================================================
// VType_wxDateProperty.cpp
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

${help.ComposePropertyHelp(wx.DateProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DateProperty, `en)}

${help.ComposeMethodHelp(wx.DateProperty, `en)}
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
// VType_wxDateProperty
//------------------------------------------------------------------------------
VType_wxDateProperty VTYPE_wxDateProperty("DateProperty");

void VType_wxDateProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDateProperty
//------------------------------------------------------------------------------
VType& Value_wxDateProperty::vtype = VTYPE_wxDateProperty;

String Value_wxDateProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DateProperty");
}

Gurax_EndModuleScope(wx)
