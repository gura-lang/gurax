//==============================================================================
// VType_Menu.cpp
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
// wx.Menu() {block?}
Gurax_DeclareConstructor(Menu)
{
	Declare(VTYPE_Menu, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Menu` instance.");
}

Gurax_ImplementConstructor(Menu)
{
	// Function body
	auto pEntity = new Value_Menu::EntityT();
	RefPtr<Value_Menu> pValue(new Value_Menu(pEntity));
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
// VType_Menu
//------------------------------------------------------------------------------
VType_Menu VTYPE_Menu("Menu");

void VType_Menu::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Menu));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Menu, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Menu, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Menu
//------------------------------------------------------------------------------
VType& Value_Menu::vtype = VTYPE_Menu;

String Value_Menu::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Menu");
}

//------------------------------------------------------------------------------
// Value_Menu::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
