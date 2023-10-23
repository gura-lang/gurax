﻿//==============================================================================
// VType_wxRibbonButtonBar.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.RibbonButtonBar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonButtonBar, `en)}

${help.ComposeMethodHelp(wx.RibbonButtonBar, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonButtonBar, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonButtonBar, `ja)}

${help.ComposeMethodHelp(wx.RibbonButtonBar, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RibbonButtonBar(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RibbonButtonBar_gurax, "RibbonButtonBar")
{
	Declare(VTYPE_wxRibbonButtonBar, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RibbonButtonBar_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxRibbonButtonBar::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxRibbonButtonBar> pValue_gurax(new Value_wxRibbonButtonBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonButtonBar#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, Create_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonButtonBar#AddButton(button_id as Number, label as String, bitmap as wx.Bitmap, help_string as String, kind? as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, AddButton_gurax, "AddButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("kind", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, AddButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	wxString help_string(args_gurax.PickString());
	bool kind_validFlag = args_gurax.IsValid();
	wxRibbonButtonKind kind = kind_validFlag? args_gurax.PickNumber<wxRibbonButtonKind>() : wxRIBBON_BUTTON_NORMAL;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->AddButton(button_id, label, bitmap, help_string, kind)));
}

// wx.RibbonButtonBar#AddDropdownButton(button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, AddDropdownButton_gurax, "AddDropdownButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, AddDropdownButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->AddDropdownButton(button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#AddHybridButton(button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, AddHybridButton_gurax, "AddHybridButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, AddHybridButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->AddHybridButton(button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#AddToggleButton(button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, AddToggleButton_gurax, "AddToggleButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, AddToggleButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->AddToggleButton(button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#InsertButton(pos as Number, button_id as Number, label as String, bitmap as wx.Bitmap, help_string as String, kind? as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, InsertButton_gurax, "InsertButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("kind", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, InsertButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	wxString help_string(args_gurax.PickString());
	bool kind_validFlag = args_gurax.IsValid();
	wxRibbonButtonKind kind = kind_validFlag? args_gurax.PickNumber<wxRibbonButtonKind>() : wxRIBBON_BUTTON_NORMAL;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->InsertButton(pos, button_id, label, bitmap, help_string, kind)));
}

// wx.RibbonButtonBar#InsertDropdownButton(pos as Number, button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, InsertDropdownButton_gurax, "InsertDropdownButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, InsertDropdownButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->InsertDropdownButton(pos, button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#InsertHybridButton(pos as Number, button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, InsertHybridButton_gurax, "InsertHybridButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, InsertHybridButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->InsertHybridButton(pos, button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#InsertToggleButton(pos as Number, button_id as Number, label as String, bitmap as wx.Bitmap, help_string? as String) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, InsertToggleButton_gurax, "InsertToggleButton")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("help_string", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, InsertToggleButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	int button_id = args_gurax.PickNumber<int>();
	wxString label(args_gurax.PickString());
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	bool help_string_validFlag = args_gurax.IsValid();
	wxString help_string = help_string_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->InsertToggleButton(pos, button_id, label, bitmap, help_string)));
}

// wx.RibbonButtonBar#GetButtonCount()
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetButtonCount_gurax, "GetButtonCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetButtonCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetButtonCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonButtonBar#SetItemClientObject(item as wx.RibbonButtonBarButtonBase, data as Any)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, SetItemClientObject_gurax, "SetItemClientObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonButtonBarButtonBase, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, SetItemClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBarButtonBase& value_item = args_gurax.Pick<Value_wxRibbonButtonBarButtonBase>();
	wxRibbonButtonBarButtonBase* item = value_item.GetEntityPtr();
	const Value& data = args_gurax.PickValue();
	// Function body
	pEntity_gurax->SetItemClientObject(item, ClientData::Create(data));
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#GetItemClientObject(item as wx.RibbonButtonBarButtonBase)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetItemClientObject_gurax, "GetItemClientObject")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonButtonBarButtonBase, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetItemClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBarButtonBase& value_item = args_gurax.Pick<Value_wxRibbonButtonBarButtonBase>();
	const wxRibbonButtonBarButtonBase* item = value_item.GetEntityPtr();
	// Function body
	ClientData* rtn = dynamic_cast<ClientData*>(pEntity_gurax->GetItemClientObject(item));
	if (!rtn) return Value::nil();
	return rtn->GetValue().Reference();
}

// wx.RibbonButtonBar#SetItemClientData(item as wx.RibbonButtonBarButtonBase, data as Pointer)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, SetItemClientData_gurax, "SetItemClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonButtonBarButtonBase, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, SetItemClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBarButtonBase& value_item = args_gurax.Pick<Value_wxRibbonButtonBarButtonBase>();
	wxRibbonButtonBarButtonBase* item = value_item.GetEntityPtr();
	void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	pEntity_gurax->SetItemClientData(item, data);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#GetItem(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetItem_gurax, "GetItem")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->GetItem(n)));
}

// wx.RibbonButtonBar#GetItemById(id as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetItemById_gurax, "GetItemById")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetItemById_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->GetItemById(id)));
}

// wx.RibbonButtonBar#GetItemId(item as wx.RibbonButtonBarButtonBase)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetItemId_gurax, "GetItemId")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonButtonBarButtonBase, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetItemId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonButtonBarButtonBase& value_item = args_gurax.Pick<Value_wxRibbonButtonBarButtonBase>();
	wxRibbonButtonBarButtonBase* item = value_item.GetEntityPtr();
	// Function body
	int rtn = pEntity_gurax->GetItemId(item);
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonButtonBar#Realize()
Gurax_DeclareMethodAlias(wxRibbonButtonBar, Realize_gurax, "Realize")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, Realize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Realize();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonButtonBar#ClearButtons()
Gurax_DeclareMethodAlias(wxRibbonButtonBar, ClearButtons_gurax, "ClearButtons")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, ClearButtons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ClearButtons();
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#DeleteButton(button_id as Number)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, DeleteButton_gurax, "DeleteButton")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, DeleteButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->DeleteButton(button_id);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonButtonBar#EnableButton(button_id as Number, enable? as Bool)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, EnableButton_gurax, "EnableButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, EnableButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	bool enable = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->EnableButton(button_id, enable);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#ToggleButton(button_id as Number, checked as Bool)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, ToggleButton_gurax, "ToggleButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button_id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("checked", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, ToggleButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonButtonBar::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int button_id = args_gurax.PickNumber<int>();
	bool checked = args_gurax.PickBool();
	// Function body
	pEntity_gurax->ToggleButton(button_id, checked);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#GetActiveItem() {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetActiveItem_gurax, "GetActiveItem")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetActiveItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->GetActiveItem()));
}

// wx.RibbonButtonBar#GetHoveredItem() {block?}
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetHoveredItem_gurax, "GetHoveredItem")
{
	Declare(VTYPE_wxRibbonButtonBarButtonBase, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetHoveredItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonButtonBarButtonBase(pEntity_gurax->GetHoveredItem()));
}

// wx.RibbonButtonBar#SetShowToolTipsForDisabled(show as Bool)
Gurax_DeclareMethodAlias(wxRibbonButtonBar, SetShowToolTipsForDisabled_gurax, "SetShowToolTipsForDisabled")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, SetShowToolTipsForDisabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetShowToolTipsForDisabled(show);
	return Gurax::Value::nil();
}

// wx.RibbonButtonBar#GetShowToolTipsForDisabled()
Gurax_DeclareMethodAlias(wxRibbonButtonBar, GetShowToolTipsForDisabled_gurax, "GetShowToolTipsForDisabled")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonButtonBar, GetShowToolTipsForDisabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetShowToolTipsForDisabled();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonButtonBar
//------------------------------------------------------------------------------
VType_wxRibbonButtonBar VTYPE_wxRibbonButtonBar("RibbonButtonBar");

void VType_wxRibbonButtonBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable, Gurax_CreateConstructor(RibbonButtonBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, Create_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, AddButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, AddDropdownButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, AddHybridButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, AddToggleButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, InsertButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, InsertDropdownButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, InsertHybridButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, InsertToggleButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetButtonCount_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, SetItemClientObject_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetItemClientObject_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, SetItemClientData_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetItemById_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetItemId_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, Realize_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, ClearButtons_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, DeleteButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, EnableButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, ToggleButton_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetActiveItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetHoveredItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, SetShowToolTipsForDisabled_gurax));
	Assign(Gurax_CreateMethod(wxRibbonButtonBar, GetShowToolTipsForDisabled_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBar
//------------------------------------------------------------------------------
VType& Value_wxRibbonButtonBar::vtype = VTYPE_wxRibbonButtonBar;

String Value_wxRibbonButtonBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonButtonBar");
}

//------------------------------------------------------------------------------
// Value_wxRibbonButtonBar::EntityT
//------------------------------------------------------------------------------
size_t Value_wxRibbonButtonBar::EntityT::GetButtonCount() const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("GetButtonCount");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Number)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function GetButtonCount is expected to return a value of %s or its derived class",
				VTYPE_Number.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Number::GetNumber<size_t>(*pValueRtn);
	} while (0);
	return public_GetButtonCount();
}

int Value_wxRibbonButtonBar::EntityT::GetItemId(wxRibbonButtonBarButtonBase* item) const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("GetItemId");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxRibbonButtonBarButtonBase(item))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Number)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function GetItemId is expected to return a value of %s or its derived class",
				VTYPE_Number.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Number::GetNumber<int>(*pValueRtn);
	} while (0);
	return public_GetItemId(item);
}

bool Value_wxRibbonButtonBar::EntityT::Realize()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Realize");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function Realize is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_Realize();
}

void Value_wxRibbonButtonBar::EntityT::ClearButtons()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("ClearButtons");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_ClearButtons();
}

bool Value_wxRibbonButtonBar::EntityT::DeleteButton(int button_id)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("DeleteButton");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(button_id))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function DeleteButton is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_DeleteButton(button_id);
}

void Value_wxRibbonButtonBar::EntityT::EnableButton(int button_id, bool enable)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("EnableButton");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(button_id))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(new Gurax::Value_Bool(enable))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_EnableButton(button_id, enable);
}

void Value_wxRibbonButtonBar::EntityT::ToggleButton(int button_id, bool checked)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("ToggleButton");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(button_id))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(new Gurax::Value_Bool(checked))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_ToggleButton(button_id, checked);
}

Gurax_EndModuleScope(wx)
