//==============================================================================
// VType_wxFindReplaceDialog.cpp
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
// VType_wxFindReplaceDialog
//------------------------------------------------------------------------------
VType_wxFindReplaceDialog VTYPE_wxFindReplaceDialog("FindReplaceDialog");

void VType_wxFindReplaceDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFindReplaceDialog
//------------------------------------------------------------------------------
VType& Value_wxFindReplaceDialog::vtype = VTYPE_wxFindReplaceDialog;

String Value_wxFindReplaceDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FindReplaceDialog");
}

//------------------------------------------------------------------------------
// Value_wxFindReplaceDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
