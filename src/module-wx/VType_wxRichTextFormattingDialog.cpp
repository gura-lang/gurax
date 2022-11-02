//==============================================================================
// VType_wxRichTextFormattingDialog.cpp
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

${help.ComposePropertyHelp(wxRichTextFormattingDialog)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRichTextFormattingDialog)}

${help.ComposeMethodHelp(wxRichTextFormattingDialog)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RichTextFormattingDialog(flags as Number, parent as wx.Window, title? as String, id? as Number, pos? as wx.Point, sz? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RichTextFormattingDialog_gurax, "RichTextFormattingDialog")
{
	Declare(VTYPE_wxRichTextFormattingDialog, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("sz", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RichTextFormattingDialog.");
}

Gurax_ImplementConstructorEx(RichTextFormattingDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* title = args_gurax.IsValid()? args_gurax.PickString() : "Formatting";
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& sz = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_DIALOG_STYLE;
	// Function body
	auto pEntity_gurax = new Value_wxRichTextFormattingDialog::EntityT(flags, parent, title, id, pos, sz, style);
	RefPtr<Value_wxRichTextFormattingDialog> pValue_gurax(new Value_wxRichTextFormattingDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RichTextFormattingDialog#ApplyStyle(ctrl as wx.RichTextCtrl, range as wx.RichTextRange, flags? as Number)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, ApplyStyle_gurax, "ApplyStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("ctrl", VTYPE_wxRichTextCtrl, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_wxRichTextRange, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, ApplyStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextCtrl& value_ctrl = args_gurax.Pick<Value_wxRichTextCtrl>();
	wxRichTextCtrl* ctrl = value_ctrl.GetEntityPtr();
	Value_wxRichTextRange& value_range = args_gurax.Pick<Value_wxRichTextRange>();
	const wxRichTextRange& range = value_range.GetEntity();
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : (wxRICHTEXT_SETSTYLE_WITH_UNDO | wxRICHTEXT_SETSTYLE_OPTIMIZE);
	// Function body
	bool rtn = pEntity_gurax->ApplyStyle(ctrl, range, flags);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#Create(flags as Number, parent as wx.Window, title? as String, id? as Number, pos? as wx.Point, sz? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("sz", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long flags = args_gurax.PickNumber<long>();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* title = args_gurax.IsValid()? args_gurax.PickString() : "Formatting";
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& sz = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_DIALOG_STYLE;
	// Function body
	bool rtn = pEntity_gurax->Create(flags, parent, title, id, pos, sz, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#GetImageList() {block?}
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetImageList_gurax, "GetImageList")
{
	Declare(VTYPE_wxImageList, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetImageList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxImageList(
		pEntity_gurax->GetImageList()));
}

// wx.RichTextFormattingDialog#GetStyle(ctrl as wx.RichTextCtrl, range as wx.RichTextRange)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("ctrl", VTYPE_wxRichTextCtrl, ArgOccur::Once, ArgFlag::None);
	DeclareArg("range", VTYPE_wxRichTextRange, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextCtrl& value_ctrl = args_gurax.Pick<Value_wxRichTextCtrl>();
	wxRichTextCtrl* ctrl = value_ctrl.GetEntityPtr();
	Value_wxRichTextRange& value_range = args_gurax.Pick<Value_wxRichTextRange>();
	const wxRichTextRange& range = value_range.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->GetStyle(ctrl, range);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#GetStyleDefinition() {block?}
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetStyleDefinition_gurax, "GetStyleDefinition")
{
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetStyleDefinition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleDefinition(
		pEntity_gurax->GetStyleDefinition()));
}

// wx.RichTextFormattingDialog#GetStyleSheet() {block?}
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetStyleSheet_gurax, "GetStyleSheet")
{
	Declare(VTYPE_wxRichTextStyleSheet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetStyleSheet_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleSheet(
		*pEntity_gurax->GetStyleSheet()));
}

// wx.RichTextFormattingDialog#SetAttributes(attr as wx.TextAttr)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, SetAttributes_gurax, "SetAttributes")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("attr", VTYPE_wxTextAttr, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, SetAttributes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxTextAttr& value_attr = args_gurax.Pick<Value_wxTextAttr>();
	const wxTextAttr& attr = value_attr.GetEntity();
	// Function body
	pEntity_gurax->SetAttributes(attr);
	return Gurax::Value::nil();
}

// wx.RichTextFormattingDialog#SetOptions(options as Number)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, SetOptions_gurax, "SetOptions")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("options", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, SetOptions_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int options = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetOptions(options);
	return Gurax::Value::nil();
}

// wx.RichTextFormattingDialog#GetOptions()
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetOptions_gurax, "GetOptions")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetOptions_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetOptions();
	return new Gurax::Value_Number(rtn);
}

// wx.RichTextFormattingDialog#HasOption(option as Number)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, HasOption_gurax, "HasOption")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("option", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, HasOption_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int option = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->HasOption(option);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#SetImageList(imageList as wx.ImageList)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, SetImageList_gurax, "SetImageList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("imageList", VTYPE_wxImageList, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, SetImageList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxImageList& value_imageList = args_gurax.Pick<Value_wxImageList>();
	wxImageList* imageList = value_imageList.GetEntityPtr();
	// Function body
	pEntity_gurax->SetImageList(imageList);
	return Gurax::Value::nil();
}

