//==============================================================================
// VType_wxRichTextCompositeObject.cpp
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

${help.ComposePropertyHelp(wx.RichTextCompositeObject, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextCompositeObject, `en)}

${help.ComposeMethodHelp(wx.RichTextCompositeObject, `en)}
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
// VType_wxRichTextCompositeObject
//------------------------------------------------------------------------------
VType_wxRichTextCompositeObject VTYPE_wxRichTextCompositeObject("RichTextCompositeObject");

void VType_wxRichTextCompositeObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRichTextObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextCompositeObject
//------------------------------------------------------------------------------
VType& Value_wxRichTextCompositeObject::vtype = VTYPE_wxRichTextCompositeObject;

String Value_wxRichTextCompositeObject::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextCompositeObject");
}

Gurax_EndModuleScope(wx)
