//==============================================================================
// VType_wxIconBundle.cpp
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

${help.ComposePropertyHelp(wxIconBundle, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxIconBundle, `en)}

${help.ComposeMethodHelp(wxIconBundle, `en)}
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
// VType_wxIconBundle
//------------------------------------------------------------------------------
VType_wxIconBundle VTYPE_wxIconBundle("IconBundle");

void VType_wxIconBundle::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxIconBundle
//------------------------------------------------------------------------------
VType& Value_wxIconBundle::vtype = VTYPE_wxIconBundle;

String Value_wxIconBundle::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.IconBundle");
}

Gurax_EndModuleScope(wx)
