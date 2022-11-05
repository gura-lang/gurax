//==============================================================================
// VType_wxListItem.cpp
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

${help.ComposePropertyHelp(wxListItem, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxListItem, `en)}

${help.ComposeMethodHelp(wxListItem, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ListItem() {block?}
Gurax_DeclareConstructorAlias(ListItem_gurax, "ListItem")
{
	Declare(VTYPE_wxListItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ListItem.");
}

Gurax_ImplementConstructorEx(ListItem_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxListItem(
		wxListItem()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ListItem#Clear()
Gurax_DeclareMethodAlias(wxListItem, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.ListItem#GetAlign()
Gurax_DeclareMethodAlias(wxListItem, GetAlign_gurax, "GetAlign")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetAlign_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxListColumnFormat rtn = pEntity_gurax->GetAlign();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetBackgroundColour() {block?}
Gurax_DeclareMethodAlias(wxListItem, GetBackgroundColour_gurax, "GetBackgroundColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetBackgroundColour()));
}

// wx.ListItem#GetColumn()
Gurax_DeclareMethodAlias(wxListItem, GetColumn_gurax, "GetColumn")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetColumn();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetFont() {block?}
Gurax_DeclareMethodAlias(wxListItem, GetFont_gurax, "GetFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->GetFont()));
}

// wx.ListItem#GetId()
Gurax_DeclareMethodAlias(wxListItem, GetId_gurax, "GetId")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetId();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetImage()
Gurax_DeclareMethodAlias(wxListItem, GetImage_gurax, "GetImage")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetImage();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetMask()
Gurax_DeclareMethodAlias(wxListItem, GetMask_gurax, "GetMask")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetMask();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetState()
Gurax_DeclareMethodAlias(wxListItem, GetState_gurax, "GetState")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetState();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#GetText()
Gurax_DeclareMethodAlias(wxListItem, GetText_gurax, "GetText")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetText();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.ListItem#GetTextColour() {block?}
Gurax_DeclareMethodAlias(wxListItem, GetTextColour_gurax, "GetTextColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetTextColour()));
}

// wx.ListItem#GetWidth()
Gurax_DeclareMethodAlias(wxListItem, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.ListItem#SetAlign(align as Number)
Gurax_DeclareMethodAlias(wxListItem, SetAlign_gurax, "SetAlign")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("align", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetAlign_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxListColumnFormat align = args_gurax.PickNumber<wxListColumnFormat>();
	// Function body
	pEntity_gurax->SetAlign(align);
	return Gurax::Value::nil();
}

// wx.ListItem#SetBackgroundColour(colBack as wx.Colour)
Gurax_DeclareMethodAlias(wxListItem, SetBackgroundColour_gurax, "SetBackgroundColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colBack", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colBack = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBack = value_colBack.GetEntity();
	// Function body
	pEntity_gurax->SetBackgroundColour(colBack);
	return Gurax::Value::nil();
}

// wx.ListItem#SetColumn(col as Number)
Gurax_DeclareMethodAlias(wxListItem, SetColumn_gurax, "SetColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetColumn(col);
	return Gurax::Value::nil();
}

// wx.ListItem#SetFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxListItem, SetFont_gurax, "SetFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFont& value_font = args_gurax.Pick<Value_wxFont>();
	const wxFont& font = value_font.GetEntity();
	// Function body
	pEntity_gurax->SetFont(font);
	return Gurax::Value::nil();
}

// wx.ListItem#SetId(id as Number)
Gurax_DeclareMethodAlias(wxListItem, SetId_gurax, "SetId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long id = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetId(id);
	return Gurax::Value::nil();
}

// wx.ListItem#SetImage(image as Number)
Gurax_DeclareMethodAlias(wxListItem, SetImage_gurax, "SetImage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("image", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int image = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetImage(image);
	return Gurax::Value::nil();
}

// wx.ListItem#SetMask(mask as Number)
Gurax_DeclareMethodAlias(wxListItem, SetMask_gurax, "SetMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long mask = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetMask(mask);
	return Gurax::Value::nil();
}

// wx.ListItem#SetState(state as Number)
Gurax_DeclareMethodAlias(wxListItem, SetState_gurax, "SetState")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("state", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long state = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetState(state);
	return Gurax::Value::nil();
}

// wx.ListItem#SetStateMask(stateMask as Number)
Gurax_DeclareMethodAlias(wxListItem, SetStateMask_gurax, "SetStateMask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stateMask", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetStateMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long stateMask = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetStateMask(stateMask);
	return Gurax::Value::nil();
}

// wx.ListItem#SetText(text as String)
Gurax_DeclareMethodAlias(wxListItem, SetText_gurax, "SetText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetText_gurax, processor_gurax, argument_gurax)
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

// wx.ListItem#SetTextColour(colText as wx.Colour)
Gurax_DeclareMethodAlias(wxListItem, SetTextColour_gurax, "SetTextColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colText", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colText = args_gurax.Pick<Value_wxColour>();
	const wxColour& colText = value_colText.GetEntity();
	// Function body
	pEntity_gurax->SetTextColour(colText);
	return Gurax::Value::nil();
}

// wx.ListItem#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxListItem, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWidth(width);
	return Gurax::Value::nil();
}

// wx.ListItem#SetData(data as Number)
Gurax_DeclareMethodAlias(wxListItem, SetData_gurax, "SetData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("data", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListItem, SetData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long data = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetData(data);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxListItem
//------------------------------------------------------------------------------
VType_wxListItem VTYPE_wxListItem("ListItem");

void VType_wxListItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable, Gurax_CreateConstructor(ListItem_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxListItem, Clear_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetAlign_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetColumn_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetFont_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetId_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetImage_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetMask_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetState_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetText_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxListItem, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetAlign_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetColumn_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetFont_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetId_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetImage_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetMask_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetState_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetStateMask_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetText_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxListItem, SetData_gurax));
}

//------------------------------------------------------------------------------
// Value_wxListItem
//------------------------------------------------------------------------------
VType& Value_wxListItem::vtype = VTYPE_wxListItem;

String Value_wxListItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ListItem");
}

Gurax_EndModuleScope(wx)
