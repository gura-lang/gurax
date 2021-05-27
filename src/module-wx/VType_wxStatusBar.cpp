//==============================================================================
// VType_wxStatusBar.cpp
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
Gurax_DeclareConstructor(StatusBar)
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.StatusBar` instance.");
}

Gurax_ImplementConstructor(StatusBar)
{
	// Function body
	auto pEntity = new Value_wxStatusBar::EntityT();
	RefPtr<Value_wxStatusBar> pValue(new Value_wxStatusBar(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
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
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StatusBar));
	// Assignment of method
	//Assign(Gurax_CreateMethod(StatusBar, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(StatusBar, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxStatusBar
//------------------------------------------------------------------------------
VType& Value_wxStatusBar::vtype = VTYPE_wxStatusBar;

String Value_wxStatusBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StatusBar");
}

//------------------------------------------------------------------------------
// Value_wxStatusBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
