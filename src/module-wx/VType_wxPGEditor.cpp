﻿//==============================================================================
// VType_wxPGEditor.cpp
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

${help.ComposePropertyHelp(wx.PGEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGEditor, `en)}

${help.ComposeMethodHelp(wx.PGEditor, `en)}
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
// VType_wxPGEditor
//------------------------------------------------------------------------------
VType_wxPGEditor VTYPE_wxPGEditor("PGEditor");

void VType_wxPGEditor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGEditor
//------------------------------------------------------------------------------
VType& Value_wxPGEditor::vtype = VTYPE_wxPGEditor;

String Value_wxPGEditor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGEditor");
}

Gurax_EndModuleScope(wx)
