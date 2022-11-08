//==============================================================================
// VType_wxSocketClient.cpp
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

${help.ComposePropertyHelp(wx.SocketClient, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SocketClient, `en)}

${help.ComposeMethodHelp(wx.SocketClient, `en)}
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
// VType_wxSocketClient
//------------------------------------------------------------------------------
VType_wxSocketClient VTYPE_wxSocketClient("SocketClient");

void VType_wxSocketClient::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSocketBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSocketClient
//------------------------------------------------------------------------------
VType& Value_wxSocketClient::vtype = VTYPE_wxSocketClient;

String Value_wxSocketClient::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SocketClient");
}

Gurax_EndModuleScope(wx)
