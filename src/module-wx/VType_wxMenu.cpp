//==============================================================================
// VType_wxMenu.cpp
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
Gurax_DeclareConstructorAlias(Menu_gurax, "Menu")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Menu.");
}

Gurax_ImplementConstructorEx(Menu_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxMenu::EntityT();
	RefPtr<Value_wxMenu> pValue_gurax(new Value_wxMenu(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Menu#Append(id as Number, item? as String, helpString? as String, kind? as Number)
Gurax_DeclareMethodAlias(wxMenu, Append_gurax, "Append")
{
	Declare(VTYPE_wxMenuItem, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("item", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("helpString", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("kind", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxMenu, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	const char* item = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* helpString = args_gurax.IsValid()? args_gurax.PickString() : "";
	wxItemKind kind = args_gurax.IsValid()? args_gurax.PickNumber<wxItemKind>() : wxITEM_NORMAL;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenuItem(
		*pEntity_gurax->Append(id, item, helpString, kind)));
}

// wx.Menu#AppendSeparator()
Gurax_DeclareMethodAlias(wxMenu, AppendSeparator_gurax, "AppendSeparator")
{
	Declare(VTYPE_wxMenuItem, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxMenu, AppendSeparator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenuItem(
		*pEntity_gurax->AppendSeparator()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMenu
//------------------------------------------------------------------------------
VType_wxMenu VTYPE_wxMenu("Menu");

void VType_wxMenu::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Menu_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMenu, Append_gurax));
	Assign(Gurax_CreateMethod(wxMenu, AppendSeparator_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMenu
//------------------------------------------------------------------------------
VType& Value_wxMenu::vtype = VTYPE_wxMenu;

String Value_wxMenu::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Menu");
}

Gurax_EndModuleScope(wx)
