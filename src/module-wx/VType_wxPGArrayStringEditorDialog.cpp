﻿//==============================================================================
// VType_wxPGArrayStringEditorDialog.cpp
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

${help.ComposePropertyHelp(wx.PGArrayStringEditorDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGArrayStringEditorDialog, `en)}

${help.ComposeMethodHelp(wx.PGArrayStringEditorDialog, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.PGArrayStringEditorDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.PGArrayStringEditorDialog, `ja)}

${help.ComposeMethodHelp(wx.PGArrayStringEditorDialog, `ja)}
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
// VType_wxPGArrayStringEditorDialog
//------------------------------------------------------------------------------
VType_wxPGArrayStringEditorDialog VTYPE_wxPGArrayStringEditorDialog("PGArrayStringEditorDialog");

void VType_wxPGArrayStringEditorDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
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