// wx.RichTextFormattingDialog#SetStyle(style as wx.TextAttr, update? as Bool)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, SetStyle_gurax, "SetStyle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("style", VTYPE_wxTextAttr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("update", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, SetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxTextAttr& value_style = args_gurax.Pick<Value_wxTextAttr>();
	const wxTextAttr& style = value_style.GetEntity();
	bool update = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->SetStyle(style, update);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#SetStyleDefinition(styleDef as wx.RichTextStyleDefinition, sheet as wx.RichTextStyleSheet, update? as Bool)
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, SetStyleDefinition_gurax, "SetStyleDefinition")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("styleDef", VTYPE_wxRichTextStyleDefinition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sheet", VTYPE_wxRichTextStyleSheet, ArgOccur::Once, ArgFlag::None);
	DeclareArg("update", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, SetStyleDefinition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextStyleDefinition& value_styleDef = args_gurax.Pick<Value_wxRichTextStyleDefinition>();
	const wxRichTextStyleDefinition& styleDef = value_styleDef.GetEntity();
	Value_wxRichTextStyleSheet& value_sheet = args_gurax.Pick<Value_wxRichTextStyleSheet>();
	wxRichTextStyleSheet* sheet = value_sheet.GetEntityPtr();
	bool update = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->SetStyleDefinition(styleDef, sheet, update);
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#UpdateDisplay()
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, UpdateDisplay_gurax, "UpdateDisplay")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, UpdateDisplay_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->UpdateDisplay();
	return new Gurax::Value_Bool(rtn);
}

// wx.RichTextFormattingDialog#GetAttributes() {block?}
Gurax_DeclareMethodAlias(wxRichTextFormattingDialog, GetAttributes_gurax, "GetAttributes")
{
	Declare(VTYPE_wxTextAttr, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRichTextFormattingDialog, GetAttributes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTextAttr(
		pEntity_gurax->GetAttributes()));
}

// wx.RichTextFormattingDialog.GetDialog(win as wx.Window) {block?}
Gurax_DeclareClassMethodAlias(wxRichTextFormattingDialog, GetDialog_gurax, "GetDialog")
{
	Declare(VTYPE_wxRichTextFormattingDialog, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxRichTextFormattingDialog, GetDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextFormattingDialog(
		wxRichTextFormattingDialog::GetDialog(win)));
}

// wx.RichTextFormattingDialog.GetDialogAttributes(win as wx.Window) {block?}
Gurax_DeclareClassMethodAlias(wxRichTextFormattingDialog, GetDialogAttributes_gurax, "GetDialogAttributes")
{
	Declare(VTYPE_wxTextAttr, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxRichTextFormattingDialog, GetDialogAttributes_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTextAttr(
		*wxRichTextFormattingDialog::GetDialogAttributes(win)));
}

// wx.RichTextFormattingDialog.GetDialogStyleDefinition(win as wx.Window) {block?}
Gurax_DeclareClassMethodAlias(wxRichTextFormattingDialog, GetDialogStyleDefinition_gurax, "GetDialogStyleDefinition")
{
	Declare(VTYPE_wxRichTextStyleDefinition, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxRichTextFormattingDialog, GetDialogStyleDefinition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextStyleDefinition(
		wxRichTextFormattingDialog::GetDialogStyleDefinition(win)));
}

// wx.RichTextFormattingDialog.GetFormattingDialogFactory() {block?}
Gurax_DeclareClassMethodAlias(wxRichTextFormattingDialog, GetFormattingDialogFactory_gurax, "GetFormattingDialogFactory")
{
	Declare(VTYPE_wxRichTextFormattingDialogFactory, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxRichTextFormattingDialog, GetFormattingDialogFactory_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRichTextFormattingDialogFactory(
		wxRichTextFormattingDialog::GetFormattingDialogFactory()));
}

// wx.RichTextFormattingDialog.SetFormattingDialogFactory(factory as wx.RichTextFormattingDialogFactory)
Gurax_DeclareClassMethodAlias(wxRichTextFormattingDialog, SetFormattingDialogFactory_gurax, "SetFormattingDialogFactory")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("factory", VTYPE_wxRichTextFormattingDialogFactory, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxRichTextFormattingDialog, SetFormattingDialogFactory_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRichTextFormattingDialogFactory& value_factory = args_gurax.Pick<Value_wxRichTextFormattingDialogFactory>();
	wxRichTextFormattingDialogFactory* factory = value_factory.GetEntityPtr();
	// Function body
	wxRichTextFormattingDialog::SetFormattingDialogFactory(factory);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRichTextFormattingDialog
//------------------------------------------------------------------------------
VType_wxRichTextFormattingDialog VTYPE_wxRichTextFormattingDialog("RichTextFormattingDialog");

void VType_wxRichTextFormattingDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPropertySheetDialog, Flag::Mutable, Gurax_CreateConstructor(RichTextFormattingDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, ApplyStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, Create_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetImageList_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetStyleDefinition_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetStyleSheet_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetAttributes_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetOptions_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetOptions_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, HasOption_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetImageList_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetStyle_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetStyleDefinition_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, UpdateDisplay_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetAttributes_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetDialog_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetDialogAttributes_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetDialogStyleDefinition_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, GetFormattingDialogFactory_gurax));
	Assign(Gurax_CreateMethod(wxRichTextFormattingDialog, SetFormattingDialogFactory_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRichTextFormattingDialog
//------------------------------------------------------------------------------
VType& Value_wxRichTextFormattingDialog::vtype = VTYPE_wxRichTextFormattingDialog;

String Value_wxRichTextFormattingDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextFormattingDialog");
}

//------------------------------------------------------------------------------
// Value_wxRichTextFormattingDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
