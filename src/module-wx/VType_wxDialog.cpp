﻿//==============================================================================
// VType_wxDialog.cpp
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

${help.ComposePropertyHelp(wx.Dialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Dialog, `en)}

${help.ComposeMethodHelp(wx.Dialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Dialog(parent as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Dialog_gurax, "Dialog")
{
	Declare(VTYPE_wxDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.Dialog.
)**");
}

Gurax_ImplementConstructorEx(Dialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_DIALOG_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxDialogNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxDialog::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxDialog> pValue_gurax(new Value_wxDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Dialog#AddMainButtonId(id as Number)
Gurax_DeclareMethodAlias(wxDialog, AddMainButtonId_gurax, "AddMainButtonId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, AddMainButtonId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	// Function body
	pEntity_gurax->AddMainButtonId(id);
	return Gurax::Value::nil();
}

// wx.Dialog#CanDoLayoutAdaptation()
Gurax_DeclareMethodAlias(wxDialog, CanDoLayoutAdaptation_gurax, "CanDoLayoutAdaptation")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CanDoLayoutAdaptation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanDoLayoutAdaptation();
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#Centre(direction? as Number)
Gurax_DeclareMethodAlias(wxDialog, Centre_gurax, "Centre")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, Centre_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	pEntity_gurax->Centre(direction);
	return Gurax::Value::nil();
}

// wx.Dialog#CreateButtonSizer(flags as Number) {block?}
Gurax_DeclareMethodAlias(wxDialog, CreateButtonSizer_gurax, "CreateButtonSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CreateButtonSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->CreateButtonSizer(flags)));
}

// wx.Dialog#CreateSeparatedButtonSizer(flags as Number) {block?}
Gurax_DeclareMethodAlias(wxDialog, CreateSeparatedButtonSizer_gurax, "CreateSeparatedButtonSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CreateSeparatedButtonSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->CreateSeparatedButtonSizer(flags)));
}

// wx.Dialog#CreateSeparatedSizer(sizer as wx.Sizer) {block?}
Gurax_DeclareMethodAlias(wxDialog, CreateSeparatedSizer_gurax, "CreateSeparatedSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareArg("sizer", VTYPE_wxSizer, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CreateSeparatedSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSizer& value_sizer = args_gurax.Pick<Value_wxSizer>();
	wxSizer* sizer = value_sizer.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->CreateSeparatedSizer(sizer)));
}

// wx.Dialog#CreateStdDialogButtonSizer(flags as Number) {block?}
Gurax_DeclareMethodAlias(wxDialog, CreateStdDialogButtonSizer_gurax, "CreateStdDialogButtonSizer")
{
	Declare(VTYPE_wxStdDialogButtonSizer, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CreateStdDialogButtonSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStdDialogButtonSizer(
		pEntity_gurax->CreateStdDialogButtonSizer(flags)));
}

// wx.Dialog#CreateTextSizer(message as String) {block?}
Gurax_DeclareMethodAlias(wxDialog, CreateTextSizer_gurax, "CreateTextSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, CreateTextSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* message = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->CreateTextSizer(message)));
}

// wx.Dialog#DoLayoutAdaptation()
Gurax_DeclareMethodAlias(wxDialog, DoLayoutAdaptation_gurax, "DoLayoutAdaptation")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, DoLayoutAdaptation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DoLayoutAdaptation();
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#EndModal(retCode as Number)
Gurax_DeclareMethodAlias(wxDialog, EndModal_gurax, "EndModal")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("retCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, EndModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int retCode = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->EndModal(retCode);
	return Gurax::Value::nil();
}

// wx.Dialog#GetAffirmativeId()
Gurax_DeclareMethodAlias(wxDialog, GetAffirmativeId_gurax, "GetAffirmativeId")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetAffirmativeId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetAffirmativeId();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#GetContentWindow() {block?}
Gurax_DeclareMethodAlias(wxDialog, GetContentWindow_gurax, "GetContentWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetContentWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetContentWindow()));
}

// wx.Dialog#GetEscapeId()
Gurax_DeclareMethodAlias(wxDialog, GetEscapeId_gurax, "GetEscapeId")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetEscapeId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetEscapeId();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#GetLayoutAdaptationDone()
Gurax_DeclareMethodAlias(wxDialog, GetLayoutAdaptationDone_gurax, "GetLayoutAdaptationDone")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetLayoutAdaptationDone_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetLayoutAdaptationDone();
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#GetLayoutAdaptationLevel()
Gurax_DeclareMethodAlias(wxDialog, GetLayoutAdaptationLevel_gurax, "GetLayoutAdaptationLevel")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetLayoutAdaptationLevel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetLayoutAdaptationLevel();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#GetLayoutAdaptationMode()
Gurax_DeclareMethodAlias(wxDialog, GetLayoutAdaptationMode_gurax, "GetLayoutAdaptationMode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetLayoutAdaptationMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxDialogLayoutAdaptationMode rtn = pEntity_gurax->GetLayoutAdaptationMode();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#GetMainButtonIds()
Gurax_DeclareMethodAlias(wxDialog, GetMainButtonIds_gurax, "GetMainButtonIds")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetMainButtonIds_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayInt rtn = pEntity_gurax->GetMainButtonIds();
	return Util::CreateList(rtn);
}

// wx.Dialog#GetReturnCode()
Gurax_DeclareMethodAlias(wxDialog, GetReturnCode_gurax, "GetReturnCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, GetReturnCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetReturnCode();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#Iconize(iconize? as Bool)
Gurax_DeclareMethodAlias(wxDialog, Iconize_gurax, "Iconize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("iconize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, Iconize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool iconize = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Iconize(iconize);
	return Gurax::Value::nil();
}

// wx.Dialog#IsIconized()
Gurax_DeclareMethodAlias(wxDialog, IsIconized_gurax, "IsIconized")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, IsIconized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsIconized();
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#IsMainButtonId(id as Number)
Gurax_DeclareMethodAlias(wxDialog, IsMainButtonId_gurax, "IsMainButtonId")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, IsMainButtonId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	// Function body
	bool rtn = pEntity_gurax->IsMainButtonId(id);
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#IsModal()
Gurax_DeclareMethodAlias(wxDialog, IsModal_gurax, "IsModal")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, IsModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsModal();
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#SetAffirmativeId(id as Number)
Gurax_DeclareMethodAlias(wxDialog, SetAffirmativeId_gurax, "SetAffirmativeId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetAffirmativeId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetAffirmativeId(id);
	return Gurax::Value::nil();
}

// wx.Dialog#SetEscapeId(id as Number)
Gurax_DeclareMethodAlias(wxDialog, SetEscapeId_gurax, "SetEscapeId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetEscapeId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetEscapeId(id);
	return Gurax::Value::nil();
}

// wx.Dialog#SetIcon(icon as wx.Icon)
Gurax_DeclareMethodAlias(wxDialog, SetIcon_gurax, "SetIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icon", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_icon = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& icon = value_icon.GetEntity();
	// Function body
	pEntity_gurax->SetIcon(icon);
	return Gurax::Value::nil();
}

// wx.Dialog#SetIcons(icons as wx.IconBundle)
Gurax_DeclareMethodAlias(wxDialog, SetIcons_gurax, "SetIcons")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icons", VTYPE_wxIconBundle, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetIcons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIconBundle& value_icons = args_gurax.Pick<Value_wxIconBundle>();
	const wxIconBundle& icons = value_icons.GetEntity();
	// Function body
	pEntity_gurax->SetIcons(icons);
	return Gurax::Value::nil();
}

// wx.Dialog#SetLayoutAdaptationDone(done as Bool)
Gurax_DeclareMethodAlias(wxDialog, SetLayoutAdaptationDone_gurax, "SetLayoutAdaptationDone")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("done", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetLayoutAdaptationDone_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool done = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetLayoutAdaptationDone(done);
	return Gurax::Value::nil();
}

// wx.Dialog#SetLayoutAdaptationLevel(level as Number)
Gurax_DeclareMethodAlias(wxDialog, SetLayoutAdaptationLevel_gurax, "SetLayoutAdaptationLevel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetLayoutAdaptationLevel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int level = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetLayoutAdaptationLevel(level);
	return Gurax::Value::nil();
}

// wx.Dialog#SetLayoutAdaptationMode(mode as Number)
Gurax_DeclareMethodAlias(wxDialog, SetLayoutAdaptationMode_gurax, "SetLayoutAdaptationMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetLayoutAdaptationMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxDialogLayoutAdaptationMode mode = args_gurax.PickNumber<wxDialogLayoutAdaptationMode>();
	// Function body
	pEntity_gurax->SetLayoutAdaptationMode(mode);
	return Gurax::Value::nil();
}

// wx.Dialog#SetReturnCode(retCode as Number)
Gurax_DeclareMethodAlias(wxDialog, SetReturnCode_gurax, "SetReturnCode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("retCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, SetReturnCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int retCode = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetReturnCode(retCode);
	return Gurax::Value::nil();
}

// wx.Dialog#Show(show? as Bool)
Gurax_DeclareMethodAlias(wxDialog, Show_gurax, "Show")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : 1;
	// Function body
	bool rtn = pEntity_gurax->Show(show);
	return new Gurax::Value_Bool(rtn);
}

// wx.Dialog#ShowModal()
Gurax_DeclareMethodAlias(wxDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

// wx.Dialog#ShowWindowModal()
Gurax_DeclareMethodAlias(wxDialog, ShowWindowModal_gurax, "ShowWindowModal")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxDialog, ShowWindowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ShowWindowModal();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDialog
//------------------------------------------------------------------------------
VType_wxDialog VTYPE_wxDialog("Dialog");

void VType_wxDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxTopLevelWindow, Flag::Mutable, Gurax_CreateConstructor(Dialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDialog, AddMainButtonId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CanDoLayoutAdaptation_gurax));
	Assign(Gurax_CreateMethod(wxDialog, Centre_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CreateButtonSizer_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CreateSeparatedButtonSizer_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CreateSeparatedSizer_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CreateStdDialogButtonSizer_gurax));
	Assign(Gurax_CreateMethod(wxDialog, CreateTextSizer_gurax));
	Assign(Gurax_CreateMethod(wxDialog, DoLayoutAdaptation_gurax));
	Assign(Gurax_CreateMethod(wxDialog, EndModal_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetAffirmativeId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetContentWindow_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetEscapeId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetLayoutAdaptationDone_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetLayoutAdaptationLevel_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetLayoutAdaptationMode_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetMainButtonIds_gurax));
	Assign(Gurax_CreateMethod(wxDialog, GetReturnCode_gurax));
	Assign(Gurax_CreateMethod(wxDialog, Iconize_gurax));
	Assign(Gurax_CreateMethod(wxDialog, IsIconized_gurax));
	Assign(Gurax_CreateMethod(wxDialog, IsMainButtonId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, IsModal_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetAffirmativeId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetEscapeId_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetIcon_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetIcons_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetLayoutAdaptationDone_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetLayoutAdaptationLevel_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetLayoutAdaptationMode_gurax));
	Assign(Gurax_CreateMethod(wxDialog, SetReturnCode_gurax));
	Assign(Gurax_CreateMethod(wxDialog, Show_gurax));
	Assign(Gurax_CreateMethod(wxDialog, ShowModal_gurax));
	Assign(Gurax_CreateMethod(wxDialog, ShowWindowModal_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDialog
//------------------------------------------------------------------------------
VType& Value_wxDialog::vtype = VTYPE_wxDialog;

String Value_wxDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Dialog");
}

//------------------------------------------------------------------------------
// Value_wxDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
