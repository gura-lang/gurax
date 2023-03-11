﻿//==============================================================================
// VType_wxRichTextContextMenuPropertiesInfo.cpp
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

${help.ComposePropertyHelp(wx.RichTextContextMenuPropertiesInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextContextMenuPropertiesInfo, `en)}

${help.ComposeMethodHelp(wx.RichTextContextMenuPropertiesInfo, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RichTextContextMenuPropertiesInfo, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RichTextContextMenuPropertiesInfo, `ja)}

${help.ComposeMethodHelp(wx.RichTextContextMenuPropertiesInfo, `ja)}
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
// VType_wxRichTextContextMenuPropertiesInfo
//------------------------------------------------------------------------------
VType_wxRichTextContextMenuPropertiesInfo VTYPE_wxRichTextContextMenuPropertiesInfo("RichTextContextMenuPropertiesInfo");

void VType_wxRichTextContextMenuPropertiesInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextContextMenuPropertiesInfo
//------------------------------------------------------------------------------
VType& Value_wxRichTextContextMenuPropertiesInfo::vtype = VTYPE_wxRichTextContextMenuPropertiesInfo;

String Value_wxRichTextContextMenuPropertiesInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextContextMenuPropertiesInfo");
}

Gurax_EndModuleScope(wx)
