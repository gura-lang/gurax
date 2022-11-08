//==============================================================================
// VType_wxNumericPropertyValidator.cpp
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

${help.ComposePropertyHelp(wx.NumericPropertyValidator, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.NumericPropertyValidator, `en)}

${help.ComposeMethodHelp(wx.NumericPropertyValidator, `en)}
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
// VType_wxNumericPropertyValidator
//------------------------------------------------------------------------------
VType_wxNumericPropertyValidator VTYPE_wxNumericPropertyValidator("NumericPropertyValidator");

void VType_wxNumericPropertyValidator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxTextValidator, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxNumericPropertyValidator
//------------------------------------------------------------------------------
VType& Value_wxNumericPropertyValidator::vtype = VTYPE_wxNumericPropertyValidator;

String Value_wxNumericPropertyValidator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.NumericPropertyValidator");
}

//------------------------------------------------------------------------------
// Value_wxNumericPropertyValidator::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
