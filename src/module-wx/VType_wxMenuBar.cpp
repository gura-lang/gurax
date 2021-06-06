//==============================================================================
// VType_wxMenuBar.cpp
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
Gurax_DeclareConstructorAlias(MenuBar_gurax, "MenuBar")
{
	Declare(VTYPE_wxMenuBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.MenuBar.");
}

Gurax_ImplementConstructorEx(MenuBar_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxMenuBar::EntityT();
	RefPtr<Value_wxMenuBar> pValue_gurax(new Value_wxMenuBar(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MenuBar#Append(menu as wx.Menu, title as String)
Gurax_DeclareMethodAlias(wxMenuBar, Append_gurax, "Append")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxMenuBar, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	const char* title = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->Append(menu, title);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMenuBar
//------------------------------------------------------------------------------
VType_wxMenuBar VTYPE_wxMenuBar("MenuBar");

void VType_wxMenuBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(MenuBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMenuBar, Append_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMenuBar
//------------------------------------------------------------------------------
VType& Value_wxMenuBar::vtype = VTYPE_wxMenuBar;

String Value_wxMenuBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuBar");
}

Gurax_EndModuleScope(wx)
