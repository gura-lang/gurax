//==============================================================================
// VType_wxUpdateUIEvent.cpp
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

${help.ComposePropertyHelp(wxUpdateUIEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxUpdateUIEvent, `en)}

${help.ComposeMethodHelp(wxUpdateUIEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.UpdateUIEvent#Check(check as Bool)
Gurax_DeclareMethodAlias(wxUpdateUIEvent, Check_gurax, "Check")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("check", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, Check_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool check = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Check(check);
	return Gurax::Value::nil();
}

// wx.UpdateUIEvent#Enable(enable as Bool)
Gurax_DeclareMethodAlias(wxUpdateUIEvent, Enable_gurax, "Enable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, Enable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Enable(enable);
	return Gurax::Value::nil();
}

// wx.UpdateUIEvent#GetChecked()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetChecked_gurax, "GetChecked")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetChecked();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetEnabled()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetEnabled_gurax, "GetEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetEnabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetEnabled();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetSetChecked()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetSetChecked_gurax, "GetSetChecked")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetSetChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetSetChecked();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetSetEnabled()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetSetEnabled_gurax, "GetSetEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetSetEnabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetSetEnabled();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetSetShown()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetSetShown_gurax, "GetSetShown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetSetShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetSetShown();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetSetText()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetSetText_gurax, "GetSetText")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetSetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetSetText();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetShown()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetShown_gurax, "GetShown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetShown();
	return new Gurax::Value_Bool(rtn);
}

// wx.UpdateUIEvent#GetText()
Gurax_DeclareMethodAlias(wxUpdateUIEvent, GetText_gurax, "GetText")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, GetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetText();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.UpdateUIEvent#SetText(text as String)
Gurax_DeclareMethodAlias(wxUpdateUIEvent, SetText_gurax, "SetText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, SetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetText(text);
	return Gurax::Value::nil();
}

// wx.UpdateUIEvent#Show(show as Bool)
Gurax_DeclareMethodAlias(wxUpdateUIEvent, Show_gurax, "Show")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxUpdateUIEvent, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Show(show);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxUpdateUIEvent
//------------------------------------------------------------------------------
VType_wxUpdateUIEvent VTYPE_wxUpdateUIEvent("UpdateUIEvent");

void VType_wxUpdateUIEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, Check_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, Enable_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetChecked_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetEnabled_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetSetChecked_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetSetEnabled_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetSetShown_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetSetText_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetShown_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, GetText_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, SetText_gurax));
	Assign(Gurax_CreateMethod(wxUpdateUIEvent, Show_gurax));
}

//------------------------------------------------------------------------------
// Value_wxUpdateUIEvent
//------------------------------------------------------------------------------
VType& Value_wxUpdateUIEvent::vtype = VTYPE_wxUpdateUIEvent;
EventValueFactoryDeriv<Value_wxUpdateUIEvent> Value_wxUpdateUIEvent::eventValueFactory;

String Value_wxUpdateUIEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.UpdateUIEvent");
}

Gurax_EndModuleScope(wx)
