﻿//==============================================================================
// VType_wxHtmlListBox.cpp
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

${help.ComposePropertyHelp(wx.HtmlListBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlListBox, `en)}

${help.ComposeMethodHelp(wx.HtmlListBox, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HtmlListBox#GetFileSystem() {block?}
Gurax_DeclareMethodAlias(wxHtmlListBox, GetFileSystem_gurax, "GetFileSystem")
{
	Declare(VTYPE_wxFileSystem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHtmlListBox, GetFileSystem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileSystem(
		pEntity_gurax->GetFileSystem()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlListBox
//------------------------------------------------------------------------------
VType_wxHtmlListBox VTYPE_wxHtmlListBox("HtmlListBox");

void VType_wxHtmlListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxVListBox, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHtmlListBox, GetFileSystem_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHtmlListBox
//------------------------------------------------------------------------------
VType& Value_wxHtmlListBox::vtype = VTYPE_wxHtmlListBox;

String Value_wxHtmlListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlListBox");
}

//------------------------------------------------------------------------------
// Value_wxHtmlListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
