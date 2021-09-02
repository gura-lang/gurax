//==============================================================================
// VType_wxPickerBase.cpp
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
// wx.PickerBase#CreateBase(parent as wx.Window, id as Number, text? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxPickerBase, CreateBase_gurax, "CreateBase")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, CreateBase_gurax, processor_gurax, argument_gurax)
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
	const char* text = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxButtonNameStr;
	// Function body
	bool rtn = pEntity_gurax->CreateBase(parent, id, text, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.PickerBase#GetInternalMargin()
Gurax_DeclareMethodAlias(wxPickerBase, GetInternalMargin_gurax, "GetInternalMargin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, GetInternalMargin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetInternalMargin();
	return new Gurax::Value_Number(rtn);
}

// wx.PickerBase#GetPickerCtrlProportion()
Gurax_DeclareMethodAlias(wxPickerBase, GetPickerCtrlProportion_gurax, "GetPickerCtrlProportion")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, GetPickerCtrlProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPickerCtrlProportion();
	return new Gurax::Value_Number(rtn);
}

// wx.PickerBase#GetTextCtrl()
Gurax_DeclareMethodAlias(wxPickerBase, GetTextCtrl_gurax, "GetTextCtrl")
{
	Declare(VTYPE_wxTextCtrl, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, GetTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxTextCtrl(
		pEntity_gurax->GetTextCtrl()));
}

// wx.PickerBase#GetPickerCtrl()
Gurax_DeclareMethodAlias(wxPickerBase, GetPickerCtrl_gurax, "GetPickerCtrl")
{
	Declare(VTYPE_wxControl, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, GetPickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxControl(
		pEntity_gurax->GetPickerCtrl()));
}

// wx.PickerBase#GetTextCtrlProportion()
Gurax_DeclareMethodAlias(wxPickerBase, GetTextCtrlProportion_gurax, "GetTextCtrlProportion")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, GetTextCtrlProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTextCtrlProportion();
	return new Gurax::Value_Number(rtn);
}

// wx.PickerBase#HasTextCtrl()
Gurax_DeclareMethodAlias(wxPickerBase, HasTextCtrl_gurax, "HasTextCtrl")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, HasTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasTextCtrl();
	return new Gurax::Value_Bool(rtn);
}

// wx.PickerBase#IsPickerCtrlGrowable()
Gurax_DeclareMethodAlias(wxPickerBase, IsPickerCtrlGrowable_gurax, "IsPickerCtrlGrowable")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, IsPickerCtrlGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsPickerCtrlGrowable();
	return new Gurax::Value_Bool(rtn);
}

// wx.PickerBase#IsTextCtrlGrowable()
Gurax_DeclareMethodAlias(wxPickerBase, IsTextCtrlGrowable_gurax, "IsTextCtrlGrowable")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, IsTextCtrlGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsTextCtrlGrowable();
	return new Gurax::Value_Bool(rtn);
}

// wx.PickerBase#SetInternalMargin(margin as Number)
Gurax_DeclareMethodAlias(wxPickerBase, SetInternalMargin_gurax, "SetInternalMargin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("margin", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetInternalMargin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int margin = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetInternalMargin(margin);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetPickerCtrlGrowable(grow? as Bool)
Gurax_DeclareMethodAlias(wxPickerBase, SetPickerCtrlGrowable_gurax, "SetPickerCtrlGrowable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("grow", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetPickerCtrlGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool grow = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetPickerCtrlGrowable(grow);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetPickerCtrlProportion(prop as Number)
Gurax_DeclareMethodAlias(wxPickerBase, SetPickerCtrlProportion_gurax, "SetPickerCtrlProportion")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("prop", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetPickerCtrlProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int prop = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPickerCtrlProportion(prop);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetTextCtrlGrowable(grow? as Bool)
Gurax_DeclareMethodAlias(wxPickerBase, SetTextCtrlGrowable_gurax, "SetTextCtrlGrowable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("grow", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetTextCtrlGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool grow = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetTextCtrlGrowable(grow);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetTextCtrlProportion(prop as Number)
Gurax_DeclareMethodAlias(wxPickerBase, SetTextCtrlProportion_gurax, "SetTextCtrlProportion")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("prop", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetTextCtrlProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int prop = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetTextCtrlProportion(prop);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetTextCtrl(text as wx.TextCtrl)
Gurax_DeclareMethodAlias(wxPickerBase, SetTextCtrl_gurax, "SetTextCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_wxTextCtrl, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxTextCtrl& value_text = args_gurax.Pick<Value_wxTextCtrl>();
	wxTextCtrl* text = value_text.GetEntityPtr();
	// Function body
	pEntity_gurax->SetTextCtrl(text);
	return Gurax::Value::nil();
}

// wx.PickerBase#SetPickerCtrl(picker as wx.Control)
Gurax_DeclareMethodAlias(wxPickerBase, SetPickerCtrl_gurax, "SetPickerCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("picker", VTYPE_wxControl, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, SetPickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxControl& value_picker = args_gurax.Pick<Value_wxControl>();
	wxControl* picker = value_picker.GetEntityPtr();
	// Function body
	pEntity_gurax->SetPickerCtrl(picker);
	return Gurax::Value::nil();
}

// wx.PickerBase#UpdatePickerFromTextCtrl()
Gurax_DeclareMethodAlias(wxPickerBase, UpdatePickerFromTextCtrl_gurax, "UpdatePickerFromTextCtrl")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, UpdatePickerFromTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UpdatePickerFromTextCtrl();
	return Gurax::Value::nil();
}

// wx.PickerBase#UpdateTextCtrlFromPicker()
Gurax_DeclareMethodAlias(wxPickerBase, UpdateTextCtrlFromPicker_gurax, "UpdateTextCtrlFromPicker")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPickerBase, UpdateTextCtrlFromPicker_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UpdateTextCtrlFromPicker();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPickerBase
//------------------------------------------------------------------------------
VType_wxPickerBase VTYPE_wxPickerBase("PickerBase");

void VType_wxPickerBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPickerBase, CreateBase_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, GetInternalMargin_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, GetPickerCtrlProportion_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, GetTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, GetPickerCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, GetTextCtrlProportion_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, HasTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, IsPickerCtrlGrowable_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, IsTextCtrlGrowable_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetInternalMargin_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetPickerCtrlGrowable_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetPickerCtrlProportion_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetTextCtrlGrowable_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetTextCtrlProportion_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, SetPickerCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, UpdatePickerFromTextCtrl_gurax));
	Assign(Gurax_CreateMethod(wxPickerBase, UpdateTextCtrlFromPicker_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPickerBase
//------------------------------------------------------------------------------
VType& Value_wxPickerBase::vtype = VTYPE_wxPickerBase;

String Value_wxPickerBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PickerBase");
}

//------------------------------------------------------------------------------
// Value_wxPickerBase::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
