//==============================================================================
// VType_wxPasswordEntryDialog.cpp
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
// VType_wxPasswordEntryDialog
//------------------------------------------------------------------------------
VType_wxPasswordEntryDialog VTYPE_wxPasswordEntryDialog("PasswordEntryDialog");

void VType_wxPasswordEntryDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxTextEntryDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPasswordEntryDialog
//------------------------------------------------------------------------------
VType& Value_wxPasswordEntryDialog::vtype = VTYPE_wxPasswordEntryDialog;

String Value_wxPasswordEntryDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PasswordEntryDialog");
}

//------------------------------------------------------------------------------
// Value_wxPasswordEntryDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
