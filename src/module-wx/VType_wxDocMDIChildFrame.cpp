//==============================================================================
// VType_wxDocMDIChildFrame.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
// VType_wxDocMDIChildFrame
//------------------------------------------------------------------------------
VType_wxDocMDIChildFrame VTYPE_wxDocMDIChildFrame("DocMDIChildFrame");

void VType_wxDocMDIChildFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxMDIChildFrame, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDocMDIChildFrame
//------------------------------------------------------------------------------
VType& Value_wxDocMDIChildFrame::vtype = VTYPE_wxDocMDIChildFrame;

String Value_wxDocMDIChildFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DocMDIChildFrame");
}

//------------------------------------------------------------------------------
// Value_wxDocMDIChildFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
