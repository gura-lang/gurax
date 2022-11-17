﻿//==============================================================================
// VType_wxLongStringProperty.cpp
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

${help.ComposePropertyHelp(wx.LongStringProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.LongStringProperty, `en)}

${help.ComposeMethodHelp(wx.LongStringProperty, `en)}
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
// VType_wxLongStringProperty
//------------------------------------------------------------------------------
VType_wxLongStringProperty VTYPE_wxLongStringProperty("LongStringProperty");

void VType_wxLongStringProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxLongStringProperty
//------------------------------------------------------------------------------
VType& Value_wxLongStringProperty::vtype = VTYPE_wxLongStringProperty;

String Value_wxLongStringProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.LongStringProperty");
}

Gurax_EndModuleScope(wx)
