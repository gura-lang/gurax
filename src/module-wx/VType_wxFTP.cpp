﻿//==============================================================================
// VType_wxFTP.cpp
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

${help.ComposePropertyHelp(wx.FTP, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FTP, `en)}

${help.ComposeMethodHelp(wx.FTP, `en)}
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
// VType_wxFTP
//------------------------------------------------------------------------------
VType_wxFTP VTYPE_wxFTP("FTP");

void VType_wxFTP::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxProtocol, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFTP
//------------------------------------------------------------------------------
VType& Value_wxFTP::vtype = VTYPE_wxFTP;

String Value_wxFTP::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FTP");
}

Gurax_EndModuleScope(wx)
