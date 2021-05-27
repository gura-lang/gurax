//==============================================================================
// VType_wxAnyButton.cpp
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
/*
// wx.AnyButton(parent:nil as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructor(AnyButton)
{
	Declare(VTYPE_wxAnyButton, Flag::None);
	DeclareArg("parent", VTYPE_Window, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.AnyButton` instance.");
}

Gurax_ImplementConstructor(AnyButton)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_Window>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* title = args.PickString();
	const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : wxDEFAULT_wxAnyButton_STYLE;
	const char* name = args.IsValid()? args.PickString() : wxAnyButtonNameStr;
	// Function body
	auto pEntity = new Value_wxAnyButton::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxAnyButton> pValue(new Value_wxAnyButton(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}
*/

// wx.AnyButton() {block?}
Gurax_DeclareConstructor(AnyButton)
{
	Declare(VTYPE_wxAnyButton, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.AnyButton` instance.");
}

Gurax_ImplementConstructor(AnyButton)
{
	// Function body
	auto pEntity = new Value_wxAnyButton::EntityT();
	RefPtr<Value_wxAnyButton> pValue(new Value_wxAnyButton(pEntity));
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
// VType_wxAnyButton
//------------------------------------------------------------------------------
VType_wxAnyButton VTYPE_wxAnyButton("AnyButton");

void VType_wxAnyButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Control, Flag::Mutable, Gurax_CreateConstructor(AnyButton));
	// Assignment of method
	//Assign(Gurax_CreateMethod(AnyButton, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(AnyButton, propSkeleton));
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
