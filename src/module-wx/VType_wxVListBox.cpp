//==============================================================================
// VType_wxVListBox.cpp
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
// VType_wxVListBox
//------------------------------------------------------------------------------
VType_wxVListBox VTYPE_wxVListBox("VListBox");

void VType_wxVListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxVScrolledWindow, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxVListBox
//------------------------------------------------------------------------------
VType& Value_wxVListBox::vtype = VTYPE_wxVListBox;

String Value_wxVListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VListBox");
}

//------------------------------------------------------------------------------
// Value_wxVListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)