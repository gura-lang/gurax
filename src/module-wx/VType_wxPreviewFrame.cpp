//==============================================================================
// VType_wxPreviewFrame.cpp
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
// VType_wxPreviewFrame
//------------------------------------------------------------------------------
VType_wxPreviewFrame VTYPE_wxPreviewFrame("PreviewFrame");

void VType_wxPreviewFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFrame, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPreviewFrame
//------------------------------------------------------------------------------
VType& Value_wxPreviewFrame::vtype = VTYPE_wxPreviewFrame;

String Value_wxPreviewFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PreviewFrame");
}

//------------------------------------------------------------------------------
// Value_wxPreviewFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
