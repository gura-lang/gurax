﻿//==============================================================================
// VType_wxPGValidationInfo.cpp
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

${help.ComposePropertyHelp(wx.PGValidationInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGValidationInfo, `en)}

${help.ComposeMethodHelp(wx.PGValidationInfo, `en)}
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
// VType_wxPGValidationInfo
//------------------------------------------------------------------------------
VType_wxPGValidationInfo VTYPE_wxPGValidationInfo("PGValidationInfo");

void VType_wxPGValidationInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGValidationInfo
//------------------------------------------------------------------------------
VType& Value_wxPGValidationInfo::vtype = VTYPE_wxPGValidationInfo;

String Value_wxPGValidationInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGValidationInfo");
}

Gurax_EndModuleScope(wx)
