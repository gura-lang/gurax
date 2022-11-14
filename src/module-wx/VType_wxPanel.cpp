﻿//==============================================================================
// VType_wxPanel.cpp
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

${help.ComposePropertyHelp(wx.Panel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Panel, `en)}

${help.ComposeMethodHelp(wx.Panel, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Panel(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Panel_gurax, "Panel")
{
	Declare(VTYPE_wxPanel, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.Panel.
)**");
}

Gurax_ImplementConstructorEx(Panel_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTAB_TRAVERSAL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPanelNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxPanel::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxPanel> pValue_gurax(new Value_wxPanel(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Panel#AcceptsFocus()
Gurax_DeclareMethodAlias(wxPanel, AcceptsFocus_gurax, "AcceptsFocus")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, AcceptsFocus_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->AcceptsFocus();
	return new Gurax::Value_Bool(rtn);
}

// wx.Panel#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxPanel, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTAB_TRAVERSAL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPanelNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.Panel#InitDialog()
Gurax_DeclareMethodAlias(wxPanel, InitDialog_gurax, "InitDialog")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, InitDialog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->InitDialog();
	return Gurax::Value::nil();
}

// wx.Panel#Layout()
Gurax_DeclareMethodAlias(wxPanel, Layout_gurax, "Layout")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, Layout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Layout();
	return new Gurax::Value_Bool(rtn);
}

// wx.Panel#OnSysColourChanged(event as wx.SysColourChangedEvent)
Gurax_DeclareMethodAlias(wxPanel, OnSysColourChanged_gurax, "OnSysColourChanged")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("event", VTYPE_wxSysColourChangedEvent, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, OnSysColourChanged_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSysColourChangedEvent& value_event = args_gurax.Pick<Value_wxSysColourChangedEvent>();
	wxSysColourChangedEvent& event = value_event.GetEntity();
	// Function body
	pEntity_gurax->OnSysColourChanged(event);
	return Gurax::Value::nil();
}

// wx.Panel#SetFocus()
Gurax_DeclareMethodAlias(wxPanel, SetFocus_gurax, "SetFocus")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, SetFocus_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SetFocus();
	return Gurax::Value::nil();
}

// wx.Panel#SetFocusIgnoringChildren()
Gurax_DeclareMethodAlias(wxPanel, SetFocusIgnoringChildren_gurax, "SetFocusIgnoringChildren")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPanel, SetFocusIgnoringChildren_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SetFocusIgnoringChildren();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPanel
//------------------------------------------------------------------------------
VType_wxPanel VTYPE_wxPanel("Panel");

void VType_wxPanel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Panel_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPanel, AcceptsFocus_gurax));
	Assign(Gurax_CreateMethod(wxPanel, Create_gurax));
	Assign(Gurax_CreateMethod(wxPanel, InitDialog_gurax));
	Assign(Gurax_CreateMethod(wxPanel, Layout_gurax));
	Assign(Gurax_CreateMethod(wxPanel, OnSysColourChanged_gurax));
	Assign(Gurax_CreateMethod(wxPanel, SetFocus_gurax));
	Assign(Gurax_CreateMethod(wxPanel, SetFocusIgnoringChildren_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPanel
//------------------------------------------------------------------------------
VType& Value_wxPanel::vtype = VTYPE_wxPanel;

String Value_wxPanel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Panel");
}

//------------------------------------------------------------------------------
// Value_wxPanel::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
