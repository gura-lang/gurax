//==============================================================================
// VType_wxSingoeChoiceDialog.cpp
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
// VType_wxSingoeChoiceDialog
//------------------------------------------------------------------------------
VType_wxSingoeChoiceDialog VTYPE_wxSingoeChoiceDialog("SingoeChoiceDialog");

void VType_wxSingoeChoiceDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSingoeChoiceDialog
//------------------------------------------------------------------------------
VType& Value_wxSingoeChoiceDialog::vtype = VTYPE_wxSingoeChoiceDialog;

String Value_wxSingoeChoiceDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SingoeChoiceDialog");
}

//------------------------------------------------------------------------------
// Value_wxSingoeChoiceDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)