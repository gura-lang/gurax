//==============================================================================
// VType_wxHyperlinkCtrl.cpp
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
// VType_wxHyperlinkCtrl
//------------------------------------------------------------------------------
VType_wxHyperlinkCtrl VTYPE_wxHyperlinkCtrl("HyperlinkCtrl");

void VType_wxHyperlinkCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkCtrl
//------------------------------------------------------------------------------
VType& Value_wxHyperlinkCtrl::vtype = VTYPE_wxHyperlinkCtrl;

String Value_wxHyperlinkCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HyperlinkCtrl");
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
