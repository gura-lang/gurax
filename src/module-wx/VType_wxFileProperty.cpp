﻿//==============================================================================
// VType_wxFileProperty.cpp
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

${help.ComposePropertyHelp(wx.FileProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileProperty, `en)}

${help.ComposeMethodHelp(wx.FileProperty, `en)}
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
// VType_wxFileProperty
//------------------------------------------------------------------------------
VType_wxFileProperty VTYPE_wxFileProperty("FileProperty");

void VType_wxFileProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFileProperty
//------------------------------------------------------------------------------
VType& Value_wxFileProperty::vtype = VTYPE_wxFileProperty;

String Value_wxFileProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileProperty");
}

Gurax_EndModuleScope(wx)
