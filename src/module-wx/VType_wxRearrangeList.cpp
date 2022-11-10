﻿//==============================================================================
// VType_wxRearrangeList.cpp
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

${help.ComposePropertyHelp(wx.RearrangeList, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RearrangeList, `en)}

${help.ComposeMethodHelp(wx.RearrangeList, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RearrangeList(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, order[] as Number, items[] as String, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(RearrangeList_gurax, "RearrangeList")
{
	Declare(VTYPE_wxRearrangeList, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RearrangeList.");
}

Gurax_ImplementConstructorEx(RearrangeList_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	wxArrayInt order = Util::CreateArrayInt(args_gurax.PickList());
	wxArrayString items = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxRearrangeListNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxRearrangeList::EntityT(parent, id, pos, size, order, items, style, validator, name);
	RefPtr<Value_wxRearrangeList> pValue_gurax(new Value_wxRearrangeList(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RearrangeList#Create(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, order[] as Number, items[] as String, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxRearrangeList, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, Create_gurax, processor_gurax, argument_gurax)
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
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	wxArrayInt order = Util::CreateArrayInt(args_gurax.PickList());
	wxArrayString items = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxRearrangeListNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, order, items, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.RearrangeList#GetCurrentOrder()
Gurax_DeclareMethodAlias(wxRearrangeList, GetCurrentOrder_gurax, "GetCurrentOrder")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, GetCurrentOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayInt rtn = pEntity_gurax->GetCurrentOrder();
	return Util::CreateList(rtn);
}

// wx.RearrangeList#CanMoveCurrentUp()
Gurax_DeclareMethodAlias(wxRearrangeList, CanMoveCurrentUp_gurax, "CanMoveCurrentUp")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, CanMoveCurrentUp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanMoveCurrentUp();
	return new Gurax::Value_Bool(rtn);
}

// wx.RearrangeList#CanMoveCurrentDown()
Gurax_DeclareMethodAlias(wxRearrangeList, CanMoveCurrentDown_gurax, "CanMoveCurrentDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, CanMoveCurrentDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanMoveCurrentDown();
	return new Gurax::Value_Bool(rtn);
}

// wx.RearrangeList#MoveCurrentUp()
Gurax_DeclareMethodAlias(wxRearrangeList, MoveCurrentUp_gurax, "MoveCurrentUp")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, MoveCurrentUp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MoveCurrentUp();
	return new Gurax::Value_Bool(rtn);
}

// wx.RearrangeList#MoveCurrentDown()
Gurax_DeclareMethodAlias(wxRearrangeList, MoveCurrentDown_gurax, "MoveCurrentDown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeList, MoveCurrentDown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->MoveCurrentDown();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRearrangeList
//------------------------------------------------------------------------------
VType_wxRearrangeList VTYPE_wxRearrangeList("RearrangeList");

void VType_wxRearrangeList::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCheckListBox, Flag::Mutable, Gurax_CreateConstructor(RearrangeList_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRearrangeList, Create_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeList, GetCurrentOrder_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeList, CanMoveCurrentUp_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeList, CanMoveCurrentDown_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeList, MoveCurrentUp_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeList, MoveCurrentDown_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRearrangeList
//------------------------------------------------------------------------------
VType& Value_wxRearrangeList::vtype = VTYPE_wxRearrangeList;

String Value_wxRearrangeList::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RearrangeList");
}

//------------------------------------------------------------------------------
// Value_wxRearrangeList::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
