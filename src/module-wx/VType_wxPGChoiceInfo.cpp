﻿//==============================================================================
// VType_wxPGChoiceInfo.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.PGChoiceInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGChoiceInfo, `en)}

${help.ComposeMethodHelp(wx.PGChoiceInfo, `en)}
)""";

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
// VType_wxPGChoiceInfo
//------------------------------------------------------------------------------
VType_wxPGChoiceInfo VTYPE_wxPGChoiceInfo("PGChoiceInfo");

void VType_wxPGChoiceInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGChoiceInfo
//------------------------------------------------------------------------------
VType& Value_wxPGChoiceInfo::vtype = VTYPE_wxPGChoiceInfo;

String Value_wxPGChoiceInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGChoiceInfo");
}

Gurax_EndModuleScope(wx)
