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
Gurax_DeclareConstructor(MenuBar)
{
	Declare(VTYPE_wxMenuBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.MenuBar` instance.");
}

Gurax_ImplementConstructor(MenuBar)
{
	// Function body
	auto pEntity = new Value_wxMenuBar::EntityT();
	RefPtr<Value_wxMenuBar> pValue(new Value_wxMenuBar(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MenuBar#Append(menu as wx.Menu, title as String)
Gurax_DeclareMethod(wxMenuBar, Append)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(wxMenuBar, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntityPtr();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	wxMenu* menu = args.Pick<Value_wxMenu>().GetEntityPtr();
	const char* title = args.PickString();
	// Function body
	bool rtn = pEntity->Append(menu, title);
	return new Value_Bool(rtn);
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
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(MenuBar));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMenuBar, Append));
	// Assignment of property
	//Assign(Gurax_CreateProperty(wxMenuBar, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxMenuBar
//------------------------------------------------------------------------------
VType& Value_wxMenuBar::vtype = VTYPE_wxMenuBar;

String Value_wxMenuBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuBar");
}

//------------------------------------------------------------------------------
// Value_wxMenuBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
