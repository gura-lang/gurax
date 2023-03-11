﻿//==============================================================================
// VType_wxPGChoiceEditor.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.PGChoiceEditor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGChoiceEditor, `en)}

${help.ComposeMethodHelp(wx.PGChoiceEditor, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.PGChoiceEditor, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.PGChoiceEditor, `ja)}

${help.ComposeMethodHelp(wx.PGChoiceEditor, `ja)}
)""";

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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
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
