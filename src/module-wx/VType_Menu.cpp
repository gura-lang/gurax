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
// wx.Menu#Append(id as Number, item? as String, helpString? as String, kind? as Number)
Gurax_DeclareMethod(Menu, Append)
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

Gurax_ImplementMethod(Menu, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	int id = args.PickNumber<int>();
	const char* item = args.IsValid()? args.PickString() : "";
	const char* helpString = args.IsValid()? args.PickString() : "";
	wxItemKind kind = args.IsValid()? args.PickNumber<wxItemKind>() : wxITEM_NORMAL;
	// Function body
	wxMenuItem* rtn = valueThis.GetEntity()->Append(id, item, helpString, kind);
	return Value::nil();
}

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
