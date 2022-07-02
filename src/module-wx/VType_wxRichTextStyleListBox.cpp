//==============================================================================
// VType_wxRichTextStyleListBox.cpp
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
// wx.RichTextStyleListBox(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RichTextStyleListBox_gurax, "RichTextStyleListBox")
{
	Declare(VTYPE_wxRichTextStyleListBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RichTextStyleListBox.");
}

Gurax_ImplementConstructorEx(RichTextStyleListBox_gurax, processor_gurax, argument_gurax)
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
	auto pEntity_gurax = new Value_wxRichTextStyleListBox::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxRichTextStyleListBox> pValue_gurax(new Value_wxRichTextStyleListBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RichTextStyleListBox#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, Create_gurax, "Create")
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

Gurax_ImplementMethodEx(wxRichTextStyleListBox, Create_gurax, processor_gurax, argument_gurax)
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

// wx.RichTextStyleListBox#ApplyStyle(i as Number)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, ApplyStyle_gurax, "ApplyStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, ApplyStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int i = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ApplyStyle(i);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListBox#ConvertTenthsMMToPixels(dc as wx.DC, units as Number)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, ConvertTenthsMMToPixels_gurax, "ConvertTenthsMMToPixels")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("units", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, ConvertTenthsMMToPixels_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	int units = args_gurax.PickNumber<int>();
	// Function body
	int rtn = pEntity_gurax->ConvertTenthsMMToPixels(dc, units);
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextStyleListBox#CreateHTML(def as wx.RichTextStyleDefinition)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, CreateHTML_gurax, "CreateHTML")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("def", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, CreateHTML_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_def = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	wxRichTextStyleDefinition* def = value_def.GetEntityPtr();
	// Function body
	wxString rtn = pEntity_gurax->CreateHTML(def);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.RichTextStyleListBox#GetApplyOnSelection()
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, GetApplyOnSelection_gurax, "GetApplyOnSelection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, GetApplyOnSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetApplyOnSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextStyleListBox#GetRichTextCtrl() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, GetRichTextCtrl_gurax, "GetRichTextCtrl")
{
	Declare(VTYPE_wxRichTextCtrl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, GetRichTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextCtrl(
		pEntity_gurax->GetRichTextCtrl()));
}

// wx.RichTextStyleListBox#GetStyle(i as Number) {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t i = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleDefinition(
		pEntity_gurax->GetStyle(i)));
}

// wx.RichTextStyleListBox#GetStyleSheet() {block?}
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, GetStyleSheet_gurax, "GetStyleSheet")
{
	Declare(VTYPE_wxRichTextStyleSheet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, GetStyleSheet_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleSheet(
		*pEntity_gurax->GetStyleSheet()));
}

// wx.RichTextStyleListBox#OnLeftDown(event as wx.MouseEvent)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, OnLeftDown_gurax, "OnLeftDown")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("event", VTYPE_wxMouseEvent, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, OnLeftDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMouseEvent& value_event = args_gurax.Pick<Value_wxMouseEvent>();
	wxMouseEvent& event = value_event.GetEntity();
	// Function body
	pEntity_gurax->OnLeftDown(event);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListBox#SetApplyOnSelection(applyOnSelection as Bool)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, SetApplyOnSelection_gurax, "SetApplyOnSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("applyOnSelection", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, SetApplyOnSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool applyOnSelection = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetApplyOnSelection(applyOnSelection);
	return Gurax::Value::nil();
}

// wx.RichTextStyleListBox#SetRichTextCtrl(ctrl as wx.RichTextCtrl)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, SetRichTextCtrl_gurax, "SetRichTextCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ctrl", VTYPE_wxRichTextCtrl, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, SetRichTextCtrl_gurax, processor_gurax, argument_gurax)
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

// wx.RichTextStyleListBox#SetStyleSheet(styleSheet as wx.RichTextStyleSheet)
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, SetStyleSheet_gurax, "SetStyleSheet")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("styleSheet", VTYPE_wxRichTextStyleSheet, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, SetStyleSheet_gurax, processor_gurax, argument_gurax)
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

// wx.RichTextStyleListBox#UpdateStyles()
Gurax_DeclareMethodAlias(wxRichTextStyleListBox, UpdateStyles_gurax, "UpdateStyles")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextStyleListBox, UpdateStyles_gurax, processor_gurax, argument_gurax)
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
// VType_wxRichTextStyleListBox
//------------------------------------------------------------------------------
VType_wxRichTextStyleListBox VTYPE_wxRichTextStyleListBox("RichTextStyleListBox");

void VType_wxRichTextStyleListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHtmlListBox, Flag::Mutable, Gurax_CreateConstructor(RichTextStyleListBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, Create_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, ApplyStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, ConvertTenthsMMToPixels_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, CreateHTML_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, GetApplyOnSelection_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, GetRichTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, GetStyleSheet_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, OnLeftDown_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, SetApplyOnSelection_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, SetRichTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, SetStyleSheet_gurax));
	Assign(Gurax_CreateMethod(wxRichTextStyleListBox, UpdateStyles_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleListBox
//------------------------------------------------------------------------------
VType& Value_wxRichTextStyleListBox::vtype = VTYPE_wxRichTextStyleListBox;

String Value_wxRichTextStyleListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextStyleListBox");
}

//------------------------------------------------------------------------------
// Value_wxRichTextStyleListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
