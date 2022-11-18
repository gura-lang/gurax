﻿//==============================================================================
// VType_wxSizerItem.cpp
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

${help.ComposePropertyHelp(wx.SizerItem, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SizerItem, `en)}

${help.ComposeMethodHelp(wx.SizerItem, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SizerItem#AssignWindow(window as wx.Window)
Gurax_DeclareMethodAlias(wxSizerItem, AssignWindow_gurax, "AssignWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, AssignWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	pEntity_gurax->AssignWindow(window);
	return Gurax::Value::nil();
}

// wx.SizerItem#AssignSizer(sizer as wx.Sizer)
Gurax_DeclareMethodAlias(wxSizerItem, AssignSizer_gurax, "AssignSizer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sizer", VTYPE_wxSizer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, AssignSizer_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->AssignSizer(sizer);
	return Gurax::Value::nil();
}

// wx.SizerItem#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.SizerItem#DeleteWindows()
Gurax_DeclareMethodAlias(wxSizerItem, DeleteWindows_gurax, "DeleteWindows")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, DeleteWindows_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DeleteWindows();
	return Gurax::Value::nil();
}

// wx.SizerItem#DetachSizer()
Gurax_DeclareMethodAlias(wxSizerItem, DetachSizer_gurax, "DetachSizer")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, DetachSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DetachSizer();
	return Gurax::Value::nil();
}

// wx.SizerItem#GetBorder()
Gurax_DeclareMethodAlias(wxSizerItem, GetBorder_gurax, "GetBorder")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, GetBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetBorder();
	return new Gurax::Value_Number(rtn);
}

// wx.SizerItem#GetFlag()
Gurax_DeclareMethodAlias(wxSizerItem, GetFlag_gurax, "GetFlag")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, GetFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlag();
	return new Gurax::Value_Number(rtn);
}

// wx.SizerItem#GetId()
Gurax_DeclareMethodAlias(wxSizerItem, GetId_gurax, "GetId")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetId();
	return new Gurax::Value_Number(rtn);
}

// wx.SizerItem#GetMinSize() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetMinSize_gurax, "GetMinSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetMinSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetMinSize()));
}

// wx.SizerItem#SetMinSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxSizerItem, SetMinSize_gurax, "SetMinSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetMinSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetMinSize(size);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetMinSizeXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetMinSizeXY_gurax, "SetMinSizeXY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetMinSizeXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinSize(x, y);
	return Gurax::Value::nil();
}

// wx.SizerItem#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

// wx.SizerItem#GetProportion()
Gurax_DeclareMethodAlias(wxSizerItem, GetProportion_gurax, "GetProportion")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, GetProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetProportion();
	return new Gurax::Value_Number(rtn);
}

// wx.SizerItem#GetRatio()
Gurax_DeclareMethodAlias(wxSizerItem, GetRatio_gurax, "GetRatio")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, GetRatio_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	float rtn = pEntity_gurax->GetRatio();
	return new Gurax::Value_Number(rtn);
}

// wx.SizerItem#GetRect() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetRect_gurax, "GetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetRect()));
}

// wx.SizerItem#GetSize() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSize()));
}

// wx.SizerItem#GetSizer() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetSizer_gurax, "GetSizer")
{
	Declare(VTYPE_wxSizer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizer(
		pEntity_gurax->GetSizer()));
}

// wx.SizerItem#GetSpacer() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetSpacer_gurax, "GetSpacer")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetSpacer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSpacer()));
}

// wx.SizerItem#GetUserData() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetUserData_gurax, "GetUserData")
{
	Declare(VTYPE_wxObject, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetUserData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxObject(
		*pEntity_gurax->GetUserData()));
}

// wx.SizerItem#GetWindow() {block?}
Gurax_DeclareMethodAlias(wxSizerItem, GetWindow_gurax, "GetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSizerItem, GetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetWindow()));
}

// wx.SizerItem#IsShown()
Gurax_DeclareMethodAlias(wxSizerItem, IsShown_gurax, "IsShown")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, IsShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsShown();
	return new Gurax::Value_Bool(rtn);
}

// wx.SizerItem#IsSizer()
Gurax_DeclareMethodAlias(wxSizerItem, IsSizer_gurax, "IsSizer")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, IsSizer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSizer();
	return new Gurax::Value_Bool(rtn);
}

// wx.SizerItem#IsSpacer()
Gurax_DeclareMethodAlias(wxSizerItem, IsSpacer_gurax, "IsSpacer")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, IsSpacer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSpacer();
	return new Gurax::Value_Bool(rtn);
}

// wx.SizerItem#IsWindow()
Gurax_DeclareMethodAlias(wxSizerItem, IsWindow_gurax, "IsWindow")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, IsWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsWindow();
	return new Gurax::Value_Bool(rtn);
}

// wx.SizerItem#SetBorder(border as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetBorder_gurax, "SetBorder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int border = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetBorder(border);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetDimension(pos as wx.Point, size as wx.Size)
Gurax_DeclareMethodAlias(wxSizerItem, SetDimension_gurax, "SetDimension")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetDimension_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetDimension(pos, size);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetFlag(flag as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetFlag_gurax, "SetFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flag = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlag(flag);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetId(id as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetId_gurax, "SetId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetId(id);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetInitSize(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetInitSize_gurax, "SetInitSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetInitSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetInitSize(x, y);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetProportion(proportion as Number)
Gurax_DeclareMethodAlias(wxSizerItem, SetProportion_gurax, "SetProportion")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("proportion", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetProportion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int proportion = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetProportion(proportion);
	return Gurax::Value::nil();
}

// wx.SizerItem#SetUserData(userData as wx.Object)
Gurax_DeclareMethodAlias(wxSizerItem, SetUserData_gurax, "SetUserData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("userData", VTYPE_wxObject, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, SetUserData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxObject& value_userData = args_gurax.Pick<Value_wxObject>();
	wxObject* userData = value_userData.GetEntityPtr();
	// Function body
	pEntity_gurax->SetUserData(userData);
	return Gurax::Value::nil();
}

// wx.SizerItem#Show(show as Bool)
Gurax_DeclareMethodAlias(wxSizerItem, Show_gurax, "Show")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSizerItem, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Show(show);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSizerItem
//------------------------------------------------------------------------------
VType_wxSizerItem VTYPE_wxSizerItem("SizerItem");

void VType_wxSizerItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSizerItem, AssignWindow_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, AssignSizer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, DeleteWindows_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, DetachSizer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetBorder_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetFlag_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetId_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetMinSize_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetMinSize_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetMinSizeXY_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetProportion_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetRatio_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetRect_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetSizer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetSpacer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetUserData_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, GetWindow_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, IsShown_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, IsSizer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, IsSpacer_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, IsWindow_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetBorder_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetDimension_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetFlag_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetId_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetInitSize_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetProportion_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, SetUserData_gurax));
	Assign(Gurax_CreateMethod(wxSizerItem, Show_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSizerItem
//------------------------------------------------------------------------------
VType& Value_wxSizerItem::vtype = VTYPE_wxSizerItem;

String Value_wxSizerItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SizerItem");
}

Gurax_EndModuleScope(wx)
