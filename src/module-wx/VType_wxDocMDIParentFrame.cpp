﻿//==============================================================================
// VType_wxDocMDIParentFrame.cpp
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

${help.ComposePropertyHelp(wx.DocMDIParentFrame, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DocMDIParentFrame, `en)}

${help.ComposeMethodHelp(wx.DocMDIParentFrame, `en)}
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
// VType_wxDocMDIParentFrame
//------------------------------------------------------------------------------
VType_wxDocMDIParentFrame VTYPE_wxDocMDIParentFrame("DocMDIParentFrame");

void VType_wxDocMDIParentFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxMDIParentFrame, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDocMDIParentFrame
//------------------------------------------------------------------------------
VType& Value_wxDocMDIParentFrame::vtype = VTYPE_wxDocMDIParentFrame;

String Value_wxDocMDIParentFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DocMDIParentFrame");
}

//------------------------------------------------------------------------------
// Value_wxDocMDIParentFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
