﻿//==============================================================================
// VType_wxPropertySheetDialog.cpp
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

${help.ComposePropertyHelp(wx.PropertySheetDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PropertySheetDialog, `en)}

${help.ComposeMethodHelp(wx.PropertySheetDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PropertySheetDialog(parent as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(PropertySheetDialog_gurax, "PropertySheetDialog")
{
	Declare(VTYPE_wxPropertySheetDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.PropertySheetDialog.");
}

Gurax_ImplementConstructorEx(PropertySheetDialog_gurax, processor_gurax, argument_gurax)
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
	auto pEntity_gurax = new Value_wxPropertySheetDialog::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxPropertySheetDialog> pValue_gurax(new Value_wxPropertySheetDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.PropertySheetDialog#AddBookCtrl(sizer as wx.Sizer)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, AddBookCtrl_gurax, "AddBookCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sizer", VTYPE_wxSizer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, AddBookCtrl_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->AddBookCtrl(sizer);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#Create(parent as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
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
	bool rtn = pEntity_gurax->Create(parent, id, title, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertySheetDialog#CreateBookCtrl() {block?}
Gurax_DeclareMethodAlias(wxPropertySheetDialog, CreateBookCtrl_gurax, "CreateBookCtrl")
{
	Declare(VTYPE_wxBookCtrlBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, CreateBookCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBookCtrlBase(
		pEntity_gurax->CreateBookCtrl()));
}

// wx.PropertySheetDialog#CreateButtons(flags? as Number)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, CreateButtons_gurax, "CreateButtons")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, CreateButtons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : (wxOK | wxCANCEL);
	// Function body
	pEntity_gurax->CreateButtons(flags);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#GetBookCtrl() {block?}
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetBookCtrl_gurax, "GetBookCtrl")
{
	Declare(VTYPE_wxBookCtrlBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetBookCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBookCtrlBase(
		pEntity_gurax->GetBookCtrl()));
}

// wx.PropertySheetDialog#GetInnerSizer() {block?}
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetInnerSizer_gurax, "GetInnerSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetInnerSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->GetInnerSizer()));
}

// wx.PropertySheetDialog#SetInnerSizer(sizer as wx.Sizer)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, SetInnerSizer_gurax, "SetInnerSizer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sizer", VTYPE_wxSizer, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, SetInnerSizer_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetInnerSizer(sizer);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#GetSheetStyle()
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetSheetStyle_gurax, "GetSheetStyle")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetSheetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetSheetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertySheetDialog#LayoutDialog(centreFlags? as Number)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, LayoutDialog_gurax, "LayoutDialog")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("centreFlags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, LayoutDialog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool centreFlags_validFlag = args_gurax.IsValid();
	int centreFlags = centreFlags_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	pEntity_gurax->LayoutDialog(centreFlags);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#SetBookCtrl(bookCtrl as wx.BookCtrlBase)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, SetBookCtrl_gurax, "SetBookCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bookCtrl", VTYPE_wxBookCtrlBase, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, SetBookCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBookCtrlBase& value_bookCtrl = args_gurax.Pick<Value_wxBookCtrlBase>();
	wxBookCtrlBase* bookCtrl = value_bookCtrl.GetEntityPtr();
	// Function body
	pEntity_gurax->SetBookCtrl(bookCtrl);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#SetSheetStyle(style as Number)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, SetSheetStyle_gurax, "SetSheetStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, SetSheetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long style = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetSheetStyle(style);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#SetSheetOuterBorder(border as Number)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, SetSheetOuterBorder_gurax, "SetSheetOuterBorder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, SetSheetOuterBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int border = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSheetOuterBorder(border);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#GetSheetOuterBorder()
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetSheetOuterBorder_gurax, "GetSheetOuterBorder")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetSheetOuterBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSheetOuterBorder();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertySheetDialog#SetSheetInnerBorder(border as Number)
Gurax_DeclareMethodAlias(wxPropertySheetDialog, SetSheetInnerBorder_gurax, "SetSheetInnerBorder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, SetSheetInnerBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int border = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSheetInnerBorder(border);
	return Gurax::Value::nil();
}

// wx.PropertySheetDialog#GetSheetInnerBorder()
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetSheetInnerBorder_gurax, "GetSheetInnerBorder")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetSheetInnerBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSheetInnerBorder();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertySheetDialog#GetContentWindow() {block?}
Gurax_DeclareMethodAlias(wxPropertySheetDialog, GetContentWindow_gurax, "GetContentWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPropertySheetDialog, GetContentWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetContentWindow()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPropertySheetDialog
//------------------------------------------------------------------------------
VType_wxPropertySheetDialog VTYPE_wxPropertySheetDialog("PropertySheetDialog");

void VType_wxPropertySheetDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(PropertySheetDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, AddBookCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, Create_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, CreateBookCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, CreateButtons_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetBookCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetInnerSizer_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, SetInnerSizer_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetSheetStyle_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, LayoutDialog_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, SetBookCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, SetSheetStyle_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, SetSheetOuterBorder_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetSheetOuterBorder_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, SetSheetInnerBorder_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetSheetInnerBorder_gurax));
	Assign(Gurax_CreateMethod(wxPropertySheetDialog, GetContentWindow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPropertySheetDialog
//------------------------------------------------------------------------------
VType& Value_wxPropertySheetDialog::vtype = VTYPE_wxPropertySheetDialog;

String Value_wxPropertySheetDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PropertySheetDialog");
}

//------------------------------------------------------------------------------
// Value_wxPropertySheetDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
