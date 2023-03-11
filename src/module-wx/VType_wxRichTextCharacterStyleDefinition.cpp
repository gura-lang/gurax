﻿//==============================================================================
// VType_wxRichTextCharacterStyleDefinition.cpp
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

${help.ComposePropertyHelp(wx.RichTextCharacterStyleDefinition, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextCharacterStyleDefinition, `en)}

${help.ComposeMethodHelp(wx.RichTextCharacterStyleDefinition, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RichTextCharacterStyleDefinition, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RichTextCharacterStyleDefinition, `ja)}

${help.ComposeMethodHelp(wx.RichTextCharacterStyleDefinition, `ja)}
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
// VType_wxRichTextCharacterStyleDefinition
//------------------------------------------------------------------------------
VType_wxRichTextCharacterStyleDefinition VTYPE_wxRichTextCharacterStyleDefinition("RichTextCharacterStyleDefinition");

void VType_wxRichTextCharacterStyleDefinition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextCharacterStyleDefinition
//------------------------------------------------------------------------------
VType& Value_wxRichTextCharacterStyleDefinition::vtype = VTYPE_wxRichTextCharacterStyleDefinition;

String Value_wxRichTextCharacterStyleDefinition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextCharacterStyleDefinition");
}

Gurax_EndModuleScope(wx)
