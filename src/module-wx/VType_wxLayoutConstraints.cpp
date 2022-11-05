//==============================================================================
// VType_wxLayoutConstraints.cpp
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

${help.ComposePropertyHelp(wx.LayoutConstraints, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.LayoutConstraints, `en)}

${help.ComposeMethodHelp(wx.LayoutConstraints, `en)}
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
// VType_wxLayoutConstraints
//------------------------------------------------------------------------------
VType_wxLayoutConstraints VTYPE_wxLayoutConstraints("LayoutConstraints");

void VType_wxLayoutConstraints::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxLayoutConstraints
//------------------------------------------------------------------------------
VType& Value_wxLayoutConstraints::vtype = VTYPE_wxLayoutConstraints;

String Value_wxLayoutConstraints::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.LayoutConstraints");
}

Gurax_EndModuleScope(wx)
