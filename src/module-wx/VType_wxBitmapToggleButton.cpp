﻿//==============================================================================
// VType_wxBitmapToggleButton.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.BitmapToggleButton, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BitmapToggleButton, `en)}

${help.ComposeMethodHelp(wx.BitmapToggleButton, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BitmapToggleButton(parent as wx.Window, id as Number, label as wx.Bitmap, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(BitmapToggleButton_gurax, "BitmapToggleButton")
{
	Declare(VTYPE_wxBitmapToggleButton, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.BitmapToggleButton.");
}

Gurax_ImplementConstructorEx(BitmapToggleButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	Value_wxBitmap& value_label = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& label = value_label.GetEntity();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxCheckBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxBitmapToggleButton::EntityT(parent, id, label, pos, size, style, validator, name);
	RefPtr<Value_wxBitmapToggleButton> pValue_gurax(new Value_wxBitmapToggleButton(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBitmapToggleButton
//------------------------------------------------------------------------------
VType_wxBitmapToggleButton VTYPE_wxBitmapToggleButton("BitmapToggleButton");

void VType_wxBitmapToggleButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxToggleButton, Flag::Mutable, Gurax_CreateConstructor(BitmapToggleButton_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxBitmapToggleButton
//------------------------------------------------------------------------------
VType& Value_wxBitmapToggleButton::vtype = VTYPE_wxBitmapToggleButton;

String Value_wxBitmapToggleButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BitmapToggleButton");
}

//------------------------------------------------------------------------------
// Value_wxBitmapToggleButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
