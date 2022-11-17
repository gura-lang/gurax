﻿//==============================================================================
// VType_wxTextEntry.cpp
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

${help.ComposePropertyHelp(wx.TextEntry, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TextEntry, `en)}

${help.ComposeMethodHelp(wx.TextEntry, `en)}
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
// VType_wxTextEntry
//------------------------------------------------------------------------------
VType_wxTextEntry VTYPE_wxTextEntry("TextEntry");

void VType_wxTextEntry::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxTextEntry
//------------------------------------------------------------------------------
VType& Value_wxTextEntry::vtype = VTYPE_wxTextEntry;

String Value_wxTextEntry::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TextEntry");
}

Gurax_EndModuleScope(wx)
