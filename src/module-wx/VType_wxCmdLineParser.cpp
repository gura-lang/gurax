//==============================================================================
// VType_wxCmdLineParser.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
// VType_wxCmdLineParser
//------------------------------------------------------------------------------
VType_wxCmdLineParser VTYPE_wxCmdLineParser("CmdLineParser");

void VType_wxCmdLineParser::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCmdLineParser
//------------------------------------------------------------------------------
VType& Value_wxCmdLineParser::vtype = VTYPE_wxCmdLineParser;

String Value_wxCmdLineParser::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CmdLineParser");
}

Gurax_EndModuleScope(wx)
