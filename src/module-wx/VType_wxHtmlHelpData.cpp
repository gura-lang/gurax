//==============================================================================
// VType_wxHtmlHelpData.cpp
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
// VType_wxHtmlHelpData
//------------------------------------------------------------------------------
VType_wxHtmlHelpData VTYPE_wxHtmlHelpData("HtmlHelpData");

void VType_wxHtmlHelpData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlHelpData
//------------------------------------------------------------------------------
VType& Value_wxHtmlHelpData::vtype = VTYPE_wxHtmlHelpData;

String Value_wxHtmlHelpData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlHelpData");
}

Gurax_EndModuleScope(wx)