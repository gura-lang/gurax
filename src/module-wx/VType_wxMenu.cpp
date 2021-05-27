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
Gurax_DeclareConstructor(Menu)
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Menu` instance.");
}

Gurax_ImplementConstructor(Menu)
{
	// Function body
	auto pEntity = new Value_wxMenu::EntityT();
	RefPtr<Value_wxMenu> pValue(new Value_wxMenu(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Menu#Append(id as Number, item? as String, helpString? as String, kind? as Number)
Gurax_DeclareMethod(wxMenu, Append)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("item", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("helpString", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("kind", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(wxMenu, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	int id = args.PickNumber<int>();
	const char* item = args.IsValid()? args.PickString() : "";
	const char* helpString = args.IsValid()? args.PickString() : "";
	wxItemKind kind = args.IsValid()? args.PickNumber<wxItemKind>() : wxITEM_NORMAL;
	// Function body
	wxMenuItem* rtn = pEntity->Append(id, item, helpString, kind);
	return new Value_wxMenuItem(rtn);
}

// wx.Menu#AppendSeparator()
Gurax_DeclareMethod(wxMenu, AppendSeparator)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(wxMenu, AppendSeparator)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Function body
	wxMenuItem* rtn = pEntity->AppendSeparator();
	return new Value_wxMenuItem(rtn);
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
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Menu));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMenu, Append));
	Assign(Gurax_CreateMethod(wxMenu, AppendSeparator));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Menu, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxMenu
//------------------------------------------------------------------------------
VType& Value_wxMenu::vtype = VTYPE_wxMenu;

String Value_wxMenu::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Menu");
}

//------------------------------------------------------------------------------
// Value_wxMenu::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
