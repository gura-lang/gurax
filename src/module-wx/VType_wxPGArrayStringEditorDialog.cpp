//==============================================================================
// VType_wxPGArrayStringEditorDialog.cpp
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
// VType_wxPGArrayStringEditorDialog
//------------------------------------------------------------------------------
VType_wxPGArrayStringEditorDialog VTYPE_wxPGArrayStringEditorDialog("PGArrayStringEditorDialog");

void VType_wxPGArrayStringEditorDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGArrayEditorDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGArrayStringEditorDialog
//------------------------------------------------------------------------------
VType& Value_wxPGArrayStringEditorDialog::vtype = VTYPE_wxPGArrayStringEditorDialog;

String Value_wxPGArrayStringEditorDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGArrayStringEditorDialog");
}

//------------------------------------------------------------------------------
// Value_wxPGArrayStringEditorDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
