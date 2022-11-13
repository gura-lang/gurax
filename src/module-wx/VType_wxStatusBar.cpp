﻿//==============================================================================
// VType_wxStatusBar.cpp
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

${help.ComposePropertyHelp(wx.StatusBar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StatusBar, `en)}

${help.ComposeMethodHelp(wx.StatusBar, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StatusBar(parent as wx.Window, id? as Number, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(StatusBar_gurax, "StatusBar")
{
	Declare(VTYPE_wxStatusBar, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.StatusBar.
)**");
}

Gurax_ImplementConstructorEx(StatusBar_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSTB_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStatusBarNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxStatusBar::EntityT(parent, id, style, name);
	RefPtr<Value_wxStatusBar> pValue_gurax(new Value_wxStatusBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StatusBar#Create(parent as wx.Window, id? as Number, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxStatusBar, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, Create_gurax, processor_gurax, argument_gurax)
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
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSTB_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStatusBarNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.StatusBar#GetFieldRect(i as Number, rect as wx.Rect)
Gurax_DeclareMethodAlias(wxStatusBar, GetFieldRect_gurax, "GetFieldRect")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetFieldRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int i = args_gurax.PickNumber<int>();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	wxRect& rect = value_rect.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->GetFieldRect(i, rect);
	return new Gurax::Value_Bool(rtn);
}

// wx.StatusBar#GetFieldsCount()
Gurax_DeclareMethodAlias(wxStatusBar, GetFieldsCount_gurax, "GetFieldsCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetFieldsCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFieldsCount();
	return new Gurax::Value_Number(rtn);
}

// wx.StatusBar#GetField(n as Number) {block?}
Gurax_DeclareMethodAlias(wxStatusBar, GetField_gurax, "GetField")
{
	Declare(VTYPE_wxStatusBarPane, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetField_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBarPane(
		pEntity_gurax->GetField(n)));
}

// wx.StatusBar#GetBorders() {block?}
Gurax_DeclareMethodAlias(wxStatusBar, GetBorders_gurax, "GetBorders")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetBorders_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetBorders()));
}

// wx.StatusBar#GetStatusText(i? as Number)
Gurax_DeclareMethodAlias(wxStatusBar, GetStatusText_gurax, "GetStatusText")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool i_validFlag = args_gurax.IsValid();
	int i = i_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	wxString rtn = pEntity_gurax->GetStatusText(i);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.StatusBar#GetStatusWidth(n as Number)
Gurax_DeclareMethodAlias(wxStatusBar, GetStatusWidth_gurax, "GetStatusWidth")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetStatusWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	int rtn = pEntity_gurax->GetStatusWidth(n);
	return new Gurax::Value_Number(rtn);
}

// wx.StatusBar#GetStatusStyle(n as Number)
Gurax_DeclareMethodAlias(wxStatusBar, GetStatusStyle_gurax, "GetStatusStyle")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, GetStatusStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	int rtn = pEntity_gurax->GetStatusStyle(n);
	return new Gurax::Value_Number(rtn);
}

// wx.StatusBar#PopStatusText(field? as Number)
Gurax_DeclareMethodAlias(wxStatusBar, PopStatusText_gurax, "PopStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("field", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, PopStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool field_validFlag = args_gurax.IsValid();
	int field = field_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->PopStatusText(field);
	return Gurax::Value::nil();
}

// wx.StatusBar#PushStatusText(string as String, field? as Number)
Gurax_DeclareMethodAlias(wxStatusBar, PushStatusText_gurax, "PushStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("field", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, PushStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	bool field_validFlag = args_gurax.IsValid();
	int field = field_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->PushStatusText(string, field);
	return Gurax::Value::nil();
}

// wx.StatusBar#SetFieldsCount(widths[]? as Number)
Gurax_DeclareMethodAlias(wxStatusBar, SetFieldsCount_gurax, "SetFieldsCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("widths", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, SetFieldsCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto widths = args_gurax.PickNumList<int>();
	// Function body
	if (widths.empty()) {
		pEntity_gurax->SetFieldsCount();
	} else {
		pEntity_gurax->SetFieldsCount(widths.sizeT<int>(), widths.data());
	}
	return Value::nil();
}

// wx.StatusBar#SetMinHeight(height as Number)
Gurax_DeclareMethodAlias(wxStatusBar, SetMinHeight_gurax, "SetMinHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, SetMinHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int height = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinHeight(height);
	return Gurax::Value::nil();
}

// wx.StatusBar#SetStatusStyles(styles[] as Number)
Gurax_DeclareMethodAlias(wxStatusBar, SetStatusStyles_gurax, "SetStatusStyles")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("styles", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, SetStatusStyles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto styles = args_gurax.PickNumList<int>();
	// Function body
	pEntity_gurax->SetStatusStyles(styles.sizeT<int>(), styles.data());
	return Value::nil();
}

// wx.StatusBar#SetStatusText(text as String, i? as Number)
Gurax_DeclareMethodAlias(wxStatusBar, SetStatusText_gurax, "SetStatusText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, SetStatusText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	bool i_validFlag = args_gurax.IsValid();
	int i = i_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->SetStatusText(text, i);
	return Gurax::Value::nil();
}

// wx.StatusBar#SetStatusWidths(widths_field[] as Number)
Gurax_DeclareMethodAlias(wxStatusBar, SetStatusWidths_gurax, "SetStatusWidths")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("widths_field", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxStatusBar, SetStatusWidths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto widths_field = args_gurax.PickNumList<int>();
	// Function body
	pEntity_gurax->SetStatusWidths(widths_field.sizeT<int>(), widths_field.data());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStatusBar
//------------------------------------------------------------------------------
VType_wxStatusBar VTYPE_wxStatusBar("StatusBar");

void VType_wxStatusBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StatusBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStatusBar, Create_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetFieldRect_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetFieldsCount_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetField_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetBorders_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetStatusText_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetStatusWidth_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, GetStatusStyle_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, PopStatusText_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, PushStatusText_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, SetFieldsCount_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, SetMinHeight_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, SetStatusStyles_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, SetStatusText_gurax));
	Assign(Gurax_CreateMethod(wxStatusBar, SetStatusWidths_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStatusBar
//------------------------------------------------------------------------------
VType& Value_wxStatusBar::vtype = VTYPE_wxStatusBar;

String Value_wxStatusBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StatusBar");
}

//------------------------------------------------------------------------------
// Value_wxStatusBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
