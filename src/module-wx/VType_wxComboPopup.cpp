//==============================================================================
// VType_wxComboPopup.cpp
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
// VType_wxComboPopup
//------------------------------------------------------------------------------
VType_wxComboPopup VTYPE_wxComboPopup("ComboPopup");

void VType_wxComboPopup::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxComboPopup
//------------------------------------------------------------------------------
VType& Value_wxComboPopup::vtype = VTYPE_wxComboPopup;

String Value_wxComboPopup::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ComboPopup");
}

Gurax_EndModuleScope(wx)