//==============================================================================
// VType_wxFontPickerCtrl.cpp
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
// VType_wxFontPickerCtrl
//------------------------------------------------------------------------------
VType_wxFontPickerCtrl VTYPE_wxFontPickerCtrl("FontPickerCtrl");

void VType_wxFontPickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFontPickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxFontPickerCtrl::vtype = VTYPE_wxFontPickerCtrl;

String Value_wxFontPickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontPickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxFontPickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)