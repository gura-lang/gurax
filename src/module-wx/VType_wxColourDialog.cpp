//==============================================================================
// VType_wxColourDialog.cpp
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
// VType_wxColourDialog
//------------------------------------------------------------------------------
VType_wxColourDialog VTYPE_wxColourDialog("ColourDialog");

void VType_wxColourDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxColourDialog
//------------------------------------------------------------------------------
VType& Value_wxColourDialog::vtype = VTYPE_wxColourDialog;

String Value_wxColourDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourDialog");
}

//------------------------------------------------------------------------------
// Value_wxColourDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
