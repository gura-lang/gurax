﻿//==============================================================================
// VType_wxOutputStream.cpp
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

${help.ComposePropertyHelp(wx.OutputStream, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.OutputStream, `en)}

${help.ComposeMethodHelp(wx.OutputStream, `en)}
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
// VType_wxOutputStream
//------------------------------------------------------------------------------
VType_wxOutputStream VTYPE_wxOutputStream("OutputStream");

void VType_wxOutputStream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxStreamBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxOutputStream
//------------------------------------------------------------------------------
VType& Value_wxOutputStream::vtype = VTYPE_wxOutputStream;

String Value_wxOutputStream::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.OutputStream");
}

Gurax_EndModuleScope(wx)
