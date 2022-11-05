//==============================================================================
// VType_wxDirProperty.cpp
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

${help.ComposePropertyHelp(wxDirProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDirProperty, `en)}

${help.ComposeMethodHelp(wxDirProperty, `en)}
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
// VType_wxDirProperty
//------------------------------------------------------------------------------
VType_wxDirProperty VTYPE_wxDirProperty("DirProperty");

void VType_wxDirProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxLongStringProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDirProperty
//------------------------------------------------------------------------------
VType& Value_wxDirProperty::vtype = VTYPE_wxDirProperty;

String Value_wxDirProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DirProperty");
}

Gurax_EndModuleScope(wx)
