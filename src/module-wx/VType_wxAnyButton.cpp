//==============================================================================
// VType_wxAnyButton.cpp
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
// wx.AnyButton() {block?} {block?}
Gurax_DeclareConstructorAlias(AnyButton_gurax, "AnyButton")
{
	Declare(VTYPE_wxAnyButton, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AnyButton.");
}

Gurax_ImplementConstructorEx(AnyButton_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxAnyButton::EntityT();
	RefPtr<Value_wxAnyButton> pValue_gurax(new Value_wxAnyButton(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAnyButton
//------------------------------------------------------------------------------
VType_wxAnyButton VTYPE_wxAnyButton("AnyButton");

void VType_wxAnyButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(AnyButton_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAnyButton
//------------------------------------------------------------------------------
VType& Value_wxAnyButton::vtype = VTYPE_wxAnyButton;

String Value_wxAnyButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AnyButton");
}

//------------------------------------------------------------------------------
// Value_wxAnyButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
