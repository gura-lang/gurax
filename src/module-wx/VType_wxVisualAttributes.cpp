//==============================================================================
// VType_wxVisualAttributes.cpp
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

${help.ComposePropertyHelp(wxVisualAttributes, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxVisualAttributes, `en)}

${help.ComposeMethodHelp(wxVisualAttributes, `en)}
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
// VType_wxVisualAttributes
//------------------------------------------------------------------------------
VType_wxVisualAttributes VTYPE_wxVisualAttributes("VisualAttributes");

void VType_wxVisualAttributes::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxVisualAttributes
//------------------------------------------------------------------------------
VType& Value_wxVisualAttributes::vtype = VTYPE_wxVisualAttributes;

String Value_wxVisualAttributes::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VisualAttributes");
}

Gurax_EndModuleScope(wx)
