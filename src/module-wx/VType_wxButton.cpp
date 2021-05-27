//==============================================================================
// VType_wxButton.cpp
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
// wx.Button(parent as wx.Window, id as Number, label? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructor(Button)
{
	Declare(VTYPE_wxButton, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Button` instance.");
}

Gurax_ImplementConstructor(Button)
{
	// Argument
	ArgPicker args(argument);
	wxWindow* parent = args.IsValid()? args.Pick<Value_wxWindow>().GetEntity() : nullptr;
	wxWindowID id = args.PickNumber<wxWindowID>();
	const char* label = args.IsValid()? args.PickString() : "";
	const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args.IsValid()? args.PickNumber<long>() : 0;
	const wxValidator& validator = args.IsValid()? *args.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args.IsValid()? args.PickString() : wxButtonNameStr;
	// Function body
	auto pEntity = new Value_wxButton::EntityT(parent, id, label, pos, size, style, validator, name);
	RefPtr<Value_wxButton> pValue(new Value_wxButton(pEntity));
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
// VType_wxButton
//------------------------------------------------------------------------------
VType_wxButton VTYPE_wxButton("Button");

void VType_wxButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(Button));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Button, SetMenuBar));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Button, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxButton
//------------------------------------------------------------------------------
VType& Value_wxButton::vtype = VTYPE_wxButton;

String Value_wxButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Button");
}

//------------------------------------------------------------------------------
// Value_wxButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
