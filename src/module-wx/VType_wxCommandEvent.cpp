//==============================================================================
// VType_wxCommandEvent.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CommandEvent#GetExtraLong()
Gurax_DeclareMethodAlias(wxCommandEvent, GetExtraLong_gurax, "GetExtraLong")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, GetExtraLong_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetExtraLong();
	return new Gurax::Value_Number(rtn);
}

// wx.CommandEvent#GetInt()
Gurax_DeclareMethodAlias(wxCommandEvent, GetInt_gurax, "GetInt")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, GetInt_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetInt();
	return new Gurax::Value_Number(rtn);
}

// wx.CommandEvent#GetSelection()
Gurax_DeclareMethodAlias(wxCommandEvent, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.CommandEvent#GetString()
Gurax_DeclareMethodAlias(wxCommandEvent, GetString_gurax, "GetString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, GetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.CommandEvent#IsChecked()
Gurax_DeclareMethodAlias(wxCommandEvent, IsChecked_gurax, "IsChecked")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, IsChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsChecked();
	return new Gurax::Value_Bool(rtn);
}

// wx.CommandEvent#IsSelection()
Gurax_DeclareMethodAlias(wxCommandEvent, IsSelection_gurax, "IsSelection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, IsSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.CommandEvent#SetExtraLong(extraLong as Number)
Gurax_DeclareMethodAlias(wxCommandEvent, SetExtraLong_gurax, "SetExtraLong")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("extraLong", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, SetExtraLong_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long extraLong = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetExtraLong(extraLong);
	return Gurax::Value::nil();
}

// wx.CommandEvent#SetInt(intCommand as Number)
Gurax_DeclareMethodAlias(wxCommandEvent, SetInt_gurax, "SetInt")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("intCommand", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, SetInt_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int intCommand = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetInt(intCommand);
	return Gurax::Value::nil();
}

// wx.CommandEvent#SetString(string as String)
Gurax_DeclareMethodAlias(wxCommandEvent, SetString_gurax, "SetString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCommandEvent, SetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetString(string);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCommandEvent
//------------------------------------------------------------------------------
VType_wxCommandEvent VTYPE_wxCommandEvent("CommandEvent");

void VType_wxCommandEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCommandEvent, GetExtraLong_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, GetInt_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, GetString_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, IsChecked_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, IsSelection_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, SetExtraLong_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, SetInt_gurax));
	Assign(Gurax_CreateMethod(wxCommandEvent, SetString_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCommandEvent
//------------------------------------------------------------------------------
VType& Value_wxCommandEvent::vtype = VTYPE_wxCommandEvent;
EventValueFactoryDeriv<Value_wxCommandEvent> Value_wxCommandEvent::eventValueFactory;

String Value_wxCommandEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CommandEvent");
}

Gurax_EndModuleScope(wx)
