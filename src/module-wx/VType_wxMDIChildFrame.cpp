﻿//==============================================================================
// VType_wxMDIChildFrame.cpp
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

${help.ComposePropertyHelp(wx.MDIChildFrame, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MDIChildFrame, `en)}

${help.ComposeMethodHelp(wx.MDIChildFrame, `en)}
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
// VType_wxMDIChildFrame
//------------------------------------------------------------------------------
VType_wxMDIChildFrame VTYPE_wxMDIChildFrame("MDIChildFrame");

void VType_wxMDIChildFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFrame, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMDIChildFrame
//------------------------------------------------------------------------------
VType& Value_wxMDIChildFrame::vtype = VTYPE_wxMDIChildFrame;

String Value_wxMDIChildFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MDIChildFrame");
}

//------------------------------------------------------------------------------
// Value_wxMDIChildFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
