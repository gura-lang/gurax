//==============================================================================
// VType_wxColourPickerCtrl.cpp
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
// VType_wxColourPickerCtrl
//------------------------------------------------------------------------------
VType_wxColourPickerCtrl VTYPE_wxColourPickerCtrl("ColourPickerCtrl");

void VType_wxColourPickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxColourPickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxColourPickerCtrl::vtype = VTYPE_wxColourPickerCtrl;

String Value_wxColourPickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourPickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxColourPickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)