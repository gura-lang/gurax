//==============================================================================
// VType_wxAuiTabArt.cpp
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

${help.ComposePropertyHelp(wxAuiTabArt)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxAuiTabArt)}

${help.ComposeMethodHelp(wxAuiTabArt)}
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
// VType_wxAuiTabArt
//------------------------------------------------------------------------------
VType_wxAuiTabArt VTYPE_wxAuiTabArt("AuiTabArt");

void VType_wxAuiTabArt::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiTabArt
//------------------------------------------------------------------------------
VType& Value_wxAuiTabArt::vtype = VTYPE_wxAuiTabArt;

String Value_wxAuiTabArt::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiTabArt");
}

Gurax_EndModuleScope(wx)
