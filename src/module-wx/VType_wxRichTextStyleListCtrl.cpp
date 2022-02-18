//==============================================================================
// VType_wxRichTextStyleListCtrl.cpp
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
// wx.RichTextStyleListCtrl(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?} {block?}
Gurax_DeclareConstructorAlias(RichTextStyleListCtrl_gurax, "RichTextStyleListCtrl")
{
	Declare(VTYPE_wxRichTextStyleListCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RichTextStyleListCtrl.");
}

Gurax_ImplementConstructorEx(RichTextStyleListCtrl_gurax, processor_gurax, argument_gurax)
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
	auto pEntity_gurax = new Value_wxRichTextStyleListCtrl::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxRichTextStyleListCtrl> pValue_gurax(new Value_wxRichTextStyleListCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RichTextStyleListCtrl#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, Create_gurax, processor_gurax, argument_gurax)
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

// wx.RichTextStyleListCtrl#GetRichTextCtrl() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, GetRichTextCtrl_gurax, "GetRichTextCtrl")
{
	Declare(VTYPE_wxRichTextCtrl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, GetRichTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextCtrl(
		pEntity_gurax->GetRichTextCtrl()));
}

// wx.RichTextStyleListCtrl#GetStyleChoice() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, GetStyleChoice_gurax, "GetStyleChoice")
{
	Declare(VTYPE_wxChoice, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, GetStyleChoice_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxChoice(
		pEntity_gurax->GetStyleChoice()));
}

// wx.RichTextStyleListCtrl#GetStyleListBox() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, GetStyleListBox_gurax, "GetStyleListBox")
{
	Declare(VTYPE_wxRichTextStyleListBox, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, GetStyleListBox_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleListBox(
		pEntity_gurax->GetStyleListBox()));
}

// wx.RichTextStyleListCtrl#GetStyleSheet() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, GetStyleSheet_gurax, "GetStyleSheet")
{
	Declare(VTYPE_wxRichTextStyleSheet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, GetStyleSheet_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleSheet(
		*pEntity_gurax->GetStyleSheet()));
}

// wx.RichTextStyleListCtrl#GetStyleType()
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, GetStyleType_gurax, "GetStyleType")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, GetStyleType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxRichTextStyleListBox::wxRichTextStyleType rtn = pEntity_gurax->GetStyleType();
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextStyleListCtrl#SetRichTextCtrl(ctrl as wx.RichTextCtrl)
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, SetRichTextCtrl_gurax, "SetRichTextCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ctrl", VTYPE_wxRichTextCtrl, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, SetRichTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextCtrl& value_ctrl = args_gurax.Pick<Value_wxRichTextCtrl>();
	wxRichTextCtrl* ctrl = value_ctrl.GetEntityPtr();
	// Function body
	pEntity_gurax->SetRichTextCtrl(ctrl);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListCtrl#SetStyleSheet(styleSheet as wx.RichTextStyleSheet)
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, SetStyleSheet_gurax, "SetStyleSheet")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("styleSheet", VTYPE_wxRichTextStyleSheet, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, SetStyleSheet_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleSheet& value_styleSheet = args_gurax.Pick<Value_wxRichTextStyleSheet>();
	wxRichTextStyleSheet* styleSheet = value_styleSheet.GetEntityPtr();
	// Function body
	pEntity_gurax->SetStyleSheet(styleSheet);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListCtrl#SetStyleType(styleType as Number)
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, SetStyleType_gurax, "SetStyleType")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("styleType", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, SetStyleType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxRichTextStyleListBox::wxRichTextStyleType styleType = args_gurax.PickNumber<wxRichTextStyleListBox::wxRichTextStyleType>();
	// Function body
	pEntity_gurax->SetStyleType(styleType);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListCtrl#UpdateStyles()
Gurax_DeclareMethodAlias(wxRichTextStyleListCtrl, UpdateStyles_gurax, "UpdateStyles")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListCtrl, UpdateStyles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UpdateStyles();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRichTextStyleListCtrl
//------------------------------------------------------------------------------
VType_wxRichTextStyleListCtrl VTYPE_wxRichTextStyleListCtrl("RichTextStyleListCtrl");

void VType_wxRichTextStyleListCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(RichTextStyleListCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, GetRichTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, GetStyleChoice_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, GetStyleListBox_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, GetStyleSheet_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, GetStyleType_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, SetRichTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, SetStyleSheet_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, SetStyleType_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListCtrl, UpdateStyles_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleListCtrl
//------------------------------------------------------------------------------
VType& Value_wxRichTextStyleListCtrl::vtype = VTYPE_wxRichTextStyleListCtrl;

String Value_wxRichTextStyleListCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextStyleListCtrl");
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleListCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
