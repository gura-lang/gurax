//==============================================================================
// VType_wxFilePickerCtrl.cpp
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
// VType_wxFilePickerCtrl
//------------------------------------------------------------------------------
VType_wxFilePickerCtrl VTYPE_wxFilePickerCtrl("FilePickerCtrl");

void VType_wxFilePickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFilePickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxFilePickerCtrl::vtype = VTYPE_wxFilePickerCtrl;

String Value_wxFilePickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FilePickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxFilePickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
