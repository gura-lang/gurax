//==============================================================================
// VType_wxHtmlHelpDialog.cpp
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
// VType_wxHtmlHelpDialog
//------------------------------------------------------------------------------
VType_wxHtmlHelpDialog VTYPE_wxHtmlHelpDialog("HtmlHelpDialog");

void VType_wxHtmlHelpDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlHelpDialog
//------------------------------------------------------------------------------
VType& Value_wxHtmlHelpDialog::vtype = VTYPE_wxHtmlHelpDialog;

String Value_wxHtmlHelpDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlHelpDialog");
}

//------------------------------------------------------------------------------
// Value_wxHtmlHelpDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)