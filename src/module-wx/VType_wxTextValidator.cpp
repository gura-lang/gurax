﻿//==============================================================================
// VType_wxTextValidator.cpp
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

${help.ComposePropertyHelp(wx.TextValidator, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TextValidator, `en)}

${help.ComposeMethodHelp(wx.TextValidator, `en)}
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
// VType_wxTextValidator
//------------------------------------------------------------------------------
VType_wxTextValidator VTYPE_wxTextValidator("TextValidator");

void VType_wxTextValidator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxValidator, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxTextValidator
//------------------------------------------------------------------------------
VType& Value_wxTextValidator::vtype = VTYPE_wxTextValidator;

String Value_wxTextValidator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TextValidator");
}

//------------------------------------------------------------------------------
// Value_wxTextValidator::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
