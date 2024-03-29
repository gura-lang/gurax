﻿//==============================================================================
// VType_wxSocketServer.cpp
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

${help.ComposePropertyHelp(wx.SocketServer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SocketServer, `en)}

${help.ComposeMethodHelp(wx.SocketServer, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SocketServer, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SocketServer, `ja)}

${help.ComposeMethodHelp(wx.SocketServer, `ja)}
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
// VType_wxSocketServer
//------------------------------------------------------------------------------
VType_wxSocketServer VTYPE_wxSocketServer("SocketServer");

void VType_wxSocketServer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxSocketBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSocketServer
//------------------------------------------------------------------------------
VType& Value_wxSocketServer::vtype = VTYPE_wxSocketServer;

String Value_wxSocketServer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SocketServer");
}

Gurax_EndModuleScope(wx)
