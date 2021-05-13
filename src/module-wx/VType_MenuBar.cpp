//==============================================================================
// VType_MenuBar.cpp
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
// wx.MenuBar() {block?}
Gurax_DeclareConstructor(MenuBar)
{
	Declare(VTYPE_MenuBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.MenuBar` instance.");
}

Gurax_ImplementConstructor(MenuBar)
{
	// Function body
	auto pEntity = new Value_MenuBar::EntityT();
	RefPtr<Value_MenuBar> pValue(new Value_MenuBar(pEntity));
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
// VType_MenuBar
//------------------------------------------------------------------------------
VType_MenuBar VTYPE_MenuBar("MenuBar");

void VType_MenuBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Window, Flag::Mutable, Gurax_CreateConstructor(MenuBar));
	// Assignment of method
	// Assignment of property
	//Assign(Gurax_CreateProperty(MenuBar, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MenuBar
//------------------------------------------------------------------------------
VType& Value_MenuBar::vtype = VTYPE_MenuBar;

String Value_MenuBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuBar");
}

//------------------------------------------------------------------------------
// Value_MenuBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
