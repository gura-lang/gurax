//==============================================================================
// VType_wxAuiDefaultToolBarArt.cpp
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
// VType_wxAuiDefaultToolBarArt
//------------------------------------------------------------------------------
VType_wxAuiDefaultToolBarArt VTYPE_wxAuiDefaultToolBarArt("AuiDefaultToolBarArt");

void VType_wxAuiDefaultToolBarArt::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAuiToolBarArt, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiDefaultToolBarArt
//------------------------------------------------------------------------------
VType& Value_wxAuiDefaultToolBarArt::vtype = VTYPE_wxAuiDefaultToolBarArt;

String Value_wxAuiDefaultToolBarArt::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiDefaultToolBarArt");
}

Gurax_EndModuleScope(wx)
