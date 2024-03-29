﻿//==============================================================================
// VType_wxDatagramSocket.cpp
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

${help.ComposePropertyHelp(wx.DatagramSocket, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DatagramSocket, `en)}

${help.ComposeMethodHelp(wx.DatagramSocket, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.DatagramSocket, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.DatagramSocket, `ja)}

${help.ComposeMethodHelp(wx.DatagramSocket, `ja)}
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
// VType_wxDatagramSocket
//------------------------------------------------------------------------------
VType_wxDatagramSocket VTYPE_wxDatagramSocket("DatagramSocket");

void VType_wxDatagramSocket::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxSocketBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDatagramSocket
//------------------------------------------------------------------------------
VType& Value_wxDatagramSocket::vtype = VTYPE_wxDatagramSocket;

String Value_wxDatagramSocket::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DatagramSocket");
}

Gurax_EndModuleScope(wx)
