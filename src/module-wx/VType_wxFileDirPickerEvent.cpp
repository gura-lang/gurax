﻿//==============================================================================
// VType_wxFileDirPickerEvent.cpp
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

${help.ComposePropertyHelp(wx.FileDirPickerEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileDirPickerEvent, `en)}

${help.ComposeMethodHelp(wx.FileDirPickerEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FileDirPickerEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FileDirPickerEvent, `ja)}

${help.ComposeMethodHelp(wx.FileDirPickerEvent, `ja)}
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
// VType_wxFileDirPickerEvent
//------------------------------------------------------------------------------
VType_wxFileDirPickerEvent VTYPE_wxFileDirPickerEvent("FileDirPickerEvent");

void VType_wxFileDirPickerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFileDirPickerEvent
//------------------------------------------------------------------------------
VType& Value_wxFileDirPickerEvent::vtype = VTYPE_wxFileDirPickerEvent;
EventValueFactoryDeriv<Value_wxFileDirPickerEvent> Value_wxFileDirPickerEvent::eventValueFactory;

String Value_wxFileDirPickerEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileDirPickerEvent");
}

Gurax_EndModuleScope(wx)
