//==============================================================================
// VType_wxAuiPanelInfo.cpp
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

${help.ComposePropertyHelp(wxAuiPanelInfo)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxAuiPanelInfo)}

${help.ComposeMethodHelp(wxAuiPanelInfo)}
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
// VType_wxAuiPanelInfo
//------------------------------------------------------------------------------
VType_wxAuiPanelInfo VTYPE_wxAuiPanelInfo("AuiPanelInfo");

void VType_wxAuiPanelInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiPanelInfo
//------------------------------------------------------------------------------
VType& Value_wxAuiPanelInfo::vtype = VTYPE_wxAuiPanelInfo;

String Value_wxAuiPanelInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiPanelInfo");
}

Gurax_EndModuleScope(wx)
