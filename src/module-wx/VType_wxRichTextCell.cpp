//==============================================================================
// VType_wxRichTextCell.cpp
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
// VType_wxRichTextCell
//------------------------------------------------------------------------------
VType_wxRichTextCell VTYPE_wxRichTextCell("RichTextCell");

void VType_wxRichTextCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextBox, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextCell
//------------------------------------------------------------------------------
VType& Value_wxRichTextCell::vtype = VTYPE_wxRichTextCell;

String Value_wxRichTextCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextCell");
}

Gurax_EndModuleScope(wx)
