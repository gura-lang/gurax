﻿//==============================================================================
// VType_wxDropTarget.cpp
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

${help.ComposePropertyHelp(wx.DropTarget, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DropTarget, `en)}

${help.ComposeMethodHelp(wx.DropTarget, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DropTarget#GetData()
Gurax_DeclareMethodAlias(wxDropTarget, GetData_gurax, "GetData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, GetData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetData();
	return new Gurax::Value_Bool(rtn);
}

// wx.DropTarget#OnData(x as Number, y as Number, defResult as Number)
Gurax_DeclareMethodAlias(wxDropTarget, OnData_gurax, "OnData")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defResult", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, OnData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	wxDragResult defResult = args_gurax.PickNumber<wxDragResult>();
	// Function body
	wxDragResult rtn = pEntity_gurax->OnData(x, y, defResult);
	return new Gurax::Value_Number(rtn);
}

// wx.DropTarget#OnDragOver(x as Number, y as Number, defResult as Number)
Gurax_DeclareMethodAlias(wxDropTarget, OnDragOver_gurax, "OnDragOver")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defResult", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, OnDragOver_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	wxDragResult defResult = args_gurax.PickNumber<wxDragResult>();
	// Function body
	wxDragResult rtn = pEntity_gurax->OnDragOver(x, y, defResult);
	return new Gurax::Value_Number(rtn);
}

// wx.DropTarget#OnDrop(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxDropTarget, OnDrop_gurax, "OnDrop")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, OnDrop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	// Function body
	bool rtn = pEntity_gurax->OnDrop(x, y);
	return new Gurax::Value_Bool(rtn);
}

// wx.DropTarget#OnEnter(x as Number, y as Number, defResult as Number)
Gurax_DeclareMethodAlias(wxDropTarget, OnEnter_gurax, "OnEnter")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defResult", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, OnEnter_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	wxDragResult defResult = args_gurax.PickNumber<wxDragResult>();
	// Function body
	wxDragResult rtn = pEntity_gurax->OnEnter(x, y, defResult);
	return new Gurax::Value_Number(rtn);
}

// wx.DropTarget#OnLeave()
Gurax_DeclareMethodAlias(wxDropTarget, OnLeave_gurax, "OnLeave")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, OnLeave_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnLeave();
	return Gurax::Value::nil();
}

// wx.DropTarget#GetDataObject() {block?}
Gurax_DeclareMethodAlias(wxDropTarget, GetDataObject_gurax, "GetDataObject")
{
	Declare(VTYPE_wxDataObject, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, GetDataObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataObject(
		pEntity_gurax->GetDataObject()));
}

// wx.DropTarget#SetDataObject(data as wx.DataObject)
Gurax_DeclareMethodAlias(wxDropTarget, SetDataObject_gurax, "SetDataObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("data", VTYPE_wxDataObject, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, SetDataObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataObject& value_data = args_gurax.Pick<Value_wxDataObject>();
	wxDataObject* data = value_data.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDataObject(data);
	return Gurax::Value::nil();
}

// wx.DropTarget#SetDefaultAction(action as Number)
Gurax_DeclareMethodAlias(wxDropTarget, SetDefaultAction_gurax, "SetDefaultAction")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("action", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, SetDefaultAction_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxDragResult action = args_gurax.PickNumber<wxDragResult>();
	// Function body
	pEntity_gurax->SetDefaultAction(action);
	return Gurax::Value::nil();
}

// wx.DropTarget#GetDefaultAction()
Gurax_DeclareMethodAlias(wxDropTarget, GetDefaultAction_gurax, "GetDefaultAction")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDropTarget, GetDefaultAction_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxDragResult rtn = pEntity_gurax->GetDefaultAction();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDropTarget
//------------------------------------------------------------------------------
VType_wxDropTarget VTYPE_wxDropTarget("DropTarget");

void VType_wxDropTarget::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDropTarget, GetData_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, OnData_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, OnDragOver_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, OnDrop_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, OnEnter_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, OnLeave_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, GetDataObject_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, SetDataObject_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, SetDefaultAction_gurax));
	Assign(Gurax_CreateMethod(wxDropTarget, GetDefaultAction_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDropTarget
//------------------------------------------------------------------------------
VType& Value_wxDropTarget::vtype = VTYPE_wxDropTarget;

String Value_wxDropTarget::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DropTarget");
}

Gurax_EndModuleScope(wx)
