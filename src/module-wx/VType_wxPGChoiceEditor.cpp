//==============================================================================
// VType_wxPGChoiceEditor.cpp
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
// VType_wxPGChoiceEditor
//------------------------------------------------------------------------------
VType_wxPGChoiceEditor VTYPE_wxPGChoiceEditor("PGChoiceEditor");

void VType_wxPGChoiceEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGChoiceEditor
//------------------------------------------------------------------------------
VType& Value_wxPGChoiceEditor::vtype = VTYPE_wxPGChoiceEditor;

String Value_wxPGChoiceEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGChoiceEditor");
}

Gurax_EndModuleScope(wx)
