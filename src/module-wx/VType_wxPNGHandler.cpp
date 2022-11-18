﻿//==============================================================================
// VType_wxPNGHandler.cpp
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

${help.ComposePropertyHelp(wx.PNGHandler, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PNGHandler, `en)}

${help.ComposeMethodHelp(wx.PNGHandler, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PNGHandler() {block?}
Gurax_DeclareConstructorAlias(PNGHandler_gurax, "PNGHandler")
{
	Declare(VTYPE_wxPNGHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(PNGHandler_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPNGHandler(
		wxPNGHandler()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPNGHandler
//------------------------------------------------------------------------------
VType_wxPNGHandler VTYPE_wxPNGHandler("PNGHandler");

void VType_wxPNGHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxImageHandler, Flag::Mutable, Gurax_CreateConstructor(PNGHandler_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPNGHandler
//------------------------------------------------------------------------------
VType& Value_wxPNGHandler::vtype = VTYPE_wxPNGHandler;

String Value_wxPNGHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PNGHandler");
}

Gurax_EndModuleScope(wx)
