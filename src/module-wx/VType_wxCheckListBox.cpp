//==============================================================================
// VType_wxCheckListBox.cpp
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
// VType_wxCheckListBox
//------------------------------------------------------------------------------
VType_wxCheckListBox VTYPE_wxCheckListBox("CheckListBox");

void VType_wxCheckListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxListBox, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCheckListBox
//------------------------------------------------------------------------------
VType& Value_wxCheckListBox::vtype = VTYPE_wxCheckListBox;

String Value_wxCheckListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CheckListBox");
}

//------------------------------------------------------------------------------
// Value_wxCheckListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)