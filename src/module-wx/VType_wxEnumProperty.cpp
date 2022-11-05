//==============================================================================
// VType_wxEnumProperty.cpp
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

${help.ComposePropertyHelp(wx.EnumProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.EnumProperty, `en)}

${help.ComposeMethodHelp(wx.EnumProperty, `en)}
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
// VType_wxEnumProperty
//------------------------------------------------------------------------------
VType_wxEnumProperty VTYPE_wxEnumProperty("EnumProperty");

void VType_wxEnumProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxEnumProperty
//------------------------------------------------------------------------------
VType& Value_wxEnumProperty::vtype = VTYPE_wxEnumProperty;

String Value_wxEnumProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EnumProperty");
}

Gurax_EndModuleScope(wx)
