//==============================================================================
// VType_wxStatusBar.cpp
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
// wx.StatusBar() {block?}
Gurax_DeclareConstructorAlias(StatusBar_gurax, "StatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.StatusBar.");
}

Gurax_ImplementConstructorEx(StatusBar_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxStatusBar::EntityT();
	RefPtr<Value_wxStatusBar> pValue_gurax(new Value_wxStatusBar(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStatusBar
//------------------------------------------------------------------------------
VType_wxStatusBar VTYPE_wxStatusBar("StatusBar");

void VType_wxStatusBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StatusBar_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxStatusBar
//------------------------------------------------------------------------------
VType& Value_wxStatusBar::vtype = VTYPE_wxStatusBar;

String Value_wxStatusBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StatusBar");
}

Gurax_EndModuleScope(wx)