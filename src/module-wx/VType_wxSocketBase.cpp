//==============================================================================
// VType_wxSocketBase.cpp
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

${help.ComposePropertyHelp(wx.SocketBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SocketBase, `en)}

${help.ComposeMethodHelp(wx.SocketBase, `en)}
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
// VType_wxSocketBase
//------------------------------------------------------------------------------
VType_wxSocketBase VTYPE_wxSocketBase("SocketBase");

void VType_wxSocketBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSocketBase
//------------------------------------------------------------------------------
VType& Value_wxSocketBase::vtype = VTYPE_wxSocketBase;

String Value_wxSocketBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SocketBase");
}

Gurax_EndModuleScope(wx)
