//==============================================================================
// VType_wxMultiChoiceProperty.cpp
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

${help.ComposePropertyHelp(wx.MultiChoiceProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MultiChoiceProperty, `en)}

${help.ComposeMethodHelp(wx.MultiChoiceProperty, `en)}
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
// VType_wxMultiChoiceProperty
//------------------------------------------------------------------------------
VType_wxMultiChoiceProperty VTYPE_wxMultiChoiceProperty("MultiChoiceProperty");

void VType_wxMultiChoiceProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMultiChoiceProperty
//------------------------------------------------------------------------------
VType& Value_wxMultiChoiceProperty::vtype = VTYPE_wxMultiChoiceProperty;

String Value_wxMultiChoiceProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MultiChoiceProperty");
}

Gurax_EndModuleScope(wx)
